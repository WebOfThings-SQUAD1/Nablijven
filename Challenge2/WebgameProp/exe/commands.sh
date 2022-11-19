#!/bin/bash


    
_pth=$(pwd)
cd ~/Room/Props/pyProps/WebgameProp/App


case "$1" in 
    'test')
        ./log succesfully-tested
        ;;
    'init')
        ./commands.sh server start
        ./commands.sh keys disable
        ./commands.sh kiosk start
        ;;
    'keys')
        case "$2" in 
            disable)
                xmodmap ./.Xmodmap-disable 
                ;;
            reset)
                xmodmap ./.Xmodmap-reset 
                ;;
            *)
                ./log -e "keys: $2";;
        esac 
        ;;

    'server')
        addrs=$(cat addrs.conf)
        case "$2" in 
            start)
                php -S $addrs -t . &> /dev/null &
                ./log "server is active";;
            stop)
                    sudo killall -9 php
                    ./log "killed all php";;
            status)
                    [[ $(curl -s --max-time 5 "http://$addrs" | wc -c) -gt 0 ]] && ./log active || ./log offline ;;
            open)
                    python -m webbrowser "http://$addrs"
                    ./log "opening server";;
            *)
                ./log -e "server: $2";;
        esac 
        ;;

    'kiosk')
        if [[ "$2" =~ ^(stop|start|status) ]]; then
            sudo systemctl $2 kiosk.service
            ./log "kiosk: $2" 
        elif [[ "$2" =~ ^(enable|disable) ]]; then
            echo "do not use these operations! it bugs the kiosk."
            ./log "kiosk (disbled option): $2" 
        else
            ./log -e "kiosk: $2"
        fi
        ;;

    *)
        ./log -e "cmd: $2";;
esac
cd $_pth


