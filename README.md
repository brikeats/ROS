# ROS
My ROS packages.

## Laptop Setup

These instructions assume a laptop running Ubuntu 16.04, and that the laptop and robot are connected to the same wifi router.

I installed as per the ROS website in Ubuntu 16.04. I added `source /opt/ros/kinetic/setup.bash` to my .bashrc.

I've had problems using ROS with anaconda -- ROS wants to use the system python. I removed the automatically-inserted anaconda lines from my `.bashrc`, so that I can use ROS. I copied them into a separate script that I can source if I want to actually use conda.

When I want to run ROS locally, I source a file with the following contents:

```
source /opt/ros/kinetic/setup.bash
source ~/robotics_code/ROS/workspace/devel/setup.bash
export ROS_MASTER_URI=http://localhost:11311/
export ROS_IP="$(ip route get 8.8.8.8 | awk '{print $NF; exit}')"
```

To use the kinect, `sudo apt install ros-kinetic-openni-launch`.

To allow for arbitrary user to use maestro servo controller, `sudo adduser <user_name> dialout` and reboot.


## Robot setup

I'm currently using an nvidia TX2 as my robot's brain. Stup instructions are [in the wiki](https://github.com/brikeats/ROS/wiki/TX2-Setup).

When I want to run ROS on the TX2 and visualize it locally in `rqt`, I source a file with the following contents:

```
source /opt/ros/kinetic/setup.bash
source ~/robotics_code/ROS/workspace/devel/setup.bash
export ROS_MASTER_URI=http://tx2:11311/
export ROS_IP="$(ip route get 8.8.8.8 | awk '{print $NF; exit}')"
```

i.e., you need to set `ROS_MASTER_URI=http://tx2:11311/`.