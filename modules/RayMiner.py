import pyautogui, time, threading
from ChargeModule import Charge
from WayBackToHome import *

OnCharging = False
y = 0

def Mine():
    while True:
        if OnCharging == False:
            pyautogui.mouseDown()
            pyautogui.keyDown('d')
        time.sleep(0.03)

def FlushKeys():
    pyautogui.mouseUp()
    pyautogui.keyUp("d")

def Charging():
    global OnCharging, y
    while True:
        time.sleep(150)
        OnCharging = True
        FlushKeys()
        time.sleep(1)
        
        Charge()
        time.sleep(15)
        Charge()
        time.sleep(100)

        y -= 100
        print("current Y: ", y)
        ComebackToHome()
        pyautogui.move(0, y)
        OnCharging = False

time.sleep(5)

t2 = threading.Thread(target=Mine, args=())
t3 = threading.Thread(target=Charging, args=())

t2.start()
t3.start()
