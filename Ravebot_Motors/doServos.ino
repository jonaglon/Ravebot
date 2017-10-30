
struct servoInfo {
  int boardNum;
  int minPosition;
  int maxPosition;
  int servoSpeed;
  int servoPos;
  servoInfo(int aBoardNum, int aMinPosition, int aMaxPosition, int aServoSpeed, int aServoPos) :
    boardNum(aBoardNum), minPosition(aMinPosition), maxPosition(aMaxPosition), servoSpeed(aServoSpeed), servoPos(aServoPos) {
  }
};

servoInfo servos[10] = {
  { 0, 0, 420, 3, 210 }, // 0 - Head - Turn
  { 1, 0, 420, 3, 210 }, // 1 - Head - Nod
  { 6,180,300, 2, 240 }, // 2 - R Arm - Gripper was 360    w
  { 5, 0, 420, 3, 210 }, // 3 - R Arm - Wrist LR     w
  { 4, 0, 420, 3, 210 }, // 4 - R Arm - Elbow
  { 7, 0, 420, 3, 210 }, // 5 - R Arm - Wrist UD
  { 2,-150, 0, 2,  -75}, // 6 - L Arm -Gripper
  { 3, 0, 420, 3, 210 }, // 7 - L Arm -Wrist UD
  { 8, 0, 420, 3, 210 }, // 8 - L Arm -Elbow
  { 9, 0, 420, 3, 210 }  // 9 -  L Arm - Wrist LR
};


// called from init, set all servos to their initial position
void initServos() {
  //delay(100);
  for (int num = 0; num < 10; num++) 
  {
    moveServoToPos(servos[num].boardNum, servos[num].servoPos - 10);
    //delay(500);
  }
}

void doServos() {

  setLeftArmsElbowsAndHandGrabber();

  //setLeftArmJoystickMovement();

  setRightArmsElbowsAndHandGrabber();

  setRightArmJoystickMovement();

}

void setLeftArmsElbowsAndHandGrabber() {
  // Right arm
  if (ps2.readButton(PS2_UP) == 0) // Left Elbow
    moveServo(servos[4].boardNum, servos[4].servoSpeed);
  else if (ps2.readButton(PS2_DOWN) == 0)
    moveServo(servos[4].boardNum, -servos[4].servoSpeed);

  if (ps2.readButton(PS2_LEFT) == 0) // Left Hand Cripper
    moveServo(servos[2].boardNum, servos[2].servoSpeed);
  else if (ps2.readButton(PS2_RIGHT) == 0)
    moveServo(servos[2].boardNum, -servos[2].servoSpeed);
}

void setRightArmsElbowsAndHandGrabber() {
  // Left arm elbows and wrists
  if (ps2.readButton(PS2_TRIANGLE) == 0) // Right Elbow
    moveServo(servos[8].boardNum, servos[8].servoSpeed);
  else if (ps2.readButton(PS2_CROSS) == 0)
    moveServo(servos[8].boardNum, -servos[8].servoSpeed);

  if (ps2.readButton(PS2_SQUARE) == 0) // Right Hand Cripper
    moveServo(servos[6].boardNum, servos[6].servoSpeed);
  else if (ps2.readButton(PS2_CIRCLE) == 0)
    moveServo(servos[6].boardNum, -servos[6].servoSpeed);
}

void setRightArmJoystickMovement() {
  // Jesus wept
}

void moveServo(int servoNum, int velocity) {
  int newPosition = servos[servoNum].servoPos + velocity;
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition) {
    servos[servoNum].servoPos = newPosition;
    servoPwm.setPWM(servoNum, 0, newPosition + 140);
  }
}

void moveServoToPos(int servoNum, int newPosition) {
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition) {
    servos[servoNum].servoPos = newPosition;
    servoPwm.setPWM(servoNum, 0, newPosition + 140);
  }
}


