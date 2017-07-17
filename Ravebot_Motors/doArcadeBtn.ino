int ledValue, switchNum;

void doArcadeBtn() {

  readArcadeSwitches();

  for (switchNum = 0; switchNum < 14; switchNum++) {
    if (digitalRead(switchPins[switchNum]) == 0) {
      ledValue = 0; //4095;
    }
    else {
      ledValue = 4095; //((timey + (switchNum*400)) % 1024);
    }
    ledPwm.setPWM(switchNum, 0, ledValue);
  }
  
}

bool messageSent[14] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false};

void readArcadeSwitches() {

  for (switchNum = 0; switchNum < 14; switchNum++) { 
    if (digitalRead(switchPins[switchNum]) == 0 && !messageSent[switchNum])
    {
      sendSerialToLights(2, switchNum);
      messageSent[switchNum] = true;
    }
    else if (messageSent[switchNum] && digitalRead(switchPins[switchNum]) == 1)
    {
      messageSent[switchNum] = false;
    }
  }
}

