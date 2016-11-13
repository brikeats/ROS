# ROS
My ROS packages for raspberry pi-based robots. This assumes that you have a raspberry pi 2 with Ubuntu and ROS installed, and that you have a remote machine (e.g., a laptop) also running Ubuntu with ROS.

## Raspberry Pi Setup
[Create a static ip address](https://help.ubuntu.com/lts/serverguide/network-configuration.html)
by editing ` /etc/network/interfaces`. Go to router's admin page and set DHCP settings to always assign the correct ip address to the pi, identified by its MAC address -- the `HWaddr` in output of `ifconfig`. (I think the MAC address is actually associated with the usb dongle.)

Make sure your enviromental variable are set correctly by adding the following to your `.bashrc`:
```
source /opt/ros/indigo/setup.bash
export ROS_MASTER_URI=http://raspberrypi:11311
export ROS_IP=`hostname -I`
```

You will need to add this both to your user's .bashrc, as well as to root's (`/root/.bashrc`). You can then run `sudo -i` to get an sudo shell with ROS setup called. As root, source the workspace setup file, e.g., `source /home/brian/ROS/workspace/devel/setup.bash`, and then start the motor driver with `roslaunch motor_driver motors.launch`. 

I haven't been able to figure out how to use the `sudo` command with the launch file (with or without passwordless sudo); if I can get it set up correctly with `sudo`, then I can set up passwordless sodu and I can add the node to a launch file like `<node pkg="motor_driver" type="motor_driver" name="motor_driver" launch-prefix="sudo"/>`.

## Laptop Setup
Add a line to `/etc/hosts` that indicates the pi's IP address, e.g., `192.168.0.104   raspberrypi`.
Set up up public key authentication -- you're good to go when you can log on to the raspberry pi with the command `ssh raspberrypi`. You can then copy the code, build, and install it on the pi with `rsync -a ROS/ raspberrypi:~/ROS`.

Add the same lines to your laptop `.bashrc`:
```
source /opt/ros/indigo/setup.bash
export ROS_MASTER_URI=http://raspberrypi:11311
export ROS_IP=`hostname -I`
```
