# src: https://pimylifeup.com/raspberry-pi-kiosk/

# install php
if [[ "$1" == "php" ]]; then
    sudo apt install lsb-release
    curl https://packages.sury.org/php/apt.gpg | sudo tee /usr/share/keyrings/suryphp-archive-keyring.gpg >/dev/null
    echo "deb [signed-by=/usr/share/keyrings/suryphp-archive-keyring.gpg] https://packages.sury.org/php/ $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/sury-php.list
    sudo apt update

    # adding repository
    sudo apt-add-repository ppa:ondrej/php
    sudo apt update

    # install php
    sudo apt install php8.1-cli

fi

# setup raspi config
if [[ "$1" == "setup" ]]; then
    sudo apt clean
    sudo apt autoremove -y
    sudo apt update
    sudo apt upgrade
    sudo apt install xdotool unclutter sed
    sudo raspi-config
fi

# Writing the Raspberry Pi Kiosk Script
if [[ "$1" == "write" ]]; then
    echo -
fi

# Setting up the Raspberry Pi Kiosk to start at boot
if [[ "$1" == "boot" ]]; then
    echo "display:   $DISPLAY"
    echo "edit file in code:"
    sudo nano /lib/systemd/system/kiosk.service

fi



