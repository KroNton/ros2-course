#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
using std::placeholders::_1;

class OdomSubscriber : public rclcpp::Node
{
public:
  // Initiate a Node called 'simple_subscriber'
  OdomSubscriber()
  : Node("odom_subscriber")
  {
    // Create a Subscriber object that will listen to the /counter topic and will call the 'topic_callback' function       // each time it reads something from the topic
    subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
      "odom", 10, std::bind(&OdomSubscriber::odom_callback, this, _1));
  }

private:

  void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
  {
  
    RCLCPP_INFO(this->get_logger(), "x position: %f ",msg->pose.pose.position.x);
  }
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OdomSubscriber>());
  rclcpp::shutdown();
  return 0;
}