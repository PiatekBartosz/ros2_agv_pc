#include <cstdio>

#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/steer.hpp"
using std::placeholders::_1;

class STMSubscriber : public rclcpp::Node
{
  void cl() { close(serial_port);};
  public:
    
    int serial_port;

    STMSubscriber()
    : Node("steering_subscriber"){

      //connecting to STM32 via USB
      serial_port = open("/dev/ttyACM0", O_RDWR);
      struct termios tty;

      // Read in existing settings, and handle any error
      if(tcgetattr(serial_port, &tty) != 0) {
          printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));

      }
      tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
      tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
      tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
      tty.c_cflag |= CS8; // 8 bits per byte (most common)
      tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
      tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

      tty.c_lflag &= ~ICANON;
      tty.c_lflag &= ~ECHO; // Disable echo
      tty.c_lflag &= ~ECHOE; // Disable erasure
      tty.c_lflag &= ~ECHONL; // Disable new-line echo
      tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
      tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
      tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

      tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
      tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
      // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
      // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

      tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
      tty.c_cc[VMIN] = 19;

        // Set in/out baud rate to be 115200
      cfsetispeed(&tty, B115200);
      cfsetospeed(&tty, B115200);

      // Save tty settings, also checking for error
      if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
          printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      }

      //creating subscriber and callback
      subscription_ = this->create_subscription<interfaces::msg::Steer>(
      "tui_steering", 10, std::bind(&STMSubscriber::topic_callback, this, _1));
    }
  private:
    void topic_callback(const interfaces::msg::Steer & msg) const{
        std::ostringstream convert;
        for (int a = 0; a < 19; a++) {
            convert << (int)msg.data[a];
        }
        std::string msg_string = convert.str();       
        RCLCPP_INFO(this->get_logger(),"I heard '%s'", msg_string.c_str()); //this can be removed
        uint8_t arr[19];
        //msg is a custom data structure and it reads as a vector. we need to convert it to array to send to STM
        copy(msg.data.begin(),msg.data.end(),arr);

        write(serial_port, arr, 19);
    }
    rclcpp::Subscription<interfaces::msg::Steer>::SharedPtr subscription_;
};


int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<STMSubscriber>());
  rclcpp::shutdown();

  return 0;
}
