#!/bin/bash
xset s noblank
xset s off
xset -dpms

unclutter -root &

sed -i 's/"exited_cleanly":false/"exited_cleanly":true/' /home/pi/.config/chromium/Default/Preferences
sed -i 's/"exit_type":"Crashed"/"exit_type":"Normal"/' /home/pi/.config/chromium/Default/Preferences

#adrs=$(echo "http://"$(~/webgame/commands.sh get address))
#adrs="http://127.0.0.1:9919"
adrs="http://localhost:9919/"
/usr/bin/chromium-browser --kiosk --noerrdialogs --enable-features=OverlayScrollbar --disable-restore-session-state --disable-infobars $adrs &





# while true; do
#    xdotool keydown ctrl+Next; xdotool keyup ctrl+Next;
#    sleep 10
# done
