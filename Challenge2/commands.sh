#!/bin/bash
_pth=$(pwd)
cd ~/Desktop


log()(
  echo $1
  echo "$(date +"%D %H:%M"):  $1" >> ~/Desktop/logs.log
)


case "$1" in
      boot)
        # wait for network
        time_elapsed=0
        max_time=10
        log "waiting for network..."

        while [ "$(hostname -I)" = "" ]; do
          if [ $time_elapsed -gt $max_time ]; then
            log "ERR - Network timeout. exitting.."
            ./commands.sh kiosk_stop
            exit 1
          fi
          #echo -en .
          ((time_elapsed++))
          sleep 10
        done


        ./commands.sh server_start
        ./commands.sh kiosk_enable
        log "boot complete"
        #sudo systemctl start kiosk.service
        ;;

    server_start)
        addrs=$(cat addrs.conf)
        php -S $addrs -t challenge_02_game &> /dev/null &
        log "server is active"
        ;;
    server_open)
        addrs=$(cat addrs.conf)
        python -m webbrowser "http://$addrs"
        log "opening server"
        ;;

      server_stop)
        sudo killall -9 php
        log "killed all php"

        ;;

      kiosk_start)
        sudo systemctl start kiosk.service
        log "kiosk start"
        ;;

      kiosk_stop)
        sudo systemctl stop kiosk.service
        log "kiosk stopped"
        ;;
        
      kiosk_enable)
        sudo systemctl enable kiosk.service
        log "kiosk enabled"
        ;;

      kiosk_disable)
        sudo systemctl disable kiosk.service
        log "kiosk disabled"
        ;;

      kiosk_status)
        sudo systemctl status kiosk.service
        log "kiosk checked status"
        ;;

      *)
        log "command not found: $1"
        ;;
esac

cd $_pth
