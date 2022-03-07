# distopian-smart-home

## Serial communications to the Arduino

### command

all values are one byte

- "u<angel>"; moves up by angel
- "d<devil>"; moves down by devil
- "s<motor><angel>"; sets the angel of motor to angel

### responses

- 404 -> no motor found
- 403 -> angel not allowed