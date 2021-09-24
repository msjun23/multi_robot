#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "actionlib_msgs/GoalStatusArray.h"

#include <string>

using namespace std;

string move_base_result = "";
geometry_msgs::PoseStamped goal_pose;

float goals_candidates[4][4] = {{1.68499982357, 1.23999977112, -0.702918877371, 0.711270027371}, 
                                {1.57499933243, -1.57000017166, 0.999979457047, -0.00640979589535}, 
                                {-1.65902221203, -1.37128508091, 0.716363792356, 0.697726964508}, 
                                {-1.50893461704, 1.60989642143, -0.0123320998138, 0.999923956766}}; // up left -> up right -> down right -> down left

void move_baseStateSubscribe(const actionlib_msgs::GoalStatusArray& move_base_status)
{
  if (move_base_status.status_list.empty()) {
    ROS_INFO("Start");
    ros::NodeHandle pub_node;
    ros::Publisher goal_pub = pub_node.advertise<geometry_msgs::PoseStamped>("test_goal", 1000);
    goal_pub.publish(goal_pose);
  }
  else {
    move_base_result = move_base_status.status_list.front().text;
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "goal_pub");

  ros::NodeHandle pub_node;
  ros::Publisher goal_pub = pub_node.advertise<geometry_msgs::PoseStamped>("test_goal", 1000);

  ros::NodeHandle sub_node;
  ros::Subscriber sub = sub_node.subscribe("/move_base/status", 1000, move_baseStateSubscribe);
  
  int goal_num = 0;
  goal_pose.header.frame_id = "map";

  goal_pose.pose.position.x = 1.68499982357;
  goal_pose.pose.position.y = 1.23999977112;
  goal_pose.pose.position.z = 0;

  goal_pose.pose.orientation.x = 0;
  goal_pose.pose.orientation.y = 0;
  goal_pose.pose.orientation.z = -0.702918877371;
  goal_pose.pose.orientation.w = 0.711270027371;

  bool run_flag = true;
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    if (run_flag && move_base_result == "Goal reached.") {
      run_flag = false;

      goal_num++;
      if (goal_num >= 4) {
        goal_num = 0;
      }
      ROS_INFO("%d", goal_num);
      
      goal_pose.pose.position.x = goals_candidates[goal_num][0];
      goal_pose.pose.position.y = goals_candidates[goal_num][1];
      goal_pose.pose.orientation.z = goals_candidates[goal_num][2];
      goal_pose.pose.orientation.w = goals_candidates[goal_num][3];
      goal_pub.publish(goal_pose);
    }
    else if (!run_flag && move_base_result != "Goal reached.") {
      run_flag = true;
    }

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
