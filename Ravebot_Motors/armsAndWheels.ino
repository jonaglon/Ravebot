int readPs2Var;
bool rightArmMoving=false;
bool leftArmMoving=false;

void doMyArms() {
  int rightUp = digitalRead(A5);
  int rightDown = digitalRead(A4);
  int leftUp = digitalRead(A2);
  int leftDown = digitalRead(A3);

  if (testMode) {
    Serial.print("  r-up:");
    Serial.print(rightUp);
    Serial.print("  r-down:");
    Serial.print(rightDown);
    Serial.print("  l-up:");
    Serial.print(leftUp);
    Serial.print("  l-down:");
    Serial.println(leftDown);
  }

  if (ps2.readButton(PS2_LEFT_2) == 0) {
    
    // Right arm
    readPs2Var=-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128);
    if (rightUp==1 && readPs2Var < 2) {
      // JR - TODO next --- ---- --- arm judders
      sendRArmMotorValue(readPs2Var);
      rightArmMoving=true;
    } else if (rightDown==1 && readPs2Var > 2) {
      sendRArmMotorValue(readPs2Var);
      rightArmMoving=true;
    } else {
      sendRArmMotorValue(0);
      rightArmMoving=false;
    }

    // Left arm
    readPs2Var=ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)-128;
    if (leftUp==1 && readPs2Var > 2) {
      sendLArmMotorValue(readPs2Var);
      leftArmMoving=true;
    } else if (leftDown==1 && readPs2Var < 2) {
      sendLArmMotorValue(readPs2Var);
      leftArmMoving=true;
    } else {
      sendLArmMotorValue(0);
      leftArmMoving=false;
    }
  }

  if (rightArmMoving && (rightUp==0 || rightDown==0)) {
      sendRArmMotorValue(0);
      rightArmMoving=false;
  }
  if (leftArmMoving && (leftUp==0 || leftDown==0)) {
      sendLArmMotorValue(0);
      leftArmMoving=false;
  }
  
}    

int rArmMotorValue = 0;
void sendRArmMotorValue(int newValue) {
  if (newValue != rArmMotorValue)
  {
    rArmMotorValue = newValue;
    ST1.motor(2, rArmMotorValue);
  }
}

int lArmMotorValue = 0;
void sendLArmMotorValue(int newValue) {
  if (newValue != lArmMotorValue)
  {
    lArmMotorValue = newValue;
    ST1.motor(1, lArmMotorValue);
  }
}

void doMyWheels() {
  //readPs2Var=-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128);

  //readPs2Var=readPs2Var-128; 
  
  //Serial.print("ly:");  
  //Serial.print(readPs2Var);  
  //ST2.motor(2, readPs2Var);

 // delay(20);

  //readPs2Var=-(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)-128);
  //Serial.print("   ry:");  
  //Serial.println(readPs2Var);  
  //ST2.motor(1, readPs2Var);

}

