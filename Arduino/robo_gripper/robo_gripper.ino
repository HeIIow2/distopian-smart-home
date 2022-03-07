#include <Braccio.h>
#include <Servo.h>

#define MOTOR_COUNT 6

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int pos[MOTOR_COUNT] = {0,  15, 180, 0, 0,  73};
int max_min[MOTOR_COUNT][2] = {{0, 180}, {15, 165}, {0, 180}, {0, 180}, {0, 180}, {10, 73}};
String input;


int goToAngel(int servo, int angel) {
  if (servo >= MOTOR_COUNT || servo < 0) {
    Serial.print("404");
    return 404;
  }

  if (angel < max_min[servo][0]) {
    pos[servo] = max_min[servo][0];
    return 403;
  } else if (angel > max_min[servo][1]) {
    pos[servo] = max_min[servo][1];
    return 403;
  } else {
    pos[servo] = angel;
    return 202;
  }
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

  Serial.print("202");

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

  Serial.print("202");

  Braccio.ServoMovement(20, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
}


void setup() {
  Braccio.begin();
  Serial.begin(9600);
  Braccio.ServoMovement(20, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
  Serial.print("202");
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.readString();

    // u<angel>
    // moves up
    if (input[0] == 'u') {
      byte Angel = input[1];

      up(Angel);
      
    // d<angel>
    // moves down
    } else if (input[0] == 'd') {
      byte Angel = input[1];
      
      down(Angel);
    }

    // <motor>, <angle>
    // sets angle of motor
    else if (input[0] == 's') {
      byte Motor = input[1];
      byte Angel = input[2];

      Serial.print(goToAngel(Motor, Angel));
    }

    else if (input[0] == 'p') {
      int error_code = 202;
      for(int i=0; i<MOTOR_COUNT; i++) {
        int current_error_code = goToAngel(i, input[i+1]);
        if (current_error_code != 202) {
          error_code = current_error_code;
        }
      }
      Serial.print(error_code);
    }
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
