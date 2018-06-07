
struct servoInfo {
  int minPosition;
  int maxPosition;
  int servoSpeed;
  int servoCenter;
  int servoPos;
  servoInfo(int aMinPosition, int aMaxPosition, int aServoSpeed, int aServoCenter, int aServoPos) :
    minPosition(aMinPosition), maxPosition(aMaxPosition), servoSpeed(aServoSpeed), servoCenter(aServoCenter), servoPos(aServoPos) {
  }
};

servoInfo servos[13] = {
  // 20 kg red servos - 150-500 / 325 mid
  { 130, 530, 3, 330, 330 }, // 0 - Head - shake
  { 360, 485, 2, 450, 450 }, // 1 - Head - Nod
  { 180, 330, 3, 240, 240 }, // 2 - L claw
  { 140, 560, 3, 350, 350 }, // 3 - l wrist ud
  { 140, 560, 2, 350, 350 }, // 4 - R elbow
  { 140, 560, 3, 350, 350 }, // 5 - R wrist lr
  { 290, 445, 3, 350, 350 }, // 6 - R claw increase to grab
  { 140, 560, 3, 350, 350 }, // 7 - r wrist ud
  { 140, 560, 2, 350, 350 }, // 8 - l elbow
  { 140, 560, 3, 350, 350 }, // 9 - l wrist lr
  { 205, 320, 1, 275, 275 }, // 10 - l new nod
  { 395, 455, 1, 425, 425 }, // 11 - l new tilt
  { 300, 400, 1, 350, 350 }  // 12 - l new shake
  
};

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
  /*
  servoPwm.setPWM(0, 0, 320);
  delay(500);
  servoPwm.setPWM(0, 0, 235);
  delay(500);
  servoPwm.setPWM(0, 0, 275);
  delay(500);

  servoPwm.setPWM(1, 0, 455);
  delay(500);
  servoPwm.setPWM(1, 0, 395);
  delay(500);
  servoPwm.setPWM(1, 0, 425);
  delay(500);

  servoPwm.setPWM(2, 0, 320);
  delay(500);
  servoPwm.setPWM(2, 0, 380);
  delay(500);
  servoPwm.setPWM(2, 0, 350);
  delay(500);*/

  setHead();
  /*
  // dont do the wrists if any mod button is pressed
  if ((ps2.readButton(PS2_LEFT_1) == 1) && (ps2.readButton(PS2_LEFT_2) == 1) && (ps2.readButton(PS2_RIGHT_1) == 1)) {
    leftWrist();
    rightWrist();
  }
  
  if (ps2.readButton(PS2_LEFT_1) == 1) { 
    leftClaw();
    rightClaw();
  } else {
    rightElbow();
    leftElbow();
  }*/
}


void setHead() {

  // Nod
  doNod();

  // shake
  if (ps2.readButton(PS2_LEFT_1) == 0) {
    moveServo(12, servos[12].servoSpeed);
    shaking = true;
    shakingTime = timey;
  }
  else if  (ps2.readButton(PS2_RIGHT_1) == 0) {
    moveServo(12, -servos[12].servoSpeed);
    shaking = true;
    shakingTime = timey;
  }
  else if (shaking) {
    if (timey > shakingTime+1800)
      shaking = false;
  }
  else if (servos[12].servoPos > servos[12].servoCenter+1) {
    moveServo(12, -servos[12].servoSpeed);
  }
  else if  (servos[12].servoPos < servos[12].servoCenter-1) {
    moveServo(12, servos[12].servoSpeed);
  }
}

int readPs2LYVar = 0;
void doNod() {
  readPs2LYVar=-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128)/3;
  moveServoToPos(10, servos[10].servoCenter-readPs2LYVar);
}

void leftClaw() {
  if (ps2.readButton(PS2_CIRCLE) == 0) {
    moveServo(2, servos[2].servoSpeed);
  }
  if (ps2.readButton(PS2_TRIANGLE) == 0) {
    moveServo(2, -servos[2].servoSpeed);
  }
}

void rightClaw() {
  if (ps2.readButton(PS2_CROSS) == 0) {
    moveServo(6, servos[6].servoSpeed);
  }
  if (ps2.readButton(PS2_SQUARE) == 0) {
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
  if (ps2.readButton(PS2_CIRCLE) == 0) {
    moveServo(8, servos[8].servoSpeed);
  }
  if (ps2.readButton(PS2_TRIANGLE) == 0) {
    moveServo(8, -servos[8].servoSpeed);
  }
}

void rightElbow() {
  if (ps2.readButton(PS2_CROSS) == 0) {
    moveServo(4, -servos[4].servoSpeed);
  }
  if (ps2.readButton(PS2_SQUARE) == 0) {
    moveServo(4, servos[4].servoSpeed);
  }
}


void setRightArmJoystickMovement() {
  // Jesus wept
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

void moveServoToPos(int servoNum, int newPosition) {
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    servoPwm.setPWM(servoNum, 0, newPosition);
    servos[servoNum].servoPos = newPosition;
  }
}


