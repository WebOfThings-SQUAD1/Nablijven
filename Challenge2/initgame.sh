#!/bin/bash

### Webgame init file
### Booted by /etc/rc.local




cd ~/webgame

# await network connection
./log "awaiting network.."
conntimeout=0
while [ "$(hostname -I)" = "" ]; do
	if [[ $conntimeout -gt 100 ]];
	then
		./log -e "network  connection timeout!"
		exit 2
	fi
	sleep 1
	((conntimeout++))
done
./log 'Network enable'


# Start kisok mode
bash /home/pi/kiosk.sh &
./log "load kiosk"


# starting node js app

cd app
node app.js &
bash ../log "node js active"

# disable keys
./disablekeys &
./log "keys disabled"
