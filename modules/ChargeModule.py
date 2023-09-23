import pyautogui, time
from WayBackToHome import *

def Charge():
    text = "t/spawn"
    for i in text:
        pyautogui.press(i)
        time.sleep(0.05)
    pyautogui.press("enter")
    time.sleep(4)

    
    pyautogui.keyDown('shiftleft')
    time.sleep(0.1)
    pyautogui.keyUp('shiftleft')

    pyautogui.keyDown('w')
    time.sleep(0.3)
    pyautogui.keyUp("w")

    pyautogui.click(button="right")
    time.sleep(2)
    
    pyautogui.moveTo(1370, 330)
    pyautogui.dragTo(1370, 480, 1, button='left')
    time.sleep(0.5)

    pyautogui.click(1200, 777, button="left")
    time.sleep(4)

    pyautogui.keyDown('d')
    time.sleep(0.9)
    pyautogui.keyUp("d")

    pyautogui.keyDown('s')
    time.sleep(0.2)
    pyautogui.keyUp("s")
    
    if __name__ == "__main__":
        exit(0)

if __name__ == "__main__":
    Charge()

# 1370 330
# 1370 470
# 1200, 777
# 1.1, 0.25
