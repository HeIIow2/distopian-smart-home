import serial
import json

ser = serial.Serial()
with open("port.json", "r") as port_file:
    port_data = json.loads(port_file.read())
    ser.port = port_data['port']
    ser.baudrate = port_data['baudrate']
    ser.timeout = port_data['timeout']
    ser.open()

if ser.isOpen():
    error_code = b''
    while error_code == b'':
        error_code = ser.read(3)

    print(ser)
    ser.write(b'u/')
    error_code = b''
    while error_code == b'':
        error_code = ser.read(3)
    print(error_code)
    ser.close()
