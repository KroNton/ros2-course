#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/srv/my_custom_service_message.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <iostream>

using namespace std::chrono_literals;
using MyCustomServiceMessage = custom_interfaces::srv::MyCustomServiceMessage;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("movement_client");
  rclcpp::Client<MyCustomServiceMessage>::SharedPtr client =
    node->create_client<MyCustomServiceMessage>("movement");

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto request = std::make_shared<MyCustomServiceMessage::Request>();
  request->move = "Turn Right";

  auto result_future = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result_future) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    auto result = result_future.get();
    if (result->success == true)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service returned success");
    }
    else if (result->success == false)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service returned false");
    }
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service /moving");
  }

  rclcpp::shutdown();
  return 0;
}