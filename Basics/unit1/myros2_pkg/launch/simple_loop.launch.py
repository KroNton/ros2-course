
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='myros2_pkg',
            executable='simple_node_loop',
            output='screen'),
    ])