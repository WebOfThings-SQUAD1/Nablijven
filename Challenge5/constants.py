#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
constants.py

Contains all the application constants. As a rule all constants are named in all caps.
'''

APPLICATION = "Nablijven"

PYPROPS_CORELIBPATH = '../../core'

USE_GPIO = True

#__________________________________________________________________
# Required by PropApp
CONFIG_FILE = '.config.yml'

MQTT_DEFAULT_HOST = '192.168.50.45' #ip lorenzogh
MQTT_DEFAULT_PORT = 1883
MQTT_DEFAULT_QoS = 0  # usually 2 but client blocks is packet loiss so try 1 (maybe 0 like Yun is safer)

# try 5 seconds cause of wifi
MQTT_KEEPALIVE = 15 # 15 seconds is default MQTT_KEEPALIVE in Arduino PubSubClient.h

#__________________________________________________________________
# Required by App
CHALLENGE = "webgame" # enter custom name...

