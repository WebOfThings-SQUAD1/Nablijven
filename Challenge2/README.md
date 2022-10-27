# Challenge 2

Een raspberry PI die een statische login pagina host in [Kiosk Mode](https://pimylifeup.com/raspberry-pi-kiosk/).
Deze README kan ook worden gebruikt als help of troubleshooting pagina.

## Troubleshooting 
Local [address](./addrs.conf)
(if you try and hack me, I will find you, and unplug you)
```txt
192.168.50.20:8142
```

edit boot command
```sh
sudo crontab -e
```

Kiosk service config:
```sh
code /lib/systemd/system/kiosk.service
```

Kiosk star/boot conf:
```sh
code /home/pi/kiosk.sh
```
<br>

Normaal boot alles met de PI, maar in *[wcs](https://www.google.com/search?q=worst+case+scenario)* zijn de volgende [commando's](./commands.sh) zijn beschikbaar:



boot
```sh
cmd boot
```
Php Server

```sh
cmd server_start
cmd server_open
cmd server_stop
``` 
Kiosk
```sh
# Warning: "kiosk_disable" gaf onfixbare bug
cmd kiosk_start
cmd kiosk_stop
cmd kiosk_status

cmd kiosk_enable
cmd kiosk_disable
```
