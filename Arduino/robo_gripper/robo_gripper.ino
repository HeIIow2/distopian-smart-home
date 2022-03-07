#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int pos[6] = {0,  15, 180, 0, 0,  73};
int max_min[6][2] = {{0, 180}, {15, 165}, {0, 180}, {0, 180}, {0, 180}, {10, 73}};
String input;


void goToAngel(int servo_, int angel) {
  int servo = servo_ - 1;

  if (angel < max_min[servo][0]) {
    pos[servo] = max_min[servo][0];
  } else if (angel > max_min[servo][1]) {
    pos[servo] = max_min[servo][1];
  } else {
    pos[servo] = angel;
  }

  Serial.println("");
  Serial.println(servo_);
  Serial.println(pos[servo]);

  Braccio.ServoMovement(20, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
}




void up(int step_) {
  bool m1 = false;
  bool m2 = true;
  bool m3 = true;

  int winkelsumme = 195;

  if (pos[2] <= max_min[2][0]) {
    m2 = false;
  }
  if (pos[3] <= max_min[3][0]) {
    m3 = false;
  }

  int new_m1 = pos[1] + step_;

  int available_count = m1 + m2 + m3;

  int add = (195 - (new_m1 + pos[2] + pos[3])) / available_count;

  pos[1] = new_m1;
  pos[2] = pos[2] + add * m2;
  pos[3] = pos[3] + add * m3;

  for (int i = 0; i <= 6; i++) {
    if (pos[i] < max_min[i][0]) {
      pos[i] = max_min[i][0];
    } else if (pos[i] > max_min[i][1]) {
      pos[i] = max_min[i][1];
    }
  }

  //Serial.println(pos[1]);
  //Serial.println(pos[2]);
  //Serial.println(pos[3]);

  Braccio.ServoMovement(20, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
}



void down(int step_) {
  bool m1 = false;
  bool m2 = true;
  bool m3 = true;

  int winkelsumme = 195;

  if (pos[2] >= max_min[2][1]) {
    m2 = false;
  }
  if (pos[3] >= max_min[3][1]) {
    m3 = false;
  }

  int new_m1 = pos[1] - step_;

  int available_count = m1 + m2 + m3;

  int add = (195 - (new_m1 + pos[2] + pos[3])) / available_count;

  pos[1] = new_m1;
  pos[2] = pos[2] + add * m2;
  pos[3] = pos[3] + add * m3;

  for (int i = 0; i <= 6; i++) {
    if (pos[i] < max_min[i][0]) {
      pos[i] = max_min[i][0];
    } else if (pos[i] > max_min[i][1]) {
      pos[i] = max_min[i][1];
    }
  }

  Braccio.ServoMovement(20, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
}


void setup() {
  Braccio.begin();
  Serial.begin(9600);
  Braccio.ServoMovement(20, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.readString();

    // up, <angle>
    if (input[0] == 'u') {
      byte Angel = input[1];
      Serial.println(Angel);
      //up(Angel);
      
    // down, <angle>
    } else if (input[0] == 'd') {
      byte Angel = input[1];
      
      Serial.println(Angel);
      //down(Angel);
    }

    // <motor>, <angle>
    else if (input[0] == 's') {
      byte Motor = input[1];
      byte Angel = input[2];

      //goToAngel(Motor, Angel);
    }

    for (int i = 0; i < 6; i++)
    {
      Serial.print(pos[i]);
      Serial.print(", ");
    }
    Serial.println();
  }




  /*
    Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
    M1=base degrees. Allowed values from 0 to 180 degrees
    M2=shoulder degrees. Allowed values from 15 to 165 degrees
    M3=elbow degrees. Allowed values from 0 to 180 degrees
    M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
    M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
    M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
}
