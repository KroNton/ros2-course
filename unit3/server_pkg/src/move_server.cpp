
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/empty.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include <memory>

using Empty = std_srvs::srv::Empty;
using std::placeholders::_1;
using std::placeholders::_2;

class ServerNode : public rclcpp::Node
{
public:
  ServerNode()
  : Node("service_moving")
  {

    srv_ = create_service<Empty>("moving", std::bind(&ServerNode::moving_callback, this, _1, _2));
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

  }

private:
  rclcpp::Service<Empty>::SharedPtr srv_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

  void moving_callback(
      const std::shared_ptr<Empty::Request> request,
      const std::shared_ptr<Empty::Response>
          response) 
    {

        auto message = geometry_msgs::msg::Twist();
        message.linear.x = 0.2;
        message.angular.z = 0.2;
        publisher_->publish(message);
    }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ServerNode>());
  rclcpp::shutdown();
  return 0;
}