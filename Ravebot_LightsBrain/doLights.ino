int currentPattern = 1;

void doLights() {

  //allOff();
  allOffBySection();

  if (currentPattern == 1) {
    horizontalRainbow(false, false, 40);
    //sectionsInTime2();
    //heartInTime();
    lightsInTimeTest01();
    doEyes();
    doTalkingLights();
  } else if (currentPattern == 2) {
    horizontalRainbow(false, false, 100);
    // smileyEyes();
    pacManEyes();
  } else {
    horizontalRainbow(false, false, 10);
  }
  LEDS.show();  
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
int currentHeartBeatValue(int sixteenHalfBeatShift, int maxValue, int dropoffLengthDivisor) {
  int sixteenHalfBeatVal = (sixteenHalfBeats + sixteenHalfBeatShift) % 8;
  int returnVal = 0;
  
  if (sixteenHalfBeatVal < 1) {
    returnVal = (((percentThroughHalfBeat * 100) / 8192)*255)/100;
  } else if (sixteenHalfBeatVal < 5) {
    returnVal = 255-(((((((sixteenHalfBeatVal-1)*8192)+percentThroughHalfBeat)*100)/(65536/dropoffLengthDivisor))*255)/100);
  }
  
  return returnVal;
}

int numLedsTube = 90;
int numLedsPerBeat=22;
int beatCompNum = 16384/numLedsPerBeat; // this is the 16384 beat% / those 30 leds. (182/546 - for 30/90)
void lightsInTimeTest01() {
  for(int j = 0; j < 90; j++)
    setSectionLed(15, j, 0, 0, 0, 0);

  
  for(int j = 0; j < numLedsTube; j++) {
    int distanceFromBeat = quickAbsolute(((j%numLedsPerBeat)*beatCompNum)-percentThroughBeat);

    if (j%numLedsPerBeat < 10) {
      int distanceFromBeat2 = quickAbsolute((((j%numLedsPerBeat)+numLedsPerBeat)*beatCompNum)-percentThroughBeat);
      if (distanceFromBeat2 < distanceFromBeat)
        distanceFromBeat = distanceFromBeat2;
    }

    int ledColour = 255 - (distanceFromBeat/10);
    if (ledColour < 0)
      ledColour = 0;

    setSectionLed(13, j, ledColour, 0, 0, 0);
    setSectionLed(14, j, 0, ledColour, 0, 0);
    setSectionLed(15, j, 0, 0, ledColour, 0);
    setSectionLed(16, j, 0, 0, 0, ledColour);
  }

}

int quickAbsolute(int number) {
  if (number < 0)
    return number * (-1);
  else
    return number;
}

void horizontalRainbow(bool includeEyes, bool includeMouth, int speedFactor) {
  int ticko = (timey / speedFactor) % 1024;
  
  for(int j = 0; j < numLeds; j++) {
    int xCoord = (getCoord(j,0)+ticko)%1024;
    SetRgbwWheelVars(xCoord/4);
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}

// lazy variable naming, j is ledNum and k is x or y
int getCoord(int j, int k) {
  if (j < 203)
     return binCoords[j][k]+ledPosOffset[0][k];
  else if (j < 378)
    return bigHeartCoords[j-203][k]+ledPosOffset[1][k];
  else if (j < 463)
    return smHeartCoords[j-378][k]+ledPosOffset[2][k];
  else if (j < 482)
    return armCoords[j-463][k]+ledPosOffset[3][k];
  else if (j < 506)
    return armCoords[j-482][k]+ledPosOffset[4][k];
  else if (j < 599)
    return eyeCoords[j-506][k]+ledPosOffset[5][k];
  else if (j < 692)
    return eyeCoords[j-599][k]+ledPosOffset[6][k];
  else if (j < 710)
    return horizCoords[j-692][k]+ledPosOffset[7][k];
  else if (j < 744)
    return tapeCoords[j-710][k]+ledPosOffset[8][k];
  else if (j < 770)
    return horizCoords[j-744][k]+ledPosOffset[9][k];
  else if (j < 774)
    return horizCoords[j-770][k]+ledPosOffset[10][k];
  else if (j < 797)
    return armCoords[j-774][k]+ledPosOffset[11][k];
  else if (j < 821)
    return armCoords[j-797][k]+ledPosOffset[12][k];
  else if (j < 911)
    return tubeCoords[j-821][k]+ledPosOffset[13][k];
  else if (j < 1001)
    return tubeCoords[j-911][k]+ledPosOffset[14][k];
  else if (j < 1090)
    return tubeCoords[j-1001][k]+ledPosOffset[15][k];
  else if (j < 1179)
    return tubeCoords[j-1090][k]+ledPosOffset[16][k];
  else if (j < 1302)
    return portLCoords[(j-1179)%19][k]+ledPosOffset[17][k];
  else if (j < 1441)
    return portRCoords[(j-1302)%19][k]+ledPosOffset[18][k];
}


void doEyes() {

  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, 110, 150, 150, 0);
    setSectionLed(6, j, 110, 150, 150, 0);
  }

  // dark eye squares
  drawPupil(ledSections[5], 55+leftEyeX, 55-leftEyeY, 0, 0, 0, 0);
  drawPupil(ledSections[6], 55+rightEyeX, 55-rightEyeY, 0, 0, 0, 0);

  // pupil
  drawLightsNear(ledSections[5], 55+leftEyeX, 55-leftEyeY, 7, 110, 150, 150, 0);
  drawLightsNear(ledSections[6], 55+rightEyeX, 55-rightEyeY, 7, 110, 150, 150, 0);

  doBlinking();
  doLeftWink();
  doRightWink();
}

