
servoInfo servos[10] = {
  {3700, 4780, 3, 3800},
  {3200, 4400, 3, 3800},
  {3000, 4700, 3, 4000},
  {3000, 4700, 3, 4000},
  {3000, 4700, 3, 4000},
  {3000, 4700, 3, 4000},
  {3000, 4700, 3, 4000},
  {3000, 4700, 3, 4000},
  {3000, 4700, 3, 4000},
  {3000, 4700, 3, 4000}
};

// called from init, set all servos to their initial position
void initServos() {

  delay(100);

  for (int num = 0; num < 10; num++) {  
    servoPwm.setPWM(num, 0, (servos[num].servoPos/10)); 
  }
 
}

void doServos() {
  
  // Nod
  if(ps2.readButton(PS2_UP)==0)
    doServo(0, servos[0].servoSpeed);
  else if(ps2.readButton(PS2_DOWN)==0)
    doServo(0, -servos[0].servoSpeed);

  // Nod
  /*if(ps2.readButton(PS2_LEFT)==0)
    doServo(1);
  else if(ps2.readButton(PS2_RIGHT)==0)
    doServo(1);*/

  // Neck
  if(ps2.readButton(PS2_LEFT)==0)
    doServo(2, servos[2].servoSpeed);
  else if(ps2.readButton(PS2_RIGHT)==0)
    doServo(2, -servos[2].servoSpeed);

}

void doServo(int servoNum, int velocity) {
  if ((velocity > 0 && servos[servoNum].servoPos < servos[servoNum].maxPosition) || 
      (velocity < 0 && servos[servoNum].servoPos > servos[servoNum].minPosition))
  {
    servos[servoNum].servoPos=servos[servoNum].servoPos + velocity;
    servoPwm.setPWM(servoNum, 0, (servos[servoNum].servoPos/10));
  } 
}


