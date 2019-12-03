#!/bin/bash
while true
do
	rosservice call /move_base/clear_costmaps
	sleep 3
done
