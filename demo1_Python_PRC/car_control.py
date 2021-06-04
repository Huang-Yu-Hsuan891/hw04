import serial
import time
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

s.write("/parkingcar/run 5 5 1 \n".encode())
time.sleep(1)
s.close()

