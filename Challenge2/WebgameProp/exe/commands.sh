#!/bin/bash


    
_pth=$(pwd)
cd $(dirname "$0")


case "$1" in 
    'test')
        ./log succesfully-tested
        ;;
    'init')
        0$ server start
        0$ keys disable
        0$ kiosk start
        ;;
    'keys')
        case "$2" in 
            disable)
                ./disablekeys
                # xmodmap ./.Xmodmap-disable 
                ;;
            reset)
                echo naat
                exit 0
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
                python3 ../gameApp/server_app.py &> /dev/null &
                ./log "server is active";;
            stop)
                    pkill -9 Python
                    ./log "server stopped";;
            status)
                    [[ $(curl -s --max-time 5 "http://$addrs" | wc -c) -gt 0 ]] && ./log active || ./log offline ;;
            open)
                    python3 -m webbrowser "http://$addrs"
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



