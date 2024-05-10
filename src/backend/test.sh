#!/bin/bash

# Start Xvfb
Xvfb :99 -screen 0 1200x400x24 &

# Set the display environment variable
export DISPLAY=:99

# Launch Google Chrome with the desired URL
/usr/bin/google-chrome

# Stop Xvfb
killall Xvfb

