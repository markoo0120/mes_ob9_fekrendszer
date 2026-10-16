from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='mes_ob9_fekrendszer',
            executable='radar_node',
            name='radar_node',
            output='screen'
        ),
        Node(
            package='mes_ob9_fekrendszer',
            executable='brake_node',
            name='brake_node',
            output='screen'
        )
    ])