
servoInfo servos[16] = {
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},  // HDKJS3150D settings
  {   0, 360, 6, 180},  // Hand servo settings
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210},
  {   0, 420, 6, 210}
};

// called from init, set all servos to their initial position
void initServos() {
  delay(100);
  for (int num = 0; num < 16; num++) {  
    moveServoToPos(num, servos[num].servoPos);
    delay(50);
  }
}

void doServos() {
  /*
  // Nod
  if(ps2.readButton(PS2_UP)==0)
    moveServo(0, servos[0].servoSpeed);
  else if(ps2.readButton(PS2_DOWN)==0)
    moveServo(0, -servos[0].servoSpeed);

  // Neck
  if(ps2.readButton(PS2_LEFT)==0)
    moveServo(1, servos[2].servoSpeed);
  else if(ps2.readButton(PS2_RIGHT)==0)
    moveServo(1, -servos[2].servoSpeed);   */

  if(ps2.readButton(PS2_LEFT)==0)
    moveServo(12, servos[2].servoSpeed);
  else if(ps2.readButton(PS2_RIGHT)==0)
    moveServo(12, -servos[2].servoSpeed);

  if(ps2.readButton(PS2_UP)==0)
    moveServo(13, servos[2].servoSpeed);
  else if(ps2.readButton(PS2_DOWN)==0)
    moveServo(13, -servos[2].servoSpeed);

  if(ps2.readButton(PS2_TRIANGLE)==0)
    moveServo(14, servos[2].servoSpeed);
  else if(ps2.readButton(PS2_CROSS)==0)
    moveServo(14, -servos[2].servoSpeed);

  if(ps2.readButton(PS2_SQUARE)==0)
    moveServo(15, servos[2].servoSpeed);
  else if(ps2.readButton(PS2_CIRCLE)==0)
    moveServo(15, -servos[2].servoSpeed);

}

void moveServo(int servoNum, int velocity) {
  int newPosition = servos[servoNum].servoPos + velocity;
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition) {
    servos[servoNum].servoPos=newPosition;
    servoPwm.setPWM(servoNum, 0, newPosition + 140); 
  } 
}

void moveServoToPos(int servoNum, int newPosition) {
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition) {
    servos[servoNum].servoPos=newPosition;
    servoPwm.setPWM(servoNum, 0, newPosition + 140); 
  }
}


