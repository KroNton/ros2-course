
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='exercise_pkg',
            executable='exercise_node',
            output='screen'),
    ])