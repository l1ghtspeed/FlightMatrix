#!/bin/bash
cd /home/pi/FlightMatrix/backend && node app.js &
cd /home/pi/FlightMatrix/src && ./main &
