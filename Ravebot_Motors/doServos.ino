
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
  { 370, 520, 1, 400, 400 }, // 0 - Head - Nod - number goes up, head goes forward
  { 130, 530, 2, 330, 330 }, // 1 - Head - shake
  { 180, 330, 3, 240, 240 }, // 2 - L Arm - Gripper was 360    w
  { 140, 560, 3, 350, 350 }, // 3 - R Arm - Wrist LR     w
  { 140, 560, 3, 350, 350 }, // 4 - R Arm - Elbow
  { 140, 560, 3, 350, 350 }, // 5 - R Arm - Wrist UD
  { 140, 0,   2, 0, 0}, // 6 - L Arm -Gripper
  { 140, 560, 3, 350, 350 }, // 7 - L Arm -Wrist UD
  { 140, 560, 3, 350, 350 }, // 8 - L Arm -Elbow
  { 140, 560, 3, 350, 350 }  // 9 -  L Arm - Wrist LR
};

// called from init, set all servos to their initial position
void initServos() {

  int delayo=35;
  int range=10;
  
  for (int servoNum = 0; servoNum < 4; servoNum++) {
    moveServoToPos(servoNum, servos[servoNum].servoCenter+range);
    delay(delayo);
    moveServoToPos(servoNum, servos[servoNum].servoCenter-range);
    delay(delayo);
    moveServoToPos(servoNum, servos[servoNum].servoCenter);
    delay(delayo);
  }
}

void doServos() {

  setHead();

  setLeftArmsElbowsAndClaw();

  //setLeftArmJoystickMovement();

  //setRightArmsElbowsAndHandGrabber();

  //setRightArmJoystickMovement();

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

void setLeftArmsElbowsAndClaw() {

  // Left Claw
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
  
  /* else if (ps2.readButton(PS2_DOWN) == 0)
    moveServo(4, -servos[4].servoSpeed);

  if (ps2.readButton(PS2_LEFT) == 0) // Left Hand Cripper
    moveServo(2, servos[2].servoSpeed);
  else if (ps2.readButton(PS2_RIGHT) == 0)
    moveServo(2, -servos[2].servoSpeed);  */
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


