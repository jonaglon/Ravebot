char strIn[4];
char strOut[4];

void talkToLights() {
  
  receiveSerialFromLights();

  checkLedIntensitySendChangeToLights();

  doWinking();

  if ((ps2.readButton(PS2_LEFT_1) == 1) && (ps2.readButton(PS2_LEFT_2) == 1) && (ps2.readButton(PS2_RIGHT_1) == 1))
    checkAnalogsForEyeMovements();

  if (ps2.readButton(PS2_RIGHT_1) == 0)
    checkButtonsForEyeColorAnimChange();

  checkButtonsSendInfoToLights();
}

void receiveSerialFromLights() {

  while (Serial3.available()) {
    int i=0;
    delay(5); //allows all serial sent to be received together
    while(Serial3.available() && i<4) {
      strIn[i++] = Serial3.read();
    }
    strIn[i++]='\0';
    int lightsMessage = atoi(strIn);
    doSomethingWithMessageFromLights(lightsMessage);
  }
}

void doSomethingWithMessageFromLights(int messageFromLights) {
  int requestFunction = messageFromLights / 1000;
  int requestMessage = messageFromLights % 1000;
  
  if (testMode) {
    Serial.print("Received Serial 2 Func:");
    Serial.print(requestFunction);
    Serial.print("   Received message:");
    Serial.println(requestMessage);
  }

  if (requestFunction == 1) // this is a beat message
  {
    // do the arcade button lights
    ledPwm.setPWM(requestMessage, 0, 0);

    // count
    currentBeat=requestMessage%16;
    if (currentBeat%4 == 0)
      currentBar++;

    doBeatDanceMove();

    if (testMode) {
      Serial.print("_____currentBeat:");
      Serial.print(currentBeat);
      Serial.print("   currentBar:");
      Serial.println(currentBar);
    }
      
  }
  else if (requestFunction == 2) // this is a message to tell us what song is playing
  {
    // If a new song is playing we should change dance
    changeDance();

    currentBeat=0;
    currentBar=0;

    doBeatDanceMove(); // todo - don't forget you added this so you can go to the initial position

    currentSegmentNum = requestMessage;
    if (robotSwitchedOn)
        showNumber();

    if (testMode) {
      Serial.print("   * ** Play song:");
      Serial.println(requestMessage);
    }
  }
}

void checkLedIntensitySendChangeToLights() {
  if (timey > nextAnalogRead) {
    int sensorValue = analogRead(A8);
    int newIntensity = 55-(sensorValue/19); // should give us a range ~2-50
    if ((newIntensity > ledIntensity+1 || newIntensity < ledIntensity-1) && newIntensity > 2) {
      ledIntensity = newIntensity;
      sendSerialToLights(3, ledIntensity);
    }
    nextAnalogRead = timey+300;
  }  
}

int leftEyeX;
int leftEyeY;
int rightEyeX;
int rightEyeY;
void checkAnalogsForEyeMovements() {

  // EYE MOVEMENT
  int newLeftX=ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)/3;
  if (newLeftX > leftEyeX || newLeftX < leftEyeX) {
    leftEyeX = newLeftX;
    sendSerialToLights(7, leftEyeX);
  }
  
  int newLeftY=ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)/3;
  if (newLeftY > leftEyeY || newLeftY < leftEyeY) {
    leftEyeY = newLeftY;
    sendSerialToLights(8, leftEyeY);
  }    

  int newRightX=ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS)/3;
  if (newRightX > rightEyeX || newRightX < rightEyeX) {
    rightEyeX = newRightX;
    sendSerialToLights(5, rightEyeX);
  }
  
  int newRightY=ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)/3;
  if (newRightY > rightEyeY || newRightY < rightEyeY) {
    rightEyeY = newRightY;
    sendSerialToLights(6, rightEyeY);
  }    

}

bool ps2LeftStickClickOn=false;
bool ps2RightStickClickOn=false;
void doWinking() {
      // WINKING
    if (!ps2LeftStickClickOn && ps2.readButton(PS2_JOYSTICK_LEFT)==0)
    {
      ps2LeftStickClickOn = true;
      sendSerialToLights(1, 2);
    }
    if (ps2LeftStickClickOn && ps2.readButton(PS2_JOYSTICK_LEFT)==1)
    {
      ps2LeftStickClickOn = false;
      sendSerialToLights(1, 3);
    }
  
    if (!ps2RightStickClickOn && ps2.readButton(PS2_JOYSTICK_RIGHT)==0)
    {
      ps2RightStickClickOn = true;
      sendSerialToLights(1, 4);
    }
    if (ps2RightStickClickOn && ps2.readButton(PS2_JOYSTICK_RIGHT)==1)
    {
      ps2RightStickClickOn = false;
      sendSerialToLights(1, 5);
    }
}
bool ps2TriangleOn=false;
bool ps2SquareOn=false;
bool ps2CircleOn=false;
bool ps2CrossOn=false;
void checkButtonsForEyeColorAnimChange() {
      // BUTTONS FOR EYE ANIMAITON AND COLOUR CHANGE
    if (!ps2TriangleOn && ps2.readButton(PS2_TRIANGLE)==0) {
      ps2TriangleOn = true;
      sendSerialToLights(1, 6);
    }
    if (ps2TriangleOn && ps2.readButton(PS2_TRIANGLE)==1)
      ps2TriangleOn = false;
    
    if (!ps2CircleOn && ps2.readButton(PS2_CIRCLE)==0) {
      ps2CircleOn = true;
      sendSerialToLights(1, 7);
    }
    if (ps2CircleOn && ps2.readButton(PS2_CIRCLE)==1) {
      ps2CircleOn = false;
    }
    
    if (!ps2CrossOn && ps2.readButton(PS2_CROSS)==0) {
      ps2CrossOn = true;
      sendSerialToLights(1, 8);
    }
    if (ps2CrossOn && ps2.readButton(PS2_CROSS)==1) {
      ps2CrossOn = false;
    }
}

bool ps2Right2On = false;
void checkButtonsSendInfoToLights() {
  // send talking signal
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
}

void sendDanceNumberToLights(int danceNumber) {
  sendSerialToLights(1, danceNumber + 20);
}

void sendSerialToLights(int function, int message) {

  if (testMode) {
    Serial.println("Sending to Serial 2");
  }

  int value = (function * 1000) + message;
  //Serial.println(message);
  
  itoa(value, strOut, 10); //Turn value into a character array
  Serial1.write(strOut, 4);

}

