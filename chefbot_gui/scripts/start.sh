#!/usr/bin/env bash
xterm -e roslaunch chefbot_bringup driver.launch &

sleep 3

python launch.py
