# distopian-smart-home

## Serial communications to the Arduino

### motors

- motor; description; range
- M0; base; 0 - 180
- M1; shoulder; 15 - 165
- M2; elbow; 0 - 180
- M3; vertical wrist; 0 - 180
- M4; rotation wrist; 0 - 180
- M5; gripper; 10 - 73

### commands

all values are one byte

- "u<angel>"; moves up by angel
- "d<devil>"; moves down by devil
- "s<motor><angel>"; sets the angel of motor to angel
- "p<motor1><motor2><motor3>"...; sets the position of the whole Gripper

### responses

- 202 -> everything right
- 404 -> no motor found
- 403 -> angel not allowed

## PC Client with python

In port.json you can config the port, baudrate, and timeout.

### using:
- pyserial for the serial communication