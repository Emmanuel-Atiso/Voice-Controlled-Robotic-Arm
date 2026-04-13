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
print("UP")
print("OPEN, CLOSE, RESET")
print("PICK, DROP")
print("PHOTO_POSE")
print("Type Q to quit")

while True:
    cmd = input(">> ").strip().upper()

    if cmd == "Q":
        break

    ser.write((cmd + "\n").encode())
    print("Sent:", cmd)

ser.close()
print("Done.")