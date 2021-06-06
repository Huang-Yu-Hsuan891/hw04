import serial
import time
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

#s.write("/parkingcar/run 10 20 0 \n".encode())
#print("ok")
#time.sleep(15)
#while True:
#    char = s.read(200)
#    print(char.decode())
s.write("/parkingcar/run 20 14 0 \n".encode())
print("ok")
time.sleep(15)
    
s.close()

