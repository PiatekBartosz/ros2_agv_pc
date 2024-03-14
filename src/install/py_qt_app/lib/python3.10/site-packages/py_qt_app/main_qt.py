import sys

# Qt5
from PyQt5.QtWidgets import QApplication, QWidget, QLabel
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot

# ROS2
import rclpy
from rcply.node import Node 

class Window():
   def __init__(self):
      app = QApplication(sys.argv)
      widget = QWidget()

      textLabel = QLabel(widget)
      textLabel.setText("Hello World!")
      textLabel.move(110,85)

      widget.setGeometry(50,50,320,200)
      widget.setWindowTitle("PyQt5 Example")
      widget.show()
      sys.exit(app.exec_())
      
def main(args=None):
   rclpy.init(args=args)
   window = Window()
   rclpy.shutdown()


if __name__ == '__main__':
   main()