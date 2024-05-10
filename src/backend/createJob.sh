#!/bin/bash




# Start Xvfb with display number 99 and screen size 1920x1080x24
Xvfb :99 -screen 0 1920x1080x24 &
XVFB_PID=$!

# Set DISPLAY environment variable to use the virtual display
export DISPLAY=:99

/home/anoozh/Desktop/Operating-System/Project/PMM/Process-Monitoring-and-Management/src/backend/create_cronjob.o "$1" "$2"


# Terminate Xvfb when done
kill $XVFB_PID
