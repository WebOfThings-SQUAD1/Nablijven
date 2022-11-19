# Challenge 2


The game.
A simple Javascript game, locally hosted with Flask in [Kiosk Mode](https://pimylifeup.com/raspberry-pi-kiosk/).

<style>
.warn{
    border: 2px solid #1115;
    padding:1rem;
    margin:1rem 0;
    border-radius:1rem;
    color: #fff;
    transition:all 0.2s;
}
.warn:before{
    content: 'Warning: '
}
.warn:hover{
    filter:brightness(2)
}
h1:hover::after{
    content: '#'
}
h2:hover::after{
    content: '#'
}
</style>


## Usage
1. **Folderstructure:**
Place the `Room` folder in your home directory eg. ~/pi. <br>
A good habbit is to place `WebgameProp` in the following folder structure. <br>
The full folderstructure with examples can be found at [github-pyProps](https://github.com/xcape-io/PyProps)

Changing the folder structure will only require changing some minor imports.


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

<div class="warn">Make sure to follow instruction at the [example](https://github.com/xcape-io/PyProps)</div>

2. **Alias:**
If you wnat to use the `cmd` command, <br>
you need to make an alias in `~/.bashrc` to the `commands.sh` file.

Use one of the following commands:
```bash
sudo echo -e "\nalias cmd='~/Room/Props/pyProps/WebgameProp/exe/commands.sh'" >> ~/.bashrc
# or
# and add: 
# alias cmd='~/Room/Props/pyProps/WebgameProp/exe/commands.sh' 
# at the end of the file
sudo nano ~/.bashrc


```
## install
volg de nodige instalaties ./install.sh



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

ps: if [code](https://code.visualstudio.com/docs/editor/command-line) command is not available use [`sudo nano`](https://linuxize.com/post/how-to-use-nano-text-editor/) instead.
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
# WARNING: you can also enable/disable kiosk mode. But this gave an unfixable bug. So don't.
```

disable keys ([xmodmap](https://wiki.archlinux.org/title/xmodmap))
``` bash
cmd disablekeys
```
