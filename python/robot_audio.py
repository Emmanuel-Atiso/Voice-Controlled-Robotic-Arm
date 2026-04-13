import serial
import time

PORT = "COM3"
BAUD = 9600

print("Opening port...")
ser = serial.Serial(PORT, BAUD, timeout=2)
time.sleep(3)

print("Connected.")
print("Commands:")
print("LEFT_SMALL, LEFT, LEFT_MORE")
print("RIGHT_SMALL, RIGHT, RIGHT_MORE")
print("DOWN_SMALL, DOWN, DOWN_MORE")
print("UP_SMALL, UP, UP_MORE")
print("OPEN, CLOSE, RESET")
print("PICK, DROP")
print("You can also type things like: RIGHT 3 or UP_SMALL 2")
print("Type Q to quit")

while True:
    user_input = input(">> ").strip().upper()

    if user_input == "Q":
        break

    parts = user_input.split()

    if len(parts) == 2 and parts[1].isdigit():
        cmd = parts[0]
        count = int(parts[1])
    else:
        cmd = user_input
        count = 1

    for _ in range(count):
        ser.write((cmd + "\n").encode())
        print("Sent:", cmd)
        time.sleep(0.2)

ser.close()
print("Done.")