import time 
import os
import subprocess
import keyboard
from pyKey import pressKey, releaseKey, press, sendSequence, showKeys
import pyautogui
import matplotlib.pyplot as plt
import pandas as pd

#open the application
fd = os.open('C:\Users\salar\Downloads\CoolTermWin64Bit\CoolTermWin64Bit\CoolTerm.exe', os.O_RDONLY)
time.sleep(5)
pyautogui.click(200,75)
time.sleep(2)
pyautogui.click(200,450)
time.sleep(2)
pyautogui.click(600,470)
time.sleep(2)
pyautogui.doubleClick(250,320)
pyautogui.click(200,100)
# pyautogui.keyDown('ctrl')
# pyautogui.keyDown('k')
# pyautogui.keyUp('k')
# pyautogui.keyUp('ctrl')

time.sleep(5)

#DataFrame
data1 = []
with open(r'C:\Users\salar\Downloads\sketch_feb11a\transducer\CoolTerm_Data.txt') as data:
     for line in data:
            data = line.split()
            data = list(map(int,data))
            data1.append(data)
            
df = pd.DataFrame(data1)
df.columns = ['Time' , 'Pressure','Frequency']
df.to_csv('data.csv', index = False, header = False )
print(df)

# # graph the plots way
# df.plot(x = 'Pressure', y = 'Frequency', kind = "line", marker = 'o', c='g', figsize = (10,15))
# df.plot(x = 'Time', y = 'Frequency', kind = "line", marker = 'o', c='g', figsize = (10,15))
# df.plot(x = 'Time', y = 'Pressure', kind = "line", marker = 'o', c='g', figsize = (15,15))

# plt.show() 


with open(r'C:\Users\salar\Downloads\sketch_feb11a\transducer\CoolTerm_Data.txt', 'w+') as file:
    file.seek(0)