import serial
import json

RETRIES = 5


def send(ser_: serial.Serial, msg: bytes):
    if not ser_.isOpen():
        print("opening the port")
        ser_.open()
        error_code_ = b''
        while error_code_ == b'':
            error_code_ = ser.read(3)

    for retry in range(RETRIES):
        ser_.write(msg)
        error_code_ = ser_.read(3)
        if error_code_ != b'':
            return error_code_

        print(f"try {retry + 1}/{RETRIES}")

    print("message failed")


ser = serial.Serial()
with open("port.json", "r") as port_file:
    port_data = json.loads(port_file.read())
    ser.port = port_data['port']
    ser.baudrate = port_data['baudrate']
    ser.timeout = port_data['timeout']

if __name__ == '__main__':
    print(send(ser, b'u/'))
    print(send(ser, b'u/'))
    print(send(ser, b'u/'))
