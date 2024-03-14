from typing import Any, Coroutine
from textual.app import App, ComposeResult
from textual.containers import ScrollableContainer
from textual.reactive import reactive
from textual.events import Key
from textual.widgets import Button, Footer, Header, Static, Input, Label, Digits
import math
import struct
import serial
import threading
import keyboard
import binascii
import rclpy
from rclpy.node import Node

from interfaces.msg import Steer

# use WASD to move robot and Q/E to rotate it along Z axis

front = "w"
rear = "s"
right = "d"
left = "a"

r_right = "e"
r_left = "q"

class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('tui_publisher')
        self.publisher_ = self.create_publisher(Steer, 'tui_steering', 10)

class agv_command:
    # type = 0x01
    # id = 0x0c
    # mode = 0x03    0x01 for movement 0x03 for stop
    pos = math.nan
    # vel = -5.0
    trq = 0.0
    acc = math.nan

    def __init__(self, type, id, mode, var_1, var_2, var_3):
        self.type = type
        self.id = id
        self.mode = mode
        if(type == 0x01):
            self.vel = var_1
        elif(type == 0x00):
            self.x_v = var_1
            print("v1: "+str(var_1))
            self.y_v = var_2
            print("v2: "+str(var_2))
            self.rot_v = var_3
            print("rot: "+str(var_3))

    def get_bytes(self):
        ba_pos = bytearray(struct.pack("f", self.pos))
        ba_arb = bytearray([self.type,self.id,self.mode])
        if(self.type == 0x01):  
            ba_vel = bytearray(struct.pack("f", self.vel))
            ba_trq = bytearray(struct.pack("f", self.trq))
            ba_acc = bytearray(struct.pack("f", self.acc))
            byte_array = ba_arb+ba_pos+ba_vel+ba_trq+ba_acc

        elif(self.type == 0x00): 
            ba_xv = bytearray(struct.pack("f", self.x_v))
            print("xv: " + str(binascii.hexlify(ba_xv)))

            ba_yv = bytearray(struct.pack("f", self.y_v))
            print("yv: " + str(binascii.hexlify(ba_yv)))

            ba_rv = bytearray(struct.pack("f", self.rot_v))
            print("rot: " + str(binascii.hexlify(ba_rv)))

            ba_nop = bytearray(4*[0x50])
            byte_array = ba_arb+ba_xv+ba_yv+ba_rv+ba_nop
            print("final: " + str(binascii.hexlify(byte_array)))
        return byte_array 

class AxisXDisplay(Static):
    axis_value = reactive(0.0)
    axis_x = reactive(0.0)

    def on_mount(self) -> None:
        """Event handler called when widget is added to the app."""
        self.set_interval(0.1, self.update_axes)
    
    def update_axes(self) -> None:
        self.axis_x = 0.0
        axis_y = 0.0
        if(keyboard.is_pressed(right)):
            self.axis_x += 1.0
        if(keyboard.is_pressed(left)):
            self.axis_x -= 1.0
        
        if(keyboard.is_pressed(front)):
            axis_y += 1.0
        if(keyboard.is_pressed(rear)):
            axis_y -= 1.0
        
        axis_val = math.sqrt(self.axis_x*self.axis_x + axis_y*axis_y)
        if(axis_val != 0):
            self.axis_value = self.axis_x/axis_val
        else:
            self.axis_value = 0.0

    def watch_axis_value(self) -> None:
        self.update(f"X: {self.axis_value}")

class AxisYDisplay(Static):
    axis_value = reactive(0.0)
    axis_y = reactive(0.0)

    def on_mount(self) -> None:
        """Event handler called when widget is added to the app."""
        self.set_interval(0.1, self.update_axes)
    
    def update_axes(self) -> None:
        self.axis_y = 0.0
        axis_x = 0.0
        if(keyboard.is_pressed(front)):
            self.axis_y += 1.0
        if(keyboard.is_pressed(rear)):
            self.axis_y -= 1.0
        
        if(keyboard.is_pressed(right)):
            axis_x += 1.0
        if(keyboard.is_pressed(left)):
            axis_x -= 1.0

        axis_val = math.sqrt(self.axis_y*self.axis_y + axis_x*axis_x)
        if(axis_val != 0):
            self.axis_value = self.axis_y/axis_val
        else:
            self.axis_value = 0.0

    def watch_axis_value(self) -> None:
        self.update(f"Y: {self.axis_value}")

