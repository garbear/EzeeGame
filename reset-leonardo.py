#!/usr/bin/env python

import serial, sys

serialPort = '/dev/ttyACM1'

try:
    serialPort = sys.argv[1]
except:
    pass

ser = serial.Serial(port=serialPort, \
                    baudrate=1200, \
                    parity=serial.PARITY_NONE, \
                    stopbits=serial.STOPBITS_ONE, \
                    bytesize=serial.EIGHTBITS)

ser.isOpen()
ser.close()

