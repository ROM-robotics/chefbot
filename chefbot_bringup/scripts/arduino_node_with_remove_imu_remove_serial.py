#!/usr/bin/env python

'''

Arduino_node.py - Receive sensor values from Arduino board and publish as topics

Created September 2014

Copyright(c) 2014 Lentin Joseph

Some portion borrowed from  Rainer Hessmer blog
http://www.hessmer.org/blog/

edited by ko su san(ghostman)
'''

#Python client library for ROS
import rospy
import sys
import time
import math

#This module helps to receive values from serial port
from SerialDataGateway import SerialDataGateway
#Importing ROS data types
from std_msgs.msg import String
from geometry_msgs.msg import Vector3Stamped
from chefbot_bringup.msg import rpm
#Importing ROS data type for IMU
from sensor_msgs.msg import Imu

#Class to handle serial data from Arduino and converted to ROS topics
class Arduino_Class(object):

	def __init__(self):
		print "Initializing Arduino Class"

#######################################################################################################################
		#Sensor variables
		self.req_right_ = 0
		self.req_left_ = 0

		self.actual_right = 0 # vector x
		self.actual_left = 0  # vector y
		self.time_ = 0.0        # time difference

		self.gyro_X = 0.0
		self.gyro_Y = 0.0
		self.gyro_Z = 0.0
		self.accel_X= 0.0
		self.accel_Y= 0.0
		self.accel_Z= 0.0

		self._Counter=0



		self.vector3 = Vector3Stamped()
#######################################################################################################################
		#Get serial port and baud rate of Tiva C Arduino
		port = rospy.get_param("~port", "/dev/ttyACM0")
		baudRate = int(rospy.get_param("~baudRate", 115200))

#######################################################################################################################
		rospy.loginfo("Starting with serial port: " + port + ", baud rate: " + str(baudRate))
		#Initializing SerialDataGateway with port, baudrate and callback function to handle serial data
		self._SerialDataGateway = SerialDataGateway(port, baudRate,  self._HandleReceivedLine)
		rospy.loginfo("Started serial communication")


#######################################################################################################################
#Subscribers and Publishers

		self._Req_subscriber = rospy.Subscriber('rpm_req_msg',rpm,self._Handle_rpm_request)

		self._Act_publisher = rospy.Publisher('rpm_act_msg',Vector3Stamped,queue_size = 10)
		#self._Imu_publisher = rospy.Publisher('mpu9250_imu',Imu,queue_size=10)
		#self._SerialPublisher = rospy.Publisher('serial', String,queue_size=10)



#######################################################################################################################
	def _Handle_rpm_request(self, msg):
		self.req_right_ = msg.req_right
		self.req_left_  = msg.req_left

		speed_message = '%d,%d,%d \r' %(int(1),int(self.req_right_),int(self.req_left_))
		#speed_message = '%d,%d %d,%d \r' %(int(2),int(self.req_right_),int(3),int(self.req_left_))
		self._WriteSerial(speed_message)




#######################################################################################################################
#Calculate orientation from accelerometer and gyrometer

	def _HandleReceivedLine(self,  line):
		self._Counter = self._Counter + 1
		#self._SerialPublisher.publish(String(str(self._Counter) + ", in:  " + line))
		#rospy.loginfo("hello1")

		if(len(line) > 0):
			#rospy.loginfo("hello2")
			lineParts = line.split(',')
			li = lineParts
			ros_time = rospy.Time.now()
			try:
				#rospy.loginfo("Try")
				if(li[0] == '5'):
					self.actual_right = float(li[1])
					self.actual_left = float(li[2])
					self.time_  = float(li[3])
					#rospy.loginfo(self.time_)
					#rospy.loginfo("oK i got actual rpm")

					self.vector3.header.stamp = ros_time
					self.vector3.vector.x = self.actual_right
					self.vector3.vector.y = self.actual_left
					self.vector3.vector.z = self.time_
					self._Act_publisher.publish(self.vector3)

				# if(li[0] == '6'):
				# 	self.gyro_X = float(li[1])
				# 	self.gyro_Y = float(li[2])
				# 	self.gyro_Z = float(li[3])
				# 	self.acce_X = float(li[4])
				# 	self.acce_Y = float(li[5])
				# 	self.acce_Z = float(li[6])
				# 	#rospy.loginfo("oK i got imu")


			except:
				#rospy.logwarn("Error in Sensor values")
				rospy.loginfo("exception!")
				pass



#######################################################################################################################


	def _WriteSerial(self, message):
		#self._SerialPublisher.publish(String(str(self._Counter) + ", out: " + message))
		self._SerialDataGateway.Write(message)

#######################################################################################################################


	def Start(self):
		rospy.logdebug("Starting")
		self._SerialDataGateway.Start()

#######################################################################################################################

	def Stop(self):
		rospy.logdebug("Stopping")
		self._SerialDataGateway.Stop()



if __name__ =='__main__':
	rospy.init_node('arduino_ros',anonymous=False)
	Arduino = Arduino_Class()
	try:

		Arduino.Start()
		rospy.spin()
	except rospy.ROSInterruptException:
		rospy.logwarn("Error in main function")


	#Arduino.Reset_Arduino()
	Arduino.Stop()

#######################################################################################################################
