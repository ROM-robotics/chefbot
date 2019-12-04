#!/bin/bash
while true
do
	rosservice call /move_base/clear_costmaps
        echo "cleared"
	sleep 1
        
done
