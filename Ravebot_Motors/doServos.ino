
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

servoInfo servos[10] = {
  { 390, 520, 1, 410, 410 }, // 0 - Head - Nod
  { 130, 530, 2, 330, 330 }, // 1 - Head - shake
  { 180, 330, 3, 240, 240 }, // 2 - L claw
  { 140, 560, 3, 350, 350 }, // 3 - l wrist ud
  { 140, 560, 2, 350, 350 }, // 4 - R elbow
  { 140, 560, 3, 350, 350 }, // 5 - R wrist lr
  { 290, 445, 3, 350, 350 }, // 6 - R claw increase to grab
  { 140, 560, 3, 350, 350 }, // 7 - r wrist ud
  { 140, 560, 3, 350, 350 }, // 8 - l elbow
  { 140, 560, 3, 350, 350 }  // 9 - l wrist lr
};

// called from init, set all servos to their initial position
void initServos() {

  int range=10;
  
  for (int servoNum = 0; servoNum < 9; servoNum++) {
    moveServoToPos(servoNum, servos[servoNum].servoCenter+range);
    delay(200);
    moveServoToPos(servoNum, servos[servoNum].servoCenter-range);
    delay(200);
    moveServoToPos(servoNum, servos[servoNum].servoCenter);
    delay(200);
  }
}

void doServos() {

  setHead();

  leftClaw();
  leftElbow();
  leftWrist();

  rightClaw();
  rightElbow();
  rightWrist();

}


void setHead() {

  // Nod
  if (ps2.readButton(PS2_UP) == 0) {
    moveServo(0, servos[0].servoSpeed);
    nodding = true;
    noddingTime = timey;
  }
  else if  (ps2.readButton(PS2_DOWN) == 0) {
    moveServo(0, -servos[0].servoSpeed);
    nodding = true;
    noddingTime = timey;
  }
  else if (nodding) {
    if (timey > noddingTime+2500)
      nodding = false;
  }
  else if  (servos[0].servoPos > servos[0].servoCenter+1) {
    moveServo(0, -servos[0].servoSpeed);
  }
  else if  (servos[0].servoPos < servos[0].servoCenter-1) {
    moveServo(0, servos[0].servoSpeed);
  }

  // Move head left and right
  if (ps2.readButton(PS2_RIGHT) == 0) {
    moveServo(1, servos[1].servoSpeed);
    shaking = true;
    shakingTime = timey;
  }
  else if  (ps2.readButton(PS2_LEFT) == 0) {
    moveServo(1, -servos[1].servoSpeed);
    shaking = true;
    shakingTime = timey;
  }
  else if (shaking) {
    if (timey > shakingTime+2500)
      shaking = false;
  }
  else if  (servos[1].servoPos > servos[1].servoCenter+1) {
    moveServo(1, -servos[1].servoSpeed);
  }
  else if  (servos[1].servoPos < servos[1].servoCenter-1) {
    moveServo(1, servos[1].servoSpeed);
  }
}

void leftClaw() {
  if (ps2.readButton(PS2_CIRCLE) == 0) {
    if (lClawOpening) {
      moveServo(2, servos[2].servoSpeed);
      lClawMoving = true;
    } else {
      moveServo(2, -servos[2].servoSpeed);
      lClawMoving = true;
    }
  } else if (lClawMoving) {
    if (lClawOpening) {
      lClawOpening = false;
    } else {
      lClawOpening = true;
    }
    lClawMoving = false;
  }
}

void rightClaw() {
  if (ps2.readButton(PS2_CROSS) == 0) {
    if (rClawOpening) {
      moveServo(6, servos[6].servoSpeed);
      rClawMoving = true;
    } else {
      moveServo(6, -servos[6].servoSpeed);
      rClawMoving = true;
    }
  } else if (rClawMoving) {
    if (rClawOpening) {
      rClawOpening = false;
    } else {
      rClawOpening = true;
    }
    rClawMoving = false;
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
  if (ps2.readButton(PS2_SQUARE) == 0) {
    if (lElbowOpening) {
      moveServo(4, servos[4].servoSpeed);
      lElbowMoving = true;
    } else {
      moveServo(4, -servos[4].servoSpeed);
      lElbowMoving = true;
    }
  } else if (lElbowMoving) {
    if (lElbowOpening) {
      lElbowOpening = false;
    } else {
      lElbowOpening = true;
    }
    lElbowMoving = false;
  }
}

void rightElbow() {
  if (ps2.readButton(PS2_TRIANGLE) == 0) {
    if (rElbowOpening) {
      moveServo(8, servos[8].servoSpeed);
      rElbowMoving = true;
    } else {
      moveServo(8, -servos[8].servoSpeed);
      rElbowMoving = true;
    }
  } else if (rElbowMoving) {
    if (rElbowOpening) {
      rElbowOpening = false;
    } else {
      rElbowOpening = true;
    }
    rElbowMoving = false;
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


