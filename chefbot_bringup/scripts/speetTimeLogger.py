#!/usr/bin/env python

import rospy
import sys
import time
import matplotlib.pyplot as plt
from geometry_msgs.msg import Vector3Stamped

right_motor_speed = []
left_motor_speed = []
time_duration = []

def callback(data):
  x = data.vector.x
  y = data.vector.y
  t = data.vector.z

  right_motor_speed.append(x)
  left_motor_speed.append(y)
  time_duration.append(t)


def showPlot():
  plt.plot(right_motor_speed,time_duration, label="Motor Right")
  plt.plot(left_motor_speed,time_duration,label="Motor Left")


  

plt.show()
def logger():
  rospy.init_node("speedTimeLogger", anonymous=False)
  sub = rospy.Subscriber("rpm_act_msg",Vector3Stamped, callback)
  plt.xlabel("Time")
  plt.ylabel("Rpm")
  plt.title("Speed Time Graph\n")
  plt.legend()
  plt.show()
  
  rospy.spin()

  



if __name__ == "__main__":
  logger()
