#!/usr/bin/env python3
import rclpy
import time
from rclpy.node import Node
from rclpy.action import ActionClient
from my_action_interfaces.action import CountUntil
from rclpy.action.client import ClientGoalHandle
class CountUntilClientNode(Node): 
    
    def __init__(self):
        super().__init__("count_until_client_node")
        self.count_until_client_=ActionClient(self,CountUntil,"count_until")
        self.get_logger().info("Action Client has been started")
        self.action_goal=CountUntil.Goal()

    def send_goal(self):
        
        self.count_until_client_.wait_for_server()
        
        #Set request to goal
        self.action_goal.target_number=10
        self.action_goal.period =2.0
        self.count_until_client_. \
        send_goal_async(self.action_goal).\
        add_done_callback(self.goal_response_callback)
        
        
    def goal_response_callback(self,future):

        self.goal_handle_:ClientGoalHandle = future.result()

        if self.goal_handle_.accepted:
            self.goal_handle_.get_result_async().add_done_callback(self.get_result_callback)
        else:
            self.get_logger().info('Goal rejected :(')
            return
    
    def get_result_callback(self,future):
        result = future.result().result
        self.get_logger().info('Goal result: ' + str(result.reached_number) )
        

def main(args=None):
    rclpy.init(args=args)
    node = CountUntilClientNode() 
    node.send_goal()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()