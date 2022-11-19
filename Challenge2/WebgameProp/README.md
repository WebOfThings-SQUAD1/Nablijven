# Challenge 2


The game.
A simple Javascript game, locally hosted with Flask in [Kiosk Mode](https://pimylifeup.com/raspberry-pi-kiosk/).


## Usage
1. **Folderstructure:**
Place the `Room` folder in your home directory ~/Room. <br>
A good habbit is to place `WebgameProp` in the following folder structure. <br>
The full folderstructure with examples can be found at [github-pyProps](https://github.com/xcape-io/PyProps)

INFO ℹ️: Changing the folder structure will only require changing some minor imports.


```bash
Room
└── Props
    ├── assets
    ├── core
    ├── help
    └── pyProps
        └── WebgameProp
            ├── App
            │   └── ...
            └── info
```

INFO ℹ️: Make sure to follow instruction at the [example](https://github.com/xcape-io/PyProps)

2. **Alias:**
To enable the `cmd` command<br>
a good practice is to make an alias in `~/.bashrc` to `commands.sh`.

(why alias? Handy while editing. Importing would need a new terminal to refresh the content)

Use one of the following commands:
```bash
sudo echo -e "\nalias cmd='~/Room/Props/pyProps/WebgameProp/exe/commands.sh'" >> ~/.bashrc
# OR
sudo nano ~/.bashrc
# scroll to the bottom and add the following line:
alias cmd='~/Room/Props/pyProps/WebgameProp/exe/commands.sh' 
# press ctrl-s and press ctrl-x



```
## install
volg de nodige instalaties `./info/install.sh`



## Troubleshooting 
The local address of the app can be found [here](./addrs.conf).


edit boot command
```sh
sudo crontab -e
```

Kiosk service config:
```sh
code /lib/systemd/system/kiosk.service
```

Kiosk star/boot conf:
(actions kiosk undertakes when booting)
```sh
code /home/pi/kiosk.sh
```

INFO ℹ️: if [code](https://code.visualstudio.com/docs/editor/command-line) command is not available use [sudo nano](https://linuxize.com/post/how-to-use-nano-text-editor/) instead.
<br>


Normally everything start with boot but in *[wcs](https://www.google.com/search?q=worst+case+scenario)* you can follow the following [commads](./commands.sh):



initialize: server & kiosk
```sh
cmd init
```

Server
```sh
cmd server start
cmd server stop
cmd server open
``` 
Kiosk
```sh
cmd kiosk start
cmd kiosk stop
cmd kiosk status
# INFO ℹ️: you can also enable/disable kiosk mode. But this gave an unfixable bug. So don't!
```

control keys ([xmodmap](https://wiki.archlinux.org/title/xmodmap))
``` bash
cmd keys disable
cmd keys reset
```
