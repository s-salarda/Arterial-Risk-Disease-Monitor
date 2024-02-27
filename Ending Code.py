import time 
import os
import subprocess
import keyboard
from pyKey import pressKey, releaseKey, press, sendSequence, showKeys
import pyautogui
import matplotlib.pyplot as plt
import pandas as pd

fd = os.popen(r'C:\Users\salar\Downloads\CoolTermWin64Bit\CoolTermWin64Bit\CoolTerm.exe')
time.sleep(5)
pyautogui.keyDown('ctrl')
pyautogui.keyDown('k')
pyautogui.keyUp('k')
pyautogui.keyUp('ctrl')

time.sleep(10)

#DataFrame
f = open(r'C:\Users\salar\Downloads\sketch_feb11a\transducer\CoolTerm_Data.txt')
df = pd.read_csv(f, header = None, sep = " ", names=  ['time', 'pressure', 'frequency'])
print(df)
df.to_excel('data.excel', index = False)

# graph the plots way 1
x = []
y = []
for line in f: 
    lines = [i for i in line.split()]
    x.append(lines[0])
    y.append(int(lines[1]))
    
plt.title("Pressure vs. Frequency")
plt.xlabel('Pressure')
plt.ylabel('Frequency')
plt.yticks(y)
plt.plot(x, y, marker = 'o', c = 'g')

# graph the plots way 2
df.plot(x = 'pressure', y = 'frequency', kind = "line", marker = 'o', c='g', figsize = (10,15))
df.plot(x = 'time', y = 'frequency', kind = "line", marker = 'o', c='g', figsize = (10,15))
df.plot(x = 'time', y = 'pressure', kind = "line", marker = 'o', c='g', figsize = (10,15))

plt.show() 



with open("example.txt",'r+') as file:
    file.truncate(0)