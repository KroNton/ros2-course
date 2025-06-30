#include <kinematics_examples/simple_turtlesim_kinematics.hpp>


SimpleTurtlesimKinematics::SimpleTurtlesimKinematics(const std::string &name) :Node(name)
{
    turtle1_pose_sub_=this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, 
        std::bind(&SimpleTurtlesimKinematics::turtle1PoseCallback,this,_1));

    turtle2_pose_sub_=this->create_subscription<turtlesim::msg::Pose>("/turtle2/pose", 10, 
        std::bind(&SimpleTurtlesimKinematics::turtle2PoseCallback,this,_1));

}


void SimpleTurtlesimKinematics::turtle1PoseCallback(const turtlesim::msg::Pose &msg){

        last_turtle1_pose_= msg;

        RCLCPP_INFO(this->get_logger(), 
        "turtle1_pose:\n"
        "  x: %.2f\n"
        "  y: %.2f\n"
        "  theta: %.2f\n"
        "  linear_velocity: %.2f\n"
        "  angular_velocity: %.2f",
        msg.x, msg.y, msg.theta, 
        msg.linear_velocity, msg.angular_velocity);

}

void SimpleTurtlesimKinematics::turtle2PoseCallback(const turtlesim::msg::Pose &msg){

        last_turtle2_pose_= msg;

        RCLCPP_INFO(this->get_logger(), 
        "turtle2_pose:\n"
        "  x: %.2f\n"
        "  y: %.2f\n"
        "  theta: %.2f\n"
        "  linear_velocity: %.2f\n"
        "  angular_velocity: %.2f",
        msg.x, msg.y, msg.theta, 
        msg.linear_velocity, msg.angular_velocity);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimpleTurtlesimKinematics>("simple_turtlesim_kinematics"));
  rclcpp::shutdown();
  return 0;
}