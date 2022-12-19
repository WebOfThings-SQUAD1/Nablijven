#!/bin/bash

exit 0
    
_pth=$(pwd)
#cd $(dirname "$0")
cd ~/webgame


case "$1" in 
    'test')
        echo test-succes
        ./log succesfully-tested
        ;;
    'keys')
        case "$2" in 
            disable)
                ./disablekeys
                ./log "keys disabled"
                ;;
            reset)
                echo naat
                exit 0
                xmodmap ./.Xmodmap-reset 
                ./log "keys reset"
                ;;
            *)
                ./log -e "keys: $2";;
        esac 
        ;;

    'server')
        addrs=$(cat addrs.conf)
        case "$2" in 
            start)
                #python3 ../gameApp/server_app.py &> /dev/null &
                cd ~/webgame/app
                node app.js &
                #echo pid
                #echo node_pid
                #echo node_pid | grep -Eo '[0-9]{1,4}' > nodepid.conf
                ./log "server is active";;
            stop)
                killall node
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
    'get')
        if [[ "$2" == 'address' ]]; then
            cat addrs.conf
        fi
        ;;

    *)
        ./log -e "cmd: $2";;
esac
cd $_pth



