import sys
import os
import time
import serial

gamepad = open("/dev/hidraw0", 'rb')

reload = [1, 128, 128, 128, 128, 2, 240]
fire = [1, 128, 128, 128, 128, 32, 240]
backward = [1, 128, 128, 128, 128, 0, 64]
forward = [1, 128, 128, 128, 128, 0, 0]


out = []

ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

def equals(a, b):
    if len(a) == len(b):
        for i in range(len(a)):
            if a[i] != b[i]:
                return False
        return True
    return False


while 1:
    for caracter in gamepad.read(1):
        out += [caracter]
    if len(out) == 56:
        out = out[0:7]
        #print(out)
        if equals(out, reload) :
            print("RELOAD")
            ser.write("r".encode())
            time.sleep(3.5)
        elif equals(out, fire) :
            print("FIRE")
            ser.write("f".encode())
            time.sleep(0.5)
        elif equals(out, forward) :
            print("FORWARD")
            ser.write("g".encode())
        elif equals(out, backward) :
            print("BACKWARD")
            ser.write("b".encode())
        gamepad.close()
        time.sleep(0.3)
        os.system("echo null > /dev/hidraw0")
        gamepad = open("/dev/hidraw0", 'rb')
        out = []
