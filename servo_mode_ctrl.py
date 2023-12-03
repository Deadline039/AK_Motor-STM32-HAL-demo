import tkinter as tk
from tkinter.constants import ACTIVE, LEFT

import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
serial_ports = []
for port, desc, hwid in sorted(ports):
    serial_ports.append(port)
    print("{}: {} [{}]".format(port, desc, hwid))

# root window
root = tk.Tk()
root.geometry('600x600')
root.resizable(False, False)
root.title('AK Servo Mode Controller')

# slider current value
value_position = tk.DoubleVar()
value_speed = tk.DoubleVar()
value_current = tk.DoubleVar()

# we need a global var to operate on serial
ser = None


def slider_position_changed(event):
    # print("Current position: " + '{: .2f}'.format(value_position.get()))
    sendData(mode=0)


def slider_speed_changed(event):
    # print("Current speed: " + '{: .2f}'.format(value_speed.get()))
    sendData(mode=1)


def slider_current_changed(event):
    # print("Current kp: " + '{: .2f}'.format(value_kp.get()))
    sendData(mode=2)


def connectClick():
    global ser
    ser = serial.Serial(serial_list.get(ACTIVE), 115200)
    label_info.config(text='Connected', fg='green')


def setOriginClick():
    if ser.is_open:
        print("set origin")
        ser.write(bytes("origin\r\n", encoding='utf-8'))


def generateSlider(min, max, init_val, val, func):
    slider = tk.Scale(
        root,
        from_=min,
        to=max,
        length=500,
        orient='horizontal',
        resolution=0.01,
        variable=val
    )
    slider.bind('<ButtonRelease-1>', func)
    slider.set(init_val)
    return slider


def sendData(mode):
    if ser.is_open:
        if mode == 0:
            # position
            prepared_payload = '{: .2f},{: .2f},{: .2f}\r\n'.format(
                value_position.get(), 0, 0
            )
        elif mode == 1:
            # speed
            prepared_payload = '{: .2f},{: .2f},{: .2f}\r\n'.format(
                0, value_speed.get(), 0
            )
        elif mode == 2:
            # current
            prepared_payload = '{: .2f},{: .2f},{: .2f}\r\n'.format(
                0, 0, value_current.get()
            )

        print(prepared_payload)
        ser.write(bytes(prepared_payload, encoding='utf-8'))


def readFromSerial():
    if ser is not None:
        if ser.in_waiting:
            rep = ser.readline()
            rep = rep.decode("utf-8")
            print(rep)
            rep = rep.strip().split(',')
            if (len(rep) == 5):
                label_position.config(text='Position: ' + rep[0])
                label_speed.config(text='Speed: ' + rep[1])
                label_current.config(text='Current: ' + rep[2])
                label_temp.config(text='Temperature: ' + rep[3])
                label_error.config(text='Error code: ' + rep[4])

    root.after(10, readFromSerial)


frame1 = tk.Frame(root, pady=10)
serial_list = tk.Listbox(frame1, height=5, width=50)
for i in range(len(serial_ports)):
    serial_list.insert(i, serial_ports[i])
serial_list.pack(side=LEFT)
tk.Button(frame1, text='Connect', padx=20, command=connectClick).pack(side=LEFT)

value_origin = tk.Button(frame1, text='Set Origin', command=setOriginClick).pack(side=LEFT)

frame1.pack()
label_info = tk.Label(root, text='Choose the serial port and click connect', padx=20, pady=5)
label_info.pack()

# label for the slider
tk.Label(root, text='Position:', pady=5).pack()
slider_position = generateSlider(-360, 360, 0, value_position, slider_position_changed)
slider_position.pack()

tk.Label(root, text='Speed:', pady=5).pack()
slider_speed = generateSlider(-100000, 100000, 0, value_speed, slider_speed_changed)
slider_speed.pack()

tk.Label(root, text='Current:', pady=5).pack()
slider_kp = generateSlider(-60000, 60000, 0, value_current, slider_current_changed)
slider_kp.pack()

frame2 = tk.Frame(root)
label_position = tk.Label(frame2, text='Position:', padx=15, pady=30)
label_position.pack(side=LEFT)
label_speed = tk.Label(frame2, text='Speed:', padx=15)
label_speed.pack(side=LEFT)
label_current = tk.Label(frame2, text='Current:', padx=15)
label_current.pack(side=LEFT)
label_temp = tk.Label(frame2, text='Temperature:', padx=15)
label_temp.pack(side=LEFT)
label_error = tk.Label(frame2, text='Error code:', padx=15)
label_error.pack(side=LEFT)

frame2.pack()

root.after(10, readFromSerial)
root.mainloop()
