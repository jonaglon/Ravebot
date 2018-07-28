int currentPattern = 1;
int numPatterns = 5;

void doLights() {

  allOff();
  //allOffBySection();

  if (currentPattern == 1) {
    horizontalRainbow(false, false, 20);
  } else if (currentPattern == 2) {
    doPatternStripes();
  } else if (currentPattern == 3) {
    doPatternTrains();
  } else if (currentPattern == 4) {
    horizontalRainbow(false, false, 80);
    sectionsInTime();
  } else {
    doPatternBlobs();
  }
  doFace();
  LEDS.show();
}

void changeLightPattern() {
  // choose a new pattern, different from the current one
  int newPattern = currentPattern;
  while (newPattern == currentPattern) {
    newPattern = random(numPatterns);
  }
  currentPattern = newPattern;
}

/////////////////////
// Generic patters //
/////////////////////

void circleInTime() {
  int numToLight = percentThroughBeat / 182;

  for(int j = 0; j < 90; j++) {
    setSectionLed(14, j, 0, 0, 0, 0);
  }
  
  for(int j = 0; j < numToLight; j++) {
    setSectionLed(14, j, 0, 0, 255, 0);
  }
  
}

void heartInTime() {
  // we want a heartbeat
  int ledValue1 = currentHeartBeatValue(0, 255, 4);
  int ledValue2 = currentHeartBeatValue(7, 170, 2);

  if (ledValue1 > ledValue2)
    setSection(1, ledValue1, 0, 0, 0);
  else
    setSection(1, ledValue2, 0, 0, 0);
}

// the shorter dropoff divisor the longer the trail
int currentHeartBeatValue(int sixteenBeatShift, int maxValue, int dropoffLengthDivisor) {
  int sixteenBeatVal = (sixteenBeats + sixteenBeatShift) % 8;
  int returnVal = 0;
  
  if (sixteenBeatVal < 1) {
    returnVal = (((percentThroughBeat * 100) / 8192)*255)/100;
  } else if (sixteenBeatVal < 5) {
    returnVal = 255-(((((((sixteenBeatVal-1)*8192)+percentThroughBeat)*100)/(65536/dropoffLengthDivisor))*255)/100);
  }
  return returnVal;
}



