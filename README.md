# multi-robot-ros
multi_robot ROS-Melodic package

Multi Robot Simulation package for turtlebot3. This is for **Simultaneously Multi Robot Path Planning** project at Robotics & A.I. Lab.(RAIL, Kwangwoon University).

---

# Environment
- Ubuntu 18.04
- ROS Melodic

---

# Intallation
- [turtlebot3_simulations](https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git)
- turtlebot3
- turtlebot3_msgs

```bash
# go to your workspace
$ cd ~/catkin_ws/src

$ git clone -b melodic-devel https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git
$ sudo apt install ros-melodic-turtlebot3
$ sudo apt install ros-melodic-turtlebot3-msgs
```

And now clone this repository to your catkin_ws/src.
```bash
$ git clone https://github.com/msjun23/multi_robot.git
```

---

# Usage
Only main.launch is what you have to launch. Then you can see two turtlebot3 burgers.

```bash
$ roslaunch multi_robot main.launch
```

![img1](/images/img1.png)
