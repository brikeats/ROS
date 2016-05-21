# ROS
My ROS packages for raspberry pi-based robots. This assumes that you have a raspberry pi 2 with Ubuntu and ROS installed, and that you have a remote machine (e.g., a laptop) also running Ubuntu with ROS.

## Raspberry Pi Setup
[Create a static ip address](https://help.ubuntu.com/lts/serverguide/network-configuration.html)
by editing ` /etc/network/interfaces`.

Several of the devices require sudo access -- you need to be able to run sudo commands without being prompted for the password. This can be accomplished by `sudo visudo -f /etc/sudoers.d/90-cloudimg-ubuntu` and adding a line like `<your username> ALL=(ALL) NOPASSWD:ALL` to the end.

Make sure your enviromental variable are set correctly by adding the following to your `.bashrc`:
```
source /opt/ros/indigo/setup.bash
export ROS_MASTER_URI=http://raspberrypi:11311
export ROS_IP=`hostname -I`
```

## Laptop Setup
Add a line to `/etc/hosts` that indicates the pi's IP address, e.g., `192.168.0.104   raspberrypi`.
Setup up public key authentication -- you're good to go when you can log on to the raspberry pi with the command `ssh raspberrypi`. You can then copy the code, build, and install it on the pi by running the install script, `./install`.

Add the same lines to your `.bashrc`:
```
source /opt/ros/indigo/setup.bash
export ROS_MASTER_URI=http://raspberrypi:11311
export ROS_IP=`hostname -I`
```
