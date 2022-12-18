
# the game


Make sure the following folder structure is respected.

```
home/pi
├── initgame.sh
├── kiosk.sh
└── webgame
    ├── addrs.conf
    ├── app
    │   ├── app.js
    │   ├── ...
    │   └── src
    ├── commands 2.sh
    ├── commands.sh
    ├── disablekeys
    ├── info
    │   ├── install.sh
    │   └── kiosk_troubleshooting.txt
    ├── log
    ├── logs.log
    └── README.md
```

## setup
Original tutorial: https://pimylifeup.com/raspberry-pi-kiosk


### 1. Or follow minimal ionstructions (without creating a service):
```
sudo apt purge wolfram-engine scratch scratch2 nuscratch sonic-pi idle3 -y
sudo apt purge smartsim java-common minecraft-pi libreoffice* -y
sudo apt clean
sudo apt autoremove -y
sudo apt update
sudo apt upgrade
sudo apt install xdotool unclutter sed

// enable auto login: "System Options" > "boot /Auto Login"
sudo raspi-config
```

### 2. Now make sure ~/initgame.sh and ~/webagme/disablekeys are executable
```
sudo chmod +x ~/initgame.sh 
sudo chmod +x ~/webgame/disablekeys
```

### 3. options to  run the ~/initgame.sh at boot
-a) place it at end of: `/etc/rc.local` (did not always work, for some reason)
-b) use LXDE:
```
sudo nano  ~/.config/lxsession/LXDE-pi/autostart
@lxpanel --profile LDXE-pi
@pcmanfm --desktop --profile LDXE-pi
@xscreensaver -no-splash

@xset s off
@xset s noblank
@xset -dpms

@sh /home/pi/initgame.sh
```

### 4.set static ip `192.168.50.20`
-a) /etc/dhcdpcd.conf
```
# Example static IP configuration:
interface wlan0
static_routers=192.168.50.1
static domain_name_servers=192.168.1.1
statis ip_address=192.168.50.20/24
```

-b) add vai UI: right-click WIFI at desktop. Add in (only) static ip at WLAN0,
make sure 'auto fill empty space' (i dont remeber exactly) is checked.

-c) crontab -e

### EXTRA: Attemps Disableling Chromium shortcuts 
-a) edit xdg file (does not really do anything)
```
sudo nano /etc/xdg/openbox/lxde-pi-rc.xml
```
Commment, remove or nullify  all <keyboard> tags

```
...
  <keyboard>
    <chainQuitKey>C-g</chainQuitKey>
    <!-- Keybindings for desktop switching -->
    <keybind key="C-A-Left">
...
```
-b) Lauch chromium with flag (not tested)
	maybe use: --app-launch-url-for-shortcuts-menu-item 
	src: https://peter.sh/experiments/chromium-command-line-switches/
