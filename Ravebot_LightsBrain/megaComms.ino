/* ************************
       RECEIVE FROM MEGA
************************* */
char str[4]; // the message from the mega

void receiveFromMega() {
  while (Serial2.available()) {
    int i=0;
    delay(5); //allows all serial sent to be received together
    while(Serial2.available() && i<4) {
      str[i++] = Serial2.read();
    }
    str[i++]='\0';
    doSomethingWithPackageFromMega(atoi(str));
  }
}

void doSomethingWithPackageFromMega(int package) {  
  int function = package / 1000;
  int message = package % 1000;

  if (function == 1)
  {
    doRobotTalkingLights(message);
  }
  else if (function == 2)
  {
    if (testMode) {
      Serial.print("Button pressed! Num:");
      Serial.println(message);
    }    
    arcadeButtonPressed(message);
  }
  else if (function == 3)
  {
    unmuteRobotVoice(message); 
  }
  else if (function == 4)
  {
    // specific track was chosen on the keypad, play the track
    // stayWithinGenre = false;
    // playTune((message / 100), (message % 100));
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
    stopAllAbletonTracks();
  }

  // Next button
  if (buttonNumber == 9) {
    if (stayWithinGenre)
      playRandomTune(currentGenre);
    else
      playRandomTune();
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

  // Play button
  if (buttonNumber == 12) {    
    stayWithinGenre = false;
    playRandomTune();
  }

  // Last tune                    // TODO remember the last x tunes played
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
    }
    else if (btnOnOffMessage == 1)
    {
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

  int value = (function * 1000) + message;
  
  itoa(value, str, 10); //Turn value into a character array
  Serial3.write(str, 4);

}

