#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "tuw_multi_robot_msgs/RobotGoalsArray.h"

void goalsCallback(const tuw_multi_robot_msgs::RobotGoalsArray& goal_arr)
{
  ROS_INFO("I heard: [%f]", goal_arr.robots.at(0).destinations.at(0).position.x);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "multi_goals_listener");

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/goals", 1000, goalsCallback);
  ros::spin();

  return 0;
}
