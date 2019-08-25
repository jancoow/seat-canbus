from reprint import output
import time
import random
import serial

print("start the output")
ser = serial.Serial(port='/dev/ttyUSB0',baudrate=9600)

while True:
    line = ser.readline().decode("UTF-8")
    msg = line.split(':')
    if len(msg) == 2:
        if msg[0] == "5C1":
            print(msg[1])
#
# with output(output_type='dict', sort_key=lambda x:x[0], interval=0) as output_lines:
#     while True:
#         line = ser.readline().decode("UTF-8")
#         msg = line.split(':')
#         if len(msg) == 2:
#             if msg[0] == " 5C1:":
#                 output_lines[msg[0]] = msg[1]