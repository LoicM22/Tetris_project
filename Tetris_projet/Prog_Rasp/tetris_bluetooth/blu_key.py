import serial
import pygame
from pynput.keyboard import Key, Controller

keyboard = Controller()

bluetoothSerial = serial.Serial("/dev/rfcomm0",baudrate=9600)
print("Bluetooth connected")
try:
    while 1:
        data=bluetoothSerial.readline()
        print(data)

        if data==b'gauche\r\n':
            print("aller a gauche")
            #key = "g"
            keyboard.press(Key.left)
            keyboard.release(Key.left)
        if data==b'droite\r\n':
            print("aller a droite")
            #key = "j"
            keyboard.press(Key.right)
            keyboard.release(Key.right)
        if data==b'bas\r\n':
            print("aller en bas")
            key = "h"
            keyboard.press(key)
            keyboard.release(key)
        if data==b'rotleft\r\n':
            print("rotation a gauche")
            key = "s"
            keyboard.press(key)
            keyboard.release(key)
        if data==b'rotright\r\n':
            print("rotation a droite")
            key = "w"
            keyboard.press(key)
            keyboard.release(key)
        
except KeyboardInterrupt:
    print("Quit")
