# ROS
My ROS packages for raspberry pi-based robots. This assumes that you have a raspberry pi 2 with Ubuntu and ROS installed, and that you have a remote machine (e.g., a laptop) also running Ubuntu with ROS.

## Laptop Setup

I installed as per the ROS website in Ubuntu 16.04. I added `source /opt/ros/kinetic/setup.bash` to my .bashrc.

Running `catkin_make` on this workspace is giving me `ImportError`s for `catkin_pkg`, even though I had apt installed the packages and PYTHONPATH is pointing to `/opt/ros/kinetic/lib/dist...`. Had to `pip install --user catkin_pkg`.

Next I'm getting `ImportError: No module named em`, so do `pip install --user empy`. Then I can build workspace okay.

When I try to run one of my nodes, I get  `ImportError: No module named 'rospkg'`. This is because of miniconda -- when it is installed, it adds itself to the beginning of the `PATH` in my `.bashrc`. I commented out this line in `~/.bashrc`, and it seems to be working okay.

To use the kinect, `sudo apt install ros-kinetic-openni-launch`.

To allow for arbitrary user to use maestro servo controller, `sudo adduser <user_name> dialout` and reboot.



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
Make sure you have all of the dependencies installed for the packages in this repo by `rosdep install --from-paths ROS/workspace/src/ --ignore-src`
