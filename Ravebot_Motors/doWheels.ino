int readPs2Var;


void doMyArms() {

  int rightUp = digitalRead(A1);
  int rightDown = digitalRead(A4);

  int leftUp = digitalRead(A2);
  int leftDown = digitalRead(A3);

  if (leftUp == 1) {
    Serial.println(".  .  .  .  .  .  .  .  .  .");
  } else {
    Serial.println("****************************");
  }
  
  if (ps2.readButton(PS2_LEFT_1) == 0) {
    ST2.motor(1, 127);
  } else if (ps2.readButton(PS2_LEFT_2) == 0) {
    ST2.motor(1, -127);
  }

  if (ps2.readButton(PS2_RIGHT_1) == 0) {
    ST2.motor(2, 127);
  } else if (ps2.readButton(PS2_RIGHT_2) == 0) {
    ST2.motor(2, -127);
  }

}


void doMyWheels() {
  readPs2Var=-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128);

  //readPs2Var=readPs2Var-128; 
  
  //Serial.print("ly:");  
  //Serial.print(readPs2Var);  
  ST2.motor(2, readPs2Var);

 // delay(20);

  readPs2Var=-(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)-128);
  //Serial.print("   ry:");  
  //Serial.println(readPs2Var);  
  ST2.motor(1, readPs2Var);

}

