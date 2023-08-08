#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

using namespace std::chrono_literals;
using std::placeholders::_1;

class ObstacleAvoidance : public rclcpp::Node
{
public:

  ObstacleAvoidance()
  : Node("obstacle_avoidance")
  {
    
    subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>("scan", 10, std::bind(&ObstacleAvoidance::laser_callback, this, _1));
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    timer_ = this->create_wall_timer(500ms, std::bind(&ObstacleAvoidance::timer_callback, this));
 
  }

private:
  float front_laser;
  float left_laser;
  float right_laser;
  float obstacle_distance=0.80;
  void timer_callback()
  {
    auto vel = geometry_msgs::msg::Twist();
     if ((front_laser > obstacle_distance && right_laser>obstacle_distance && left_laser>obstacle_distance)||
     (right_laser<obstacle_distance && left_laser<obstacle_distance)) {
        vel.linear.x = 0.2;
        vel.angular.z = 0;
        RCLCPP_INFO(this->get_logger(), "move front: %f \n",front_laser);
        }

     if (front_laser < obstacle_distance || right_laser <= obstacle_distance) {
      vel.linear.x = 0.0;
      vel.angular.z = 0.2;
      RCLCPP_INFO(this->get_logger(), "move left: %f \n",left_laser);

    }

     if (left_laser <= obstacle_distance) {
      vel.linear.x = 0.0;
      vel.angular.z = -0.2;
      RCLCPP_INFO(this->get_logger(), "move right: %f \n",right_laser);
    }
    
    publisher_->publish(vel);
  }

  void laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
  {
    front_laser=msg->ranges[0];
    left_laser=msg->ranges[90];
    right_laser=msg->ranges[270];

    // RCLCPP_INFO(this->get_logger(), "laser front: %f \n",front_laser);
    // RCLCPP_INFO(this->get_logger(), "laser right: %f \n",right_laser);
    // RCLCPP_INFO(this->get_logger(), "laser left: %f \n",left_laser);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ObstacleAvoidance>());
  rclcpp::shutdown();
  return 0;
}