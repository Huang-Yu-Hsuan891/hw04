import serial
import time
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

s.write("/parkingcar/run 10 10 1 \n".encode())
print("ok")
time.sleep(1)
#while True:
#    char = s.read(200)
#    print(char.decode())
    
s.close()

