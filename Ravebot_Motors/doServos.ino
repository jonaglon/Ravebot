
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
  { 230, 560, 0, 380, 380 }, // 0 - Head - Nod
  { 140, 560, 3, 360, 360 }, // 1 - Head - shake
  { 180, 300, 2, 240, 240 }, // 2 - L Arm - Gripper was 360    w
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
  for (int num = 5; num < 6; num++) 
  {
    moveServoToPos(num, servos[num].servoCenter-20);
    delay(10);
    moveServoToPos(num, servos[num].servoCenter-10);
    delay(10);
    moveServoToPos(num, servos[num].servoCenter);
  }
}

void doServos() {

  setHead();

  //setLeftArmsElbowsAndHandGrabber();

  //setLeftArmJoystickMovement();

  //setRightArmsElbowsAndHandGrabber();

  //setRightArmJoystickMovement();

}


void setHead() {

  // Nod

  // Move head left and right
  int newPos = (ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)-128)+servos[5].servoCenter; // 128+ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)+servos[1].servoCenter;
  //Serial.print("pos:");
  //Serial.println(newPos);
  moveServoToPos(5, newPos);


}

void setLeftArmsElbowsAndHandGrabber() {
  // Right arm
  if (ps2.readButton(PS2_UP) == 0) // Left Elbow
    moveServo(4, servos[4].servoSpeed);
  else if (ps2.readButton(PS2_DOWN) == 0)
    moveServo(4, -servos[4].servoSpeed);

  if (ps2.readButton(PS2_LEFT) == 0) // Left Hand Cripper
    moveServo(2, servos[2].servoSpeed);
  else if (ps2.readButton(PS2_RIGHT) == 0)
    moveServo(2, -servos[2].servoSpeed);
}

void setRightArmJoystickMovement() {
  // Jesus wept
}

void moveServo(int servoNum, int velocity) {
  int newPosition = servos[servoNum].servoPos + velocity;
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    servoPwm.setPWM(servoNum, 0, newPosition);
    servos[servoNum].servoPos = newPosition;
  }
}

void moveServoToPos(int servoNum, int newPosition) {
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    servoPwm.setPWM(servoNum, 0, newPosition);
    servos[servoNum].servoPos = newPosition;
  }
}


