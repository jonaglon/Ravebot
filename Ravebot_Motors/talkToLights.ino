char lightsMessageInStr[4];
char lightsMessageOutStr[4];

void talkToLights() {
  
  receiveSerialFromLights();

  checkLedIntensitySendChangeToLights();

  checkButtonsSendInfoToLights();
}

void receiveSerialFromLights() {

  while (Serial2.available()) {
    int i=0;
    delay(5); //allows all serial sent to be received together
    while(Serial2.available() && i<4) {
      lightsMessageInStr[i++] = Serial2.read();
    }
    lightsMessageInStr[i++]='\0';
    int lightsMessage = atoi(lightsMessageInStr);
    doSomethingWithMessageFromLights(lightsMessageInStr);
  }
}

void doSomethingWithMessageFromLights(int messageFromLights) {
  int requestFunction = messageFromLights / 1000;
  int requestMessage = messageFromLights % 1000;
  
    if (testMode) {
      Serial.print("Received Serial 2 Func:");
      Serial.print(messageFromLights);
      Serial.print("   Received message:");
      Serial.println(messageFromLights);
    }

  if (requestFunction == 1) // this is a beat message
  {
    for (int switchNum = 0; switchNum < 14; switchNum++) {
      if (switchNum==requestMessage) {
        ledPwm.setPWM(switchNum, 0, 0);
      }
    }
  }
  else if (requestFunction == 2) // this is a message to tell us what song is playing
  {
    currentSegmentNum = requestMessage;
    showNumber();
    if (testMode) {
      Serial.print("   * ** Play song:");
      Serial.println(requestMessage);
    }
  }
}

void checkLedIntensitySendChangeToLights() {

  if (nextAnalogRead > timey) {
    int sensorValue = analogRead(A8);
    int newIntensity = 50-(sensorValue/19); // should give us a range ~2-50
    if (newIntensity != ledIntensity) {
      ledIntensity = newIntensity;
      sendSerialToLights(3, ledIntensity);
    }    
    nextAnalogRead = timey+300;
  }  
}

// bool ps2Right1On = false;
bool ps2Right2On = false;
void checkButtonsSendInfoToLights() {
  
  if (!ps2Right2On && ps2.readButton(PS2_RIGHT_2)==0)
  {
    ps2Right2On = true;
    sendSerialToLights(1, 0);
  }
  if (ps2Right2On && ps2.readButton(PS2_RIGHT_2)==1)
  {
    ps2Right2On = false;
    sendSerialToLights(1, 1);
  }
  
  /* if (!ps2Right2On && ps2.readButton(PS2_RIGHT_2)==0)
  {
    ps2Right2On = true;
    sendSerialToLights(3, 0);
  }
  if (ps2Right2On && ps2.readButton(PS2_RIGHT_2)==1)
  {
    ps2Right2On = false;
    sendSerialToLights(3, 1);
  } */
  
}


void sendSerialToLights(int function, int message) {

  if (testMode) {
    Serial.println("Sending to Serial 2");
  }

  int value = (function * 1000) + message;
  //Serial.println(message);
  
  itoa(value, lightsMessageOutStr, 10); //Turn value into a character array
  Serial1.write(lightsMessageOutStr, 4);

}

