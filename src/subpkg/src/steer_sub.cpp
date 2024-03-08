#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/steer.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<interfaces::msg::Steer>(
      "tui_steering", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const interfaces::msg::Steer & msg) const{
        std::ostringstream convert;
        for (int a = 0; a < 19; a++) {
            convert << (int)msg.data[a];
        }
        std::string msg_string = convert.str();       
        RCLCPP_INFO(this->get_logger(),"I heard '%s'", msg_string.c_str());
    }
    rclcpp::Subscription<interfaces::msg::Steer>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}