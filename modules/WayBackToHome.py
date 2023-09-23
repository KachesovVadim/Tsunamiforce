import pyautogui, time

def ComebackToHome():
    text = "t/home t"
    for i in text:
        pyautogui.press(i)
        time.sleep(0.05)
    pyautogui.press("enter")
    time.sleep(2)