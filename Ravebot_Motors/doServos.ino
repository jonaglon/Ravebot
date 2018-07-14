
// called from init, set all servos to their initial position
void initServos() {
  int range=3;
  
  for (int servoNum = 0; servoNum < 13; servoNum++) {
    moveServoToPos(servoNum, servos[servoNum].servoCenter+range);
  }
  delay(200);
  for (int servoNum = 0; servoNum < 13; servoNum++) {
    moveServoToPos(servoNum, servos[servoNum].servoCenter-range);
  }
  delay(200);
  for (int servoNum = 0; servoNum < 13; servoNum++) {
    moveServoToPos(servoNum, servos[servoNum].servoCenter);
  }
}

void doServos() {

  if (ps2.readButton(PS2_RIGHT_1) == 0) {
    doHead();
  }

  // dont do the wrists if any mod button is pressed
  if (ps2.readButton(PS2_LEFT_1) == 0) {
    leftWrist();
    rightWrist();
    leftClaw();
    rightClaw();
    rightElbow();
    leftElbow();
  }
}

void doAutomaticServos() {

  
}

void doHead() {
  doNod();
  doShake();
  doTilt();
}

int readPs2LYVar = 0;
void doNodDirect() {
  readPs2LYVar=-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128)/3;
  moveServoToPos(10, servos[10].servoCenter-readPs2LYVar);
}

// movement control vars
bool nodding = false;
unsigned long noddingTime;
void doNod() {
  readPs2LYVar=(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128)/33;

  // nod
  if (readPs2LYVar != 0) {
    moveServoSoft(10, readPs2LYVar);
    nodding = true;
    noddingTime = timey;
  }
  else if (nodding) {
    if (timey > noddingTime+1800)
      nodding = false;
  }
  else if (servos[10].servoPos > servos[10].servoCenter) {
    moveServoSoft(10, -2);
  }
  else if  (servos[10].servoPos < servos[10].servoCenter) {
    moveServoSoft(10, 2);
  }
}

// movement control vars
bool shaking = false;
unsigned long shakingTime;
int readPs2RXVar = 0;
void doShake() {
  // shake
  readPs2RXVar=(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS)-128)/38;

  if (readPs2RXVar != 0) {
    moveServoSoft(12, readPs2RXVar);
    shaking = true;
    shakingTime = timey;
  }
  else if (shaking) {
    if (timey > shakingTime+1800)
      shaking = false;
  }
  else if (servos[12].servoPos > servos[12].servoCenter) {
    moveServoSoft(12, -2);
  }
  else if  (servos[12].servoPos < servos[12].servoCenter) {
    moveServoSoft(12, 2);
  }
}

int readPs2LXVar = 0;
bool tilting = false;
unsigned long tiltTime;
void doTilt() {
  readPs2LXVar=-(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)-128)/63;

  // tilt
  if (readPs2LXVar != 0) {
    moveServoSoft(11, readPs2LXVar);
    tilting = true;
    tiltTime = timey;
  }
  else if (tilting) {
    if (timey > tiltTime+1800)
      tilting = false;
  }
  else if (servos[11].servoPos > servos[11].servoCenter) {
    moveServoSoft(11, -2);
  }
  else if  (servos[11].servoPos < servos[11].servoCenter) {
    moveServoSoft(11, 2);
  }
}

void leftClaw() {
  if (ps2.readButton(PS2_SQUARE) == 0) {
    moveServo(2, servos[2].servoSpeed);
  }
  if (ps2.readButton(PS2_CIRCLE) == 0) {
    moveServo(2, -servos[2].servoSpeed);
  }
}

void rightClaw() {
  if (ps2.readButton(PS2_RIGHT) == 0) {
    moveServo(6, servos[6].servoSpeed);
  }
  if (ps2.readButton(PS2_LEFT) == 0) {
    moveServo(6, -servos[6].servoSpeed);
  }
}

void leftWrist() {
  moveServoToPos(9, (-(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS)-128))+servos[9].servoCenter);
  moveServoToPos(3, (-(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)-128))+servos[3].servoCenter);
}

void rightWrist() {
  moveServoToPos(5, (ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)-128)+servos[5].servoCenter);
  moveServoToPos(7, (-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128))+servos[7].servoCenter);
}


void leftElbow() {
  if (ps2.readButton(PS2_CROSS) == 0) {
    moveServo(8, servos[8].servoSpeed);
  }
  if (ps2.readButton(PS2_TRIANGLE) == 0) {
    moveServo(8, -servos[8].servoSpeed);
  }
}

void rightElbow() {
  if (ps2.readButton(PS2_DOWN) == 0) {
    moveServo(4, -servos[4].servoSpeed);
  }
  if (ps2.readButton(PS2_UP) == 0) {
    moveServo(4, servos[4].servoSpeed);
  }
}

void moveServo(int servoNum, int velocity) {
  int newPosition = servos[servoNum].servoPos + velocity;
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    servoPwm.setPWM(servoNum, 0, newPosition);
    servos[servoNum].servoPos = newPosition;
    /*Serial.print("moving ");
    Serial.print(servoNum);
    Serial.print("to ");
    Serial.println(newPosition);*/
  }
}

void moveServoSoft(int servoNum, int velocity) {
  int newPosition = servos[servoNum].servoPos + velocity;
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    if (timey > (servos[servoNum].servoMoveTime + 16)) {
      servoPwm.setPWM(servoNum, 0, newPosition);
      servos[servoNum].servoPos = newPosition;
      servos[servoNum].servoMoveTime = timey;
    }
  }
}

void moveServoToPos(int servoNum, int newPosition) {
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    servoPwm.setPWM(servoNum, 0, newPosition);
    servos[servoNum].servoPos = newPosition;
  }
}


