#!/usr/bin/env bash
xterm -e roslaunch chefbot_bringup driver.launch &
sleep 5
xterm -e roslaunch chefbot_bringup twist.launch

#xterm -e roslaunch chefbot_bringup multi_driver.launch &
#sleep 5
#xterm -e roslaunch chefbot_bringup multi_twist.launch
