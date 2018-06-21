/* ************************
       RECEIVE FROM MEGA
************************* */

void receiveFromMega() {
  while (Serial1.available()) {
    char strIn[4];
    int i=0;
    delay(2); //allows all serial sent to be received together
    while(Serial1.available() && i<4) {   // JR - You changed this from 1 where it was working because there is a pin stuck in that hole
      strIn[i++] = Serial1.read();
    }
    strIn[i++]='\0';
    doSomethingWithPackageFromMega(atoi(strIn));
  }
}

void doSomethingWithPackageFromMega(int package) {  
  int function = package / 1000;
  int message = package % 1000;

    if (testMode) {
      Serial.print("Message Received fn:");
      Serial.print(function);
      Serial.print("  msg:");
      Serial.println(message);
    }    

  if (function == 1)
  {
    if (message < 2)
      doRobotTalkingLights(message);
    else if (message < 4)
      winkLeftMessage(message % 2);
    else if (message < 6)
      winkRightMessage(message % 2);
    else if (message < 7)
      changeEyeType();
    else if (message < 8)
      changePrimaryEyeColour();
    else if (message < 9)
      changeSecondaryEyeColour();
  }
  else if (function == 2)
  {
    arcadeButtonPressed(message);
  }
  else if (function == 3)
  {
    ledIntensity=message;
  }
  else if (function == 4)
  {
    // specific track was chosen on the keypad, play the track
    stayWithinGenre = false;
    playTune((message / 100), (message % 100), true);
  }
  else if (function == 5 || function == 6 || function == 7 || function == 8)
  {
    setEyeCoords(function, message);
  }

}

int leftEyeXIn = 0;
int leftEyeYIn = 0;
void setEyeCoords(int function, int message) {
  if (function == 5) {
    leftEyeX = message-43;
    leftEyeXIn = message-43;
  } else if (function == 6) {
    leftEyeY = message-43;
    leftEyeYIn = message-43;    
  } else if (function == 7) {
    rightEyeX = message-43;
    if (leftEyeXIn > -2 && leftEyeXIn < 2)
      leftEyeX = rightEyeX;
  } else if (function == 8) {
    rightEyeY = message-43;
    if (leftEyeYIn > -2 && leftEyeYIn < 2)
      leftEyeY = rightEyeY;
  }
}

void arcadeButtonPressed(int buttonNumber) {

  // Genre arcade button pressed
  if (buttonNumber < 8) {
    stayWithinGenre = true;
    playRandomTune(buttonNumber);
  }

  // Stop button
  if (buttonNumber == 8) {
    sendFullStop();
    //delay(20);
    //startRobotVoiceTrack();
  }

  // Next button
  if (buttonNumber == 9) {
    playNextTrack();
  }

  // Vol down button
  if (buttonNumber == 10) {
    mainVolume = mainVolume - 8;
    setMainVolume(mainVolume);
  }

  // Vol up button
  if (buttonNumber == 11) {
    mainVolume = mainVolume + 8;
    setMainVolume(mainVolume);
  }

  // Previous tune
  if (buttonNumber == 12) {    
    playPreviousTrack();
    //sendFullStop();
  }

  // Play button
  if (buttonNumber == 13) {
    stayWithinGenre = false;
    playRandomTune();
  }

}

void doRobotTalkingLights(int btnOnOffMessage) {
    if (btnOnOffMessage == 0)
    {
      robotTalking = true;
      robotTalkingOnTime = timey;
      // TODO turn down ableton volume here!
    } else if (btnOnOffMessage == 1) {
      robotTalking = false;
    }
}

void unmuteRobotVoice(int btnOnOffMessage) {
    if (btnOnOffMessage == 0)
    {
      setRobotVolume(100);
    }
    else if (btnOnOffMessage == 1)
    {
      setRobotVolume(0);
    }
}

/* ************************
       SEND TO MEGA
************************* */
void sendBeatToMega() {
  sendSerialToMega(1, sixteenBeats);
}

void sendSerialToMega(int function, int message) {
  if (testMode) {
    Serial.print("* * SENDING TO MEGA FN:");
    Serial.print(function);
    Serial.print("   MSG:");
    Serial.println(message);
  }

  if (megaAttached) {
    char strOut[4]; // the message from the mega
    itoa((function * 1000) + message, strOut, 10); //Turn value into a character array
    Serial1.write(strOut, 4);
  }
}