void heartEyes() {

  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, 0, 0, 0, 0);
    setSectionLed(6, j, 0, 0, 0, 0);
  }

  for(int j = 0; j < 56; j++) {
    setSectionLed(5, eyeHeartLeds[j], 255, 0, 216, 0);
    setSectionLed(6, eyeHeartLeds[j], 255, 0, 216, 0);
  }
}

void pacManEyes() {
  // 16384 is a beat length  1489 is an 11th
  int animationStep = percentThroughBeat / 1489;
  
  for(int j = 0; j < 93; j++) {
    if (pacManAnimationMask[animationStep][j])
      setSectionLed(5, j, 120, 130, 0, 0);
    else
      setSectionLed(5, j, 0, 0, 0, 0);
  }
}

void smileyEyes() {
  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, 90, 160, 0, 0);
    setSectionLed(6, j, 90, 160, 0, 0);
  }

  for(int j = 0; j < 26; j++) {
    setSectionLed(5, eyeSmileyLeds[j], 0, 0, 0, 0);
    setSectionLed(6, eyeSmileyLeds[j], 0, 0, 0, 0);
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
    for(int j = 0; j < 93; j++) {
      setSectionLed(6, j, 0, 0, 0, 0);
    }
    setSectionLed(6, 24, 110, 150, 150, 0);
    setSectionLed(6, 50, 110, 150, 150, 0);
    setSectionLed(6, 68, 110, 150, 150, 0);
    setSectionLed(6, 81, 110, 150, 150, 0);
    setSectionLed(6, 90, 110, 150, 150, 0);
    setSectionLed(6, 92, 110, 150, 150, 0);
    setSectionLed(6, 86, 110, 150, 150, 0);
    setSectionLed(6, 75, 110, 150, 150, 0);
    setSectionLed(6, 60, 110, 150, 150, 0);
    setSectionLed(6, 38, 110, 150, 150, 0);
    setSectionLed(6,  8, 110, 150, 150, 0);
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
    for(int j = 0; j < 93; j++) {
      setSectionLed(5, j, 0, 0, 0, 0);
    }
    setSectionLed(5, 24, 110, 150, 150, 0);
    setSectionLed(5, 50, 110, 150, 150, 0);
    setSectionLed(5, 68, 110, 150, 150, 0);
    setSectionLed(5, 81, 110, 150, 150, 0);
    setSectionLed(5, 90, 110, 150, 150, 0);
    setSectionLed(5, 92, 110, 150, 150, 0);
    setSectionLed(5, 86, 110, 150, 150, 0);
    setSectionLed(5, 75, 110, 150, 150, 0);
    setSectionLed(5, 60, 110, 150, 150, 0);
    setSectionLed(5, 38, 110, 150, 150, 0);
    setSectionLed(5,  8, 110, 150, 150, 0);
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


//   drawLightsNear(ledSections[5], 55+leftEyeX, 55-leftEyeY, 30, 0, 0, 0, 0);
void drawLightsNear(int offSet, int xCoord, int  yCoord, int radius, int r, int g, int b, int w) {
  for(int j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setLedDirect(offSet+j, r, g, b, w, false);
      }
    }
  }
}

const int pupilRadius=26;
const int maxRadius=42;
void drawPupil(int ledNumOffSet, int xCoord, int  yCoord,  int r, int g, int b, int w) {
  for (int j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+pupilRadius)) && (eyeCoords[j][1] < (yCoord+pupilRadius))) {
      if ((eyeCoords[j][0] > (xCoord-pupilRadius)) && (eyeCoords[j][1] > (yCoord-pupilRadius))) {
        int x = quickAbsolute(xCoord-eyeCoords[j][0]);
        int y = quickAbsolute(yCoord-eyeCoords[j][1]);
        if (x + y < maxRadius) {
          setLedDirect(ledNumOffSet+j, r, g, b, w, false);
        }
      }
    }
  }
}


void sectionsInTime() {
  int beat4 = sixteenHalfBeats % 4;  
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
  int beat16 = sixteenHalfBeats % 16;  
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



