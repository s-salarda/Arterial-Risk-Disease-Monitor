from tkinter import *
import random
import time
import serial
import numpy as np

ser = serial.Serial('COM4', 9600)

write_duration = 120

# Get the start time
start_time = time.time()

# Open the file outside the loop
with open('data_replace.txt', 'w') as f:
    # Your code to collect and process data goes here
    while time.time() - start_time < write_duration:
        while True:
            # Read data from serial
            data = ser.readline().decode().strip()

            if data:
                # Write data to file
                f.write(data + '\n')
                break

ser.close()

for i in range(3, 0, -1):
    time.sleep(1)
 

with open('data_replace.txt', 'r') as file:
    # Read the entire contents of the file
    lines = file.readlines()

# Extract data from lines
# Filter out lines with either two periods or a value greater than 200 or less than 70 because sometimes the arduino drops numbers or doesn't jump to next line
filtered_lines = [line for line in lines if line.count('.') != 2 and not any(float(value) > 400 for value in line.split()) and not any(float(value) < 70 for value in line.split())]

with open('data_filtered.txt', 'w') as file:
    # Write the filtered lines back to the file
    file.writelines(filtered_lines)

with open('data_filtered.txt', 'r') as file:
    new_lines = file.readlines()

data_filtered = np.array([float(line.strip()) for line in new_lines]) 

t_step = 1 / 118.55
max_index = 14226

# Generate time array
t = np.arange(0, max_index) * t_step

# Generate frequency range
freq_range = np.fft.fftfreq(max_index, t_step)

# Compute FFT
v_freq = np.fft.fft(data_filtered, max_index)

# Compute magnitude spectrum
v_mag = 2 * np.abs(v_freq) ** 2 / max_index ** 2

# Compute area under the curve using trapezoidal rule
area = np.trapz(v_mag[:max_index//2], freq_range[:max_index//2])

print("Area under the curve:", area)


def change_color(area):
    # Determine color based on risk level
    risk_level = (area - 183.00)*100/3
    if area < 183.85:
        color = "green"
    elif area < 185.00:
        color = "yellow"
    elif area < 200.00:
        color = "red"
    else:
        color = "white"
    
    # Change color of the rectangle
    canvas.itemconfig(rectangle, fill=color)

    risk_label.config(text=f"Risk Level: {risk_level:.2f}%")
    
    # Disable the "Run" button after it is pressed
    b1.config(state=DISABLED)
    
    # Enable the "Refresh" button
    b2.config(state=NORMAL)

def close_window():
    window.destroy()

def generate_random_risk():
    if i > 1:
        area = 201
    else:
        # Change the color based on the generated area
        area = np.trapz(v_mag[:max_index//2], freq_range[:max_index//2])
        change_color(area)


window = Tk()

s1=Label(window, text="   ", font=20)
s1.grid(row=0, column=0)

s2=Label(window, text="  ", font=20)
s2.grid(row=0, column=2)

s3=Label(window, text="   ", font=20)
s3.grid(row=0, column=4)

s4=Label(window, text="   ", font=12)
s4.grid(row=5, column=0)

l1=Label(window, text="Arterial Disease Risk Monitor", font=20)
l1.grid(row=0,column=1)

risk_label = Label(window, text="Risk Level:", font=20)
risk_label.grid(row=1, column=1)

canvas = Canvas(window, width=150, height=80)
canvas.grid(row=3, column=1, columnspan=2)

rectangle = canvas.create_rectangle(0, 0, 150, 150, fill="white")

b1 = Button(window, text="Run", font=20, width=12, command=generate_random_risk)
b1.grid(row=0, column=3)

b2 = Button(window, text="Refresh", font=20, width=12, command=generate_random_risk, state=DISABLED)
b2.grid(row=1, column=3)

b3 = Button(window, text="Close", font=20, width=12, command=close_window)
b3.grid(row=4, column=3)

window.mainloop()