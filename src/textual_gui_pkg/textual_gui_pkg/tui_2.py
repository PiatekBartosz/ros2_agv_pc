from typing import Any, Coroutine
from textual.app import App, ComposeResult
from textual.containers import ScrollableContainer
from textual.events import Key
from textual.widgets import Button, Footer, Header, Static, Input, Label
import math
import struct
import serial

class agv_command:
    # type = 0x01
    # id = 0x0c
    # mode = 0x03    0x01 for movement, 0x03 for stop, 0x02 for brake
    pos = math.nan
    # vel = -5.0
    trq = 0.0
    acc = math.nan

    def __init__(self, type, id, mode, var_1 = 0x00, var_2 = 0x00):
        self.type = type
        self.id = id
        self.mode = mode
        if(type == 0x01):
            self.vel = var_1
        elif(type == 0x00):
            self.x_v = var_1
            self.y_v = var_2

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
            ba_yv = bytearray(struct.pack("f", self.y_v)) 
            byte_array = ba_arb+ba_pos+ba_vel+ba_xv+ba_yv
        return byte_array
    
class Motor(Static):
    vel = 0.0
    motor_id = 0x00
    """A stopwatch widget."""
    def compose(self) -> ComposeResult:
        yield Label("Motor "+str(self.id),id="MotorHead")
        yield Button("Start", id="start", variant="success")
        yield Input(placeholder="type desired velocity",id="vel_input",type="number")
        yield Button("Stop", id="stop", variant="error")
        yield Button("Brake", id="brake", variant="primary")

    def on_button_pressed(self, event: Button.Pressed) -> None:
        """Event handler called when a button is pressed."""
        
        if event.button.id == "start":
            print("starting")
            print(self.vel)
            print(hex(int(self.id[1:])))
            out_command = agv_command(0x01,int(self.id[1:]),0x01,self.vel)
            send_to_stm(out_command)
            
        elif event.button.id == "stop":
            print("stopping")
            print(self.vel)
            print(hex(int(self.id[1:])))
            out_command = agv_command(0x01,int(self.id[1:]),0x03,self.vel)
            send_to_stm(out_command)
        
        elif event.button.id == "brake":
            print("braking")
            print(self.vel)
            print(hex(int(self.id[1:])))
            out_command = agv_command(0x01,int(self.id[1:]),0x04,self.vel)
            send_to_stm(out_command)
    
    def on_input_changed(self, event: Input.Changed) -> None:
        print(event.input.value)
        try:
            self.vel = float(event.input.value)
        except:
            self.vel = 0.0
    
    def on_key_pressed(self, event: Key) -> None:
        print(event.key)
        print("dupa")

class MoteusApp(App):

    CSS_PATH = "/workspaces/ros_agv_pc/src/textual_gui_pkg/textual_gui_pkg/moteus_app.tcss"
    BINDINGS = [("d", "toggle_dark", "Toggle dark mode")]

    def compose(self) -> ComposeResult:
        """Create child widgets for the app."""
        yield Header()
        yield Footer()
        yield ScrollableContainer(Motor(id="d10"),Motor(id="d11"),Motor(id="d12"),Motor(id="d13"))

    def action_toggle_dark(self) -> None:
        """An action to toggle dark mode."""
        self.dark = not self.dark

def send_to_stm(to_send: agv_command):
    bytes_to_send = to_send.get_bytes()
    if ser.is_open:
        ser.write(bytes_to_send)
        print(bytes_to_send)
    

def main():
    ser = serial.Serial()
    ser.port="/dev/ttyACM0"
    ser.baudrate=115200
    ser.open()
    if ser.is_open:
        app = MoteusApp()
        app.run()

    ser.close()


if __name__ == '__main__':
    main()
