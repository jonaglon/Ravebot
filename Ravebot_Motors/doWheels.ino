int readPs2Var;

void doWheels()
{
  readPs2Var=-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128);

  //readPs2Var=readPs2Var-128; 
  
  //Serial.print("ly:");  
  //Serial.print(readPs2Var);  
  ST.motor(2, readPs2Var);

 // delay(20);

  readPs2Var=-(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)-128);
  //Serial.print("   ry:");  
  //Serial.println(readPs2Var);  
  ST.motor(1, readPs2Var);

}

