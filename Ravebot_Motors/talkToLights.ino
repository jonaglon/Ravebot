char str[4];

void talkToLights() {
  
  receiveSerialFromLights();

  checkButtonsSendInfoToLights();
}

void receiveSerialFromLights() {

  while (Serial3.available()) {
    int i=0;
    delay(5); //allows all serial sent to be received together
    while(Serial3.available() && i<4) {
      str[i++] = Serial3.read();
    }
    str[i++]='\0';
    doSomethingWithMessageFromLights(atoi(str));
  }
}

void doSomethingWithMessageFromLights(int messageInt) {
  int function = messageInt / 1000;
  int message = messageInt % 1000;

  if (function == 1) // this is a beat message
  {
    for (int switchNum = 0; switchNum < 14; switchNum++) {
      if (switchNum==message)
        ledPwm.setPWM(switchNum, 0, 4095);
    }
  }
  else if (function == 2) // this is a message to tell us what song is playing
  {
    setDisplay(message);
  }
}

bool ps2Right1On = false;
bool ps2Right2On = false;
void checkButtonsSendInfoToLights() {
  
  if (!ps2Right1On && ps2.readButton(PS2_RIGHT_1)==0)
  {
    ps2Right1On = true;
    sendSerialToLights(1, 0);
  }  
  if (ps2Right1On && ps2.readButton(PS2_RIGHT_1)==1)
  {
    ps2Right1On = false;
    sendSerialToLights(1, 1);
  }
  
  if (!ps2Right2On && ps2.readButton(PS2_RIGHT_2)==0)
  {
    ps2Right2On = true;
    sendSerialToLights(3, 0);
  }  
  if (ps2Right2On && ps2.readButton(PS2_RIGHT_2)==1)
  {
    ps2Right2On = false;
    sendSerialToLights(3, 1);
  }
  
}


void sendSerialToLights(int function, int message) {

  // we want to tell lights about how bright it should be - set by ps2 controllers
  
  int value = (function * 1000) + message;
  //Serial.println(message);
  
  itoa(value, str, 10); //Turn value into a character array
  Serial2.write(str, 4);

}

