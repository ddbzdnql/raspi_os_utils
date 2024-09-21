#!/bin/bash

# This is the script to be run by /xdg/autostart, NOT the script to be placed in init.d!

# Wait a while before attempting to execute the startup
sleep 2
~/scripts/carousel/bg_carousel &
   
exit 0 