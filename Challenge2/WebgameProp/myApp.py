#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
BlinkApp.py

Pygame BlinkApp extends ThreadingProp.
'''
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
GameApp.py

GameApp extends PropApp.

'''

from constants import *

from PropApp import PropApp
from PropData import PropData

import os, re, threading, time, yaml
if USE_GPIO and os.path.isfile('/opt/vc/include/bcm_host.h'):
    import RPi.GPIO as GPIO

import pygame
import subprocess



class MyApp(PropApp):

    #__________________________________________________________________
    def __init__(self, argv, client, debugging_mqtt=False):
        
        super().__init__(argv, client, debugging_mqtt)
        print("--inited")
    
    def run(self, arg):
        #subprocess.run([f'~/Room/Props/pyProps/WebgameProp/App/commands.sh {0}'.format(" ".join(args))], shell=True)
        subprocess.run(["~/Room/Props/pyProps/WebgameProp/App/commands.sh", arg], shell=True)
        
        
    #__________________________________________________________________ 
    def boot(self, keynote):
        try:
            print('--boot')


        
        except BaseException as e:
            self._logger.error("{} at {}: {}".format("Error", "boot", str(e)))
            
            
        ________________________________________________________
    def onConnect(self, client, userdata, flags, rc):
        print("connected")
        self.run('init')
        # for i in range(10):
            # sleep(1)
            # try:
                # print(1)
                # if self.publishMessage:
                    # self.publishMessage(self._mqttOutbox, "DISCONNECTED FREEEDOOOM YEAAAH ")
                    # exit
            # except:
                # pass
        # extend as a virtual method
        pass
        
        
        
    #__________________________________________________________________
    def onDisconnect(self, client, userdata, rc):
        # extend as a virtual method
        self.publishMessage(self._mqttOutbox, "DISCONNECTED FREEEDOOOM YEAAAH ")
        print('disconnected')
        pass
        

    #__________________________________________________________________
    def onMessage(self, topic, message):
        print('doesnt work mate')
        return
        # extend as a virtual method
        #print(topic, message)
        if message == "app:test":
            self.run('test')
            pass
        elif message == "app:start":
            self.publishMessage(self._mqttOutbox, "start NANI DESUKA NADEBAYO ")
            pass
        elif message == "app:startup":
            self.publishMessage(self._mqttOutbox, " stqtup NANI DESUKA NADEBAYO ")
            pass
        else:
            self.run(message)
             
             
#         elif message == "app:data":
#             super.publishAllData()
#             self.publishMessage(self._mqttOutbox, "DONE " + message)
#         elif message.startswith("setup:1"):
#             
#             except Exception as e:
#                 self._logger.debug(e)
#                 self.publishMessage(self._mqttOutbox, "MESG " + message +"-->" + e)
#             self.publishMessage(self._mqttOutbox, "DONE " + message)
#         else
#             self.publishMessage(self._mqttOutbox, "OPTION NOT AVAILABLE " + message)
#         

    #__________________________________________________________________
    def publishAllData(self):
        
        while True:
            try:
                super()._publishAllData()
            except:
                pass
            finally:
                time.sleep(3)

    #__________________________________________________________________
    def publishDataChanges(self):

        while True:
            try:
                super()._publishDataChanges()
            except:
                pass
            finally:
                time.sleep(30)
    

