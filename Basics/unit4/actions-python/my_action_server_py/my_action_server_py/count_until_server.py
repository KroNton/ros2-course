#!/usr/bin/env python3
import rclpy
import time
from rclpy.node import Node
from rclpy.action import ActionServer
from my_action_interfaces.action import CountUntil
from rclpy.action.server import ServerGoalHandle
class CountUntilServerNode(Node): 
    def __init__(self):
        super().__init__("count_until_server_node")
        self.count_intil_server_=ActionServer(self,CountUntil,"count_until",
                                              self._execute_cb)
        self.get_logger().info("Action server has been started")

    def _execute_cb(self,goal_handle:ServerGoalHandle):
        #Get request from goal
        target= goal_handle.request.target_number
        period= goal_handle.request.period

        self.get_logger().info("Executing the goal")
        counter=0
        for i in range(target):
            counter +=1
            self.get_logger().info(str(counter))
            time.sleep(period)

        goal_handle.succeed()
        result=CountUntil.Result()
        result.reached_number = counter
        return result

def main(args=None):
    rclpy.init(args=args)
    node = CountUntilServerNode() 
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()