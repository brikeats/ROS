# ROS
My ROS packages for raspberry pi-based robots. This assumes that you have a raspberry pi 2 with Ubuntu and ROS installed, and that you have a remote machine (e.g., a laptop) also running Ubuntu with ROS.

## Raspberry Pi Setup
[Create a static ip address](https://help.ubuntu.com/lts/serverguide/network-configuration.html)
by editing ` /etc/network/interfaces`.
From home directory, clone the workspace with `git clone https://github.com/brikeats/ROS.git` and build the workspace with `cd ROS/workspace` and `catkin_make && catkin_make install`.

## Laptop Setup
Add a line to `/etc/hosts` that indicates the pi's IP address, e.g., `192.168.0.104   raspberrypi`.
Setup up public key authentication. You're good to go when you can log on to the raspberry pi with the command `ssh raspberrypi`.
Ensure that the environmental variables `ROS_MASTER_URI` and `ROS_IP` are set as follows: 

`export ROS_MASTER_URI=http://raspberrypi:11311`
`export ROS_IP=`hostname -I`

I do this in my `.bashrc`. When you want to use ROS, you should run `source /opt/ros/indigo/setup.bash`. 

