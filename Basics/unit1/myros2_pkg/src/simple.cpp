
// Import the rclcpp client library
#include "rclcpp/rclcpp.hpp"

int main(int argc, char *argv[]) {
  // Initialize the ROS2 communication
  rclcpp::init(argc, argv);

  // Create a ROS2 node named ObiWan
  auto node = rclcpp::Node::make_shared("ObiWan");

  // Print a message to the terminal
  RCLCPP_INFO(node->get_logger(),
              "Help me Obi-Wan Kenobi, you're my only hope");

  // Shutdown the ROS2 communication
  rclcpp::shutdown();
  return 0;
}