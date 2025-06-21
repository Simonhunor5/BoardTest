import socket
import struct
import tkinter as tk
import threading
import time

TARGET_IP = '192.168.69.123'
TARGET_PORT = 7

def map_angle_to_pwm(angle):
    return int((angle / 180.0) * 2000 + 500)

def send_udp(pwm1, pwm2, pwm3):
    data = struct.pack('<hhh', pwm1, pwm2, pwm3)
    sock.sendto(data, (TARGET_IP, TARGET_PORT))
    print(f"Sent: {pwm1}, {pwm2}, {pwm3}")

def send_from_ui():
    try:
        angles = []
        for entry in entries:
            angle = int(entry.get())
            if not 0 <= angle <= 180:
                raise ValueError
            angles.append(angle)
        pwms = [map_angle_to_pwm(a) for a in angles]
        send_udp(*pwms)
    except ValueError:
        print("Invalid input: angles must be between 0 and 180")

looping = False
def loop_test():
    def run_loop():
        global looping
        looping = True
        direction = 1
        angle = 0

        while looping:
            for i in range(3):
                sliders[i].set(angle)
                entries[i].delete(0, tk.END)
                entries[i].insert(0, str(angle))
            send_from_ui()
            time.sleep(0.1)
            angle += direction
            if angle >= 180 or angle <= 0:
                direction *= -1

    threading.Thread(target=run_loop, daemon=True).start()


def stop_loop():
    global looping
    looping = False

def go_home():
    for i in range(3):
        entries[i].delete(0, tk.END)
        entries[i].insert(0, "90")
        sliders[i].set(90)
    send_from_ui()

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

root = tk.Tk()
root.title("Servo Control Panel")

labels = ['Roll (°)', 'Pitch (°)', 'Yaw (°)']
sliders = []
entries = []

for i, label in enumerate(labels):
    tk.Label(root, text=label).grid(row=i, column=0, padx=10, pady=5)

    entry_var = tk.StringVar(value="90")
    entry = tk.Entry(root, textvariable=entry_var, width=5)
    entry.grid(row=i, column=2)
    entries.append(entry)

    def slider_changed(val, idx=i):
        entries[idx].delete(0, tk.END)
        entries[idx].insert(0, str(int(float(val))))

    slider = tk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, length=200,
                      command=lambda val, idx=i: slider_changed(val, idx))
    slider.set(90)
    slider.grid(row=i, column=1)
    sliders.append(slider)

    def entry_updated(*args, idx=i):
        try:
            val = int(entry_var.get())
            if 0 <= val <= 180:
                sliders[idx].set(val)
        except ValueError:
            pass 

    entry_var.trace_add("write", entry_updated)


btn_send = tk.Button(root, text="Send", command=send_from_ui)
btn_send.grid(row=3, column=0, pady=10)

btn_loop = tk.Button(root, text="Start Loop Demo", command=loop_test)
btn_loop.grid(row=3, column=1)

btn_stop = tk.Button(root, text="Stop Loop", command=stop_loop)
btn_stop.grid(row=3, column=2)

btn_home = tk.Button(root, text="Home (90°)", command=go_home)
btn_home.grid(row=4, column=0, columnspan=3, pady=10)

root.protocol("WM_DELETE_WINDOW", lambda: [stop_loop(), root.destroy()])
root.mainloop()