class RotDisplay(Static):
    axis_value = reactive(0.0)
    axis_z = reactive(0.0)

    def on_mount(self) -> None:
        """Event handler called when widget is added to the app."""
        self.set_interval(0.1, self.update_axes)
        
    def update_axes(self) -> None:
        self.axis_z = 0.0
        if(keyboard.is_pressed(r_left)):
            self.axis_z += 1.0
        if(keyboard.is_pressed(r_right)):
            self.axis_z -= 1.0
            
        self.axis_value = self.axis_z

    def watch_axis_value(self) -> None:
        self.update(f"ROT: {self.axis_value}")

class MoteusApp(App):

    CSS_PATH = "/workspaces/ros_agv_pc/src/textual_gui_pkg/textual_gui_pkg/moteus_app.tcss"
    BINDINGS = [("r", "toggle_dark", "Toggle dark mode")]

    send = False
    vel = 0.0
    use_brake = True

    def compose(self) -> ComposeResult:
        """Create child widgets for the app."""
        yield Header()
        yield Footer()
        yield AxisXDisplay()
        yield AxisYDisplay()
        yield RotDisplay()
        yield Button("Start", id="start", variant="success")
        yield Input(placeholder="type desired velocity",id="vel_input",type="number")
        yield Button("Stop", id="stop", variant="error")
        yield Button("Brake", id="brake", variant="success")
        yield Button("No Brake", id="no_brake", variant="error")

    def action_toggle_dark(self) -> None:
        """An action to toggle dark mode."""
        self.dark = not self.dark

    def on_mount(self) -> None:
        """Event handler called when widget is added to the app."""
        self.set_interval(0.1, self.send_frame)

    def send_frame(self):
        if(self.send):

            axis_y = self.query_one(AxisYDisplay).axis_value
            axis_x = self.query_one(AxisXDisplay).axis_value

            axis_rot = self.query_one(RotDisplay).axis_value
            # print(axis_x)
            # print(axis_y)
            # print(self.vel)
            if(axis_y == 0 and axis_x == 0 and axis_rot == 0):
                # mode = 0x04 #free to move
                if(self.use_brake):
                    mode = 0x04
                else:
                    mode = 0x03
            else:
                mode = 0x01
            print("dupa")
            print(axis_x*self.vel)
            new_command = agv_command(0x00, 0x10, mode, axis_x*self.vel, axis_y*self.vel, axis_rot)
            send_to_stm(new_command)

    def on_button_pressed(self, event: Button.Pressed) -> None:
        """Event handler called when a button is pressed."""
        if event.button.id == "start":
            self.send = True
            
        elif event.button.id == "stop":
            self.send = False
        
        elif event.button.id == "brake":
            self.add_class("braking")
            self.use_brake = False

        elif event.button.id == "no_brake":
            self.remove_class("braking")
            self.use_brake = True   
    
    def on_input_changed(self, event: Input.Changed) -> None:
        print(event.input.value)
        try:
            self.vel = float(event.input.value)
        except:
            self.vel = 0.0
    

def send_to_stm(to_send: agv_command):
    bytes_to_send = to_send.get_bytes()
    print(bytes_to_send)
    # ser.write(bytes_to_send) #if you want to directly send to STM
    msg = Steer()
    msg.data = bytes_to_send
    publisher.publisher_.publish(msg)
    # publisher.get_logger().info('Publishing: ' + str(msg.data)) #works but fucks shit up
    
def main(args=None):
    rclpy.init(args=args)
    global ser
    global publisher
    publisher = MinimalPublisher()
    app = MoteusApp()
    app.run()
    # ser = serial.Serial()
    # ser.port="/dev/ttyACM0"
    # ser.baudrate=115200
    # ser.open()
    # if ser.is_open:
    #     app = MoteusApp()
    #     app.run()

    # ser.close()

if __name__ == "__main__":
    main()
