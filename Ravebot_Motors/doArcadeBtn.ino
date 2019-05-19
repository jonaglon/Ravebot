int ledValue;

void doArcadeBtn() {
  readArcadeSwitches();
  switchPressedButtonToFullBrightness();
}

bool messageSent[14] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false};
void readArcadeSwitches() {
  for (int switchNum = 0; switchNum < 14; switchNum++) { 
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

void switchPressedButtonToFullBrightness() {
  for (int switchNum = 0; switchNum < 14; switchNum++) {
    if (digitalRead(switchPins[switchNum]) == 0) {
      ledValue = 4095;
    }
    else {
      ledValue = 0;
    }
    ledPwm.setPWM(switchNum, 0, ledValue);
  }
}

void switchOffArcadeButtons() {
  for (int switchNum = 0; switchNum < 14; switchNum++) { 
    ledPwm.setPWM(switchNum, 0, 0);
  }  
}
