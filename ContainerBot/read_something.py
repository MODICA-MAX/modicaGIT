from gerbil.gerbil import Gerbil
import serial

#ser_bytes = ser.readline()
#print(ser_bytes)


accessPort = 'COM6'
buadRate = 115200
try:
    ArduinoConnect = serial.Serial(accessPort, buadRate, timeout=4)
    print("connected to serial port: {} at rate: {}".format(accessPort, buadRate))
except:
    print("connection to serial port: {} failed".format(accessPort))


