#!/usr/bin/env python

import sys
import rospy
from servo_driver.srv import set_speed


def set_servo_speed(servo_num, speed):
    # blocks until service is available
    rospy.wait_for_service('set_speed')
    try:
        set_speed_service = rospy.ServiceProxy('set_speed', set_speed)
        response = set_speed_service(servo_num, speed)
        return response.response
    except rospy.ServiceException, e:
        print "Service call failed: %s" % e


def usage():
    return "%s [servo_number] [speed]" % sys.argv[0]


if __name__ == "__main__":

    if len(sys.argv) == 3:
        servo_num = int(sys.argv[1])
        speed = float(sys.argv[2])
    else:
        print usage()
        sys.exit(1)

    print "Requesting servo speed %.f for servo %i" % (speed, servo_num)
    print "Waiting for service..."
    print "Service response: %s" % set_servo_speed(servo_num, speed)