void horizontalRainbow(bool includeEyes, bool includeMouth, int speedFactor) {
  int ticko = (timey / speedFactor) % 1024;
  
  for(int j = 0; j < numLeds; j++) {
    int xCoord = (getCoord(j,0)+ticko)%1024;
    SetRgbwWheelVars(xCoord/4);
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}


void sectionsInTime() {
  int beat4 = sixteenBeats % 4;  
  if (beat4 == 0) {
    setSection(13, 255, 0, 0, 0);
    setSection(14, 0, 255, 0, 0);
    setSection(15, 0, 0, 255, 0);
    setSection(16, 0, 0, 0, 255);
  } else if (beat4 == 1) {
    setSection(14, 255, 0, 0, 0);
    setSection(15, 0, 255, 0, 0);
    setSection(16, 0, 0, 255, 0);
    setSection(13, 0, 0, 0, 255);  
  } else if (beat4 == 2) {
    setSection(15, 255, 0, 0, 0);
    setSection(16, 0, 255, 0, 0);
    setSection(13, 0, 0, 255, 0);
    setSection(14, 0, 0, 0, 255);  
  } else if (beat4 == 3) {
    setSection(16, 255, 0, 0, 0);
    setSection(13, 0, 255, 0, 0);
    setSection(14, 0, 0, 255, 0);
    setSection(15, 0, 0, 0, 255);  
  };
}

void sectionsInTime2() {
  int beat16 = sixteenBeats % 16;  
  if (beat16 < 5) {
    setSection(13, 0, 0, 0, 0);
  } else if (beat16 < 9) {
    setSection(14, 0, 0, 0, 0);
  } else if (beat16 < 13) {
    setSection(15, 0, 0, 0, 0);
  } else {
    setSection(16, 0, 0, 0, 0);
  };
}


/* ******************************* EYES & MOUTH ********************************** */

// Eye types are used when the robot is in manual mode, in auto eye dances are used
int currentEyeType = 0;
void changeEyeType() {
  currentEyeType = (currentEyeType+1)%5;
}

int currentEyeDance = 0;
void changeEyeDance() {
  currentEyeDance = (currentEyeDance+1)%4;
}

void doFace() {
  eyeController();
  doTalkingLights();
}

void eyeController() {

  if (robotManualMode) {
    switch (currentEyeType) {
      case 0: doNormalEyes();
        break;
      case 1: doStonerEyes();
        break;
      case 2: heartEyes();
        break;
      case 3: pacManEyes();
        break;
      case 4: smileyEyes();
        break;
    }
  } else {
    switch (currentEyeDance) {
      case 0: 
        doNormalEyes();
        break;
      case 1: 
        leftEyeX = (sixteenBeats * 10)-80;
        rightEyeX = (sixteenBeats * 10)-80;
        break;
      case 2: 
        if ((currentBar%4) == 0) {
          int eyePrimaryR = 255;
          int eyePrimaryG = 0;
          int eyePrimaryB = 0;
          heartEyes();
        } else {
          int eyePrimaryR = 110;
          int eyePrimaryG = 150;
          int eyePrimaryB = 150;
          doNormalEyes();
        }
        break;
      case 3: 
        if ((currentBar%4) == 0) {
          pacManEyes();
        } else {
          doNormalEyes();
        }
        break;
    }
  }
  
}

int eyePrimaryR = 110;
int eyePrimaryG = 150;
int eyePrimaryB = 150;
int eyeRValues[6] = {255,0,  0,  110, 0, 255};
int eyeGValues[6] = {0,  255,0,  150, 0, 0  };
int eyeBValues[6] = {0,  0,  255,150, 0, 210};
int currentEyePrimaryPos = 3;
void changePrimaryEyeColour() {
  currentEyePrimaryPos = (currentEyePrimaryPos+1)%6;
  eyePrimaryR = eyeRValues[currentEyePrimaryPos];
  eyePrimaryG = eyeGValues[currentEyePrimaryPos];
  eyePrimaryB = eyeBValues[currentEyePrimaryPos];
}

int eyeSecondaryR = 0;
int eyeSecondaryG = 0;
int eyeSecondaryB = 0;
int currentEyeSecondaryPos = 4;
void changeSecondaryEyeColour() {
  currentEyeSecondaryPos = (currentEyeSecondaryPos+1)%6;
  eyeSecondaryR = eyeRValues[currentEyeSecondaryPos];
  eyeSecondaryG = eyeGValues[currentEyeSecondaryPos];
  eyeSecondaryB = eyeBValues[currentEyeSecondaryPos];
}

void doNormalEyes() {

  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }

  // iris
  drawHexagon(ledSections[5], 55+leftEyeX, 55-leftEyeY, 26, 42, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  drawHexagon(ledSections[6], 55+rightEyeX, 55-rightEyeY, 26, 42, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);

  // pupil
  drawEyeSquare(ledSections[5], 55+leftEyeX, 55-leftEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  drawEyeSquare(ledSections[6], 55+rightEyeX, 55-rightEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);

  doBlinking();
  doLeftWink();
  doRightWink();
}

void doStonerEyes() {

  for(int j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 56) {
      setSectionLed(5, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
      setSectionLed(6, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    } else {
      setSectionLed(5, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
      setSectionLed(6, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
    }
  }

  // dark eye squares
  drawHexagon(ledSections[5], 55+leftEyeX, 29-leftEyeY, 20, 35, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  drawHexagon(ledSections[6], 55+rightEyeX, 29-rightEyeY, 20, 35, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);

  // pupil
  drawEyeSquare(ledSections[5], 55+leftEyeX, 29-leftEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  drawEyeSquare(ledSections[6], 55+rightEyeX, 29-rightEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);

  doLeftWink();
  doRightWink();
}

void heartEyes() {

  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
    setSectionLed(6, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  }

  for(int j = 0; j < 56; j++) {
    setSectionLed(5, eyeHeartLeds[j], eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, eyeHeartLeds[j], eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }
}

void pacManEyes() {
  // 16384 is a beat length  1365 is an 12th-ish
  //int animationStep = percentThroughBeat / 1365;
  
  int animationStep1 = (timeyInTime / 2048)%8;
  int animationStep2 = (timeyInTime / 1024)%16;
  
  for(int j = 0; j < 93; j++) {
    if (pacManAnimationMask[(animationStep2)%16][j]) {
      setSectionLed(6, j, 120, 120, 0, 0);
    } else if (pacManAnimationMask2[(animationStep1+4)%8][j]) {
      setSectionLed(6, j, 0, 0, 0, 0);
    } else {
      setSectionLed(6, j, 255, 255, 255, 0);
    }
  }
  for(int j = 0; j < 93; j++) {
    if (pacManAnimationMask2[animationStep1][j]) {
      setSectionLed(5, j, 0, 0, 0, 0);
    } else {
      setSectionLed(5, j, 255, 255, 255, 0);
    }
  }
}

void smileyEyes() {
  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }
  for(int j = 0; j < 26; j++) {
    setSectionLed(5, eyeSmileyLeds[j], eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
    setSectionLed(6, eyeSmileyLeds[j], eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  }
}

unsigned long blinkStart=4000;
const int blinkLength=240;
void doBlinking() {
  int drawTo = 0;
  //int drawTo2 = 0;
  int blinkHeight = 60;
  
  if (timey > (blinkStart + blinkLength)) {
    // blink over, reset
    if (random(9) == 0) {
      blinkStart = timey + random(400);
    } else {
      blinkStart = timey + random(4000,9000);
    }
  } else if (timey > blinkStart) {
    int percIntoBlink = ((timey - blinkStart)*100)/(blinkLength/2);
    if (timey > (blinkStart + (blinkLength/2))) {
      // on way up
      drawTo = ((blinkHeight * percIntoBlink)/100)-blinkHeight+50;
    } else {
      // on way down
      drawTo = blinkHeight+50-((blinkHeight * percIntoBlink)/100);
    }
    for(int j = 0; j < 93; j++) {
      if (eyeCoords[j][1] < 110 - drawTo) {
          setSectionLed(5, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] > drawTo) {
          setSectionLed(5, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] < 110 - drawTo) {
          setSectionLed(6, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] > drawTo) {
          setSectionLed(6, j, 0, 0, 0, 0);
      }
    }
  }
}

unsigned long lWinkStart=0;
unsigned long rWinkStart=0;
unsigned long lWinkEnd=0;
unsigned long rWinkEnd=0;
bool lWinking = false;
bool rWinking = false;
const int winkLength=350;

// Note, left and right winks are copied and pasted, change both the same.
void doLeftWink() {
  if (!lWinking)
    return;

  int drawTo = 0;  
  if (lWinkEnd!=0 && (timey > (lWinkEnd + (winkLength/2)))) {
    // blink over, reset
    lWinking = false;
    lWinkEnd=0;
    drawTo = 110;
  } else if (lWinkEnd==0 && timey < (lWinkStart + (winkLength/2))) {
    // on way down
    int percIntoBlink = ((timey - lWinkStart)*100)/(winkLength/2);
    drawTo = 110-((60 * percIntoBlink)/100);
  } else if (lWinkEnd!=0) {
    // on way up
    int percIntoBlink = ((timey - lWinkEnd)*100)/(winkLength/2);
    drawTo = 50+((60 * percIntoBlink)/100);
  } else {
    // in the middle
    for(int j = 0; j < 93; j++) {
      setSectionLed(6, j, 0, 0, 0, 0);
    }
    setSectionLed(6, 24, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 50, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 68, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 81, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 90, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 92, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 86, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 75, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 60, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 38, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6,  8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    return;
  }
  for(int j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(6, j, 0, 0, 0, 0);
    }
    if (eyeCoords[j][1] > drawTo) {
        setSectionLed(6, j, 0, 0, 0, 0);
    }
  }
}

void doRightWink() {
  if (!rWinking)
    return;

  int drawTo = 0;  
  if (rWinkEnd!=0 && (timey > (rWinkEnd + (winkLength/2)))) {
    // blink over, reset
    rWinking = false;
    rWinkEnd=0;
    drawTo = 110;
  } else if (rWinkEnd==0 && timey < (rWinkStart + (winkLength/2))) {
    // on way down
    int percIntoBlink = ((timey - rWinkStart)*100)/(winkLength/2);
    drawTo = 110-((60 * percIntoBlink)/100);
  } else if (rWinkEnd!=0) {
    // on way up
    int percIntoBlink = ((timey - rWinkEnd)*100)/(winkLength/2);
    drawTo = 50+((60 * percIntoBlink)/100);
  } else {
    // in the middle
    for(int j = 0; j < 93; j++) {
      setSectionLed(5, j, 0, 0, 0, 0);
    }
    setSectionLed(5, 24, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 50, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 68, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 81, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 90, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 92, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 86, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 75, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 60, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 38, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5,  8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    return;
  }
  for(int j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(5, j, 0, 0, 0, 0);
    }
    if (eyeCoords[j][1] > drawTo) {
        setSectionLed(5, j, 0, 0, 0, 0);
    }
  }
}

void winkLeftMessage(int blinkOnOffMessage) {
  if (blinkOnOffMessage == 0) {
    // start new wink
    lWinkStart=timey;
    lWinking = true;
    lWinkEnd=0;
    // push forward the next blink
    blinkStart = timey + random(3000,8000);
  } else if (blinkOnOffMessage == 1) {
    // end wink
    lWinkEnd=timey;
  }
}

void winkRightMessage(int blinkOnOffMessage) {
  if (blinkOnOffMessage == 0) {
    // start new wink
    rWinkStart=timey;
    rWinking = true;
    rWinkEnd=0;
    // push forward the next blink
    blinkStart = timey + random(3000,8000);
  } else if (blinkOnOffMessage == 1) {
    // end wink
    rWinkEnd=timey;
  }
}


void doTalkingLights() {

  if (robotTalking) {
    setLedDirect(ledSections[7]+8, 255, 60, 60, 100, true);
    setLedDirect(ledSections[7]+9, 255, 60, 60, 100, true);
    
    if (timey > (robotTalkingOnTime + 40)) {
      setLedDirect(ledSections[7]+7, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+10, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 80)) {
      setLedDirect(ledSections[7]+6, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+11, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 110)) {
      setLedDirect(ledSections[7]+5, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+12, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 135)) {
      setLedDirect(ledSections[7]+4, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+13, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 150)) {
      setLedDirect(ledSections[7]+3, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+14, 255, 60, 60, 100, true);
    }
  }  
}

