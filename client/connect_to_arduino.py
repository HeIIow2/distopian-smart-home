import serial
import json

RETRIES = 5

LOOK_AT_ME=[60,50,180,50]

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

def up(ser_: serial.Serial, n: bytes):
    return send(ser_, b'u'+n)

def down(ser_: serial.Serial, n: bytes):
    return send(ser_, b'd'+n)

def set_angle(ser_: serial.Serial, motor: bytes, angle: bytes):
    return send(ser_, b's'+motor+angle)

def set_position(ser_: serial.Serial, angles: tuple):
    pass


ser = serial.Serial()
with open("port.json", "r") as port_file:
    port_data = json.loads(port_file.read())
    ser.port = port_data['port']
    ser.baudrate = port_data['baudrate']
    #ser.timeout = port_data['timeout']

if __name__ == '__main__':
    while True:
        motor, angle = input("m, a").split(",")
        motor = int(motor).to_bytes(1, "big")
        if motor == b'':
            motor = b'\x00'
        angle = int(angle).to_bytes(1, "big")
        if angle == b'':
            angle = b'\x00'
        print(set_angle(ser, motor, angle))

