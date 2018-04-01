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

// animationPoint=0;

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

  // TODOs
  // can you give this a colour which moves from tube to tube?

  // heart

  // pattern which eminates from center on beat
}

int quickAbsolute(int number) {
  if (number < 0)
    return number * (-1);
  else
    return number;
}
/*
void lightsInTimeTest01() {
  for(int j = 0; j < 90; j++)
    setSectionLed(15, j, 0, 0, 0, 0);

  for(int j = 0; j < numLedsExp; j++) {
    int distanceFromBeat = quickAbsolute((j*beatCompNum)-percentThroughBeat);

    // how can we make 0 and numLedsExp "close" ?
    //if (distanceFromBeat > 5000)
    //  distanceFromBeat = quickAbsolute((16384-(j*beatCompNum))-percentThroughBeat);

    int ledColour = 255 - (distanceFromBeat/10);
    if (ledColour < 0)
      ledColour = 0;

    setSectionLed(15, j, ledColour, 0, 0, 0);
  }
}
*/

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

void doLightsLessOld() {

  allOff();
  // allOffBySection();

  // stripes
  //drawMovingPatternX(8);
  //drawMovingPattern(8);

  //setSection(1, 255, 0, 0, 0);
  /*for(int j = 0; j < 203; j++) {
    if (j % 4 == 0) {
      setSectionLed(2, j, 255, 255, 0, 255);
    }
  }
  setSectionLed(2, 0, 255, 0, 0, 0);
  setSectionLed(2, 3, 0, 0, 255, 0); 

  
  drawStripeX(4, 100, 0, 0, 255, 0);
  drawStripeX(9, 150, 0, 90, 155, 0);
  //drawStripeX(17, 80, 50, 50, 55, 255);

  drawStripeY(2, 200, 0, 0, 255, 0);
  //drawStripeY(5, 100, 120, 60, 0, 10);
  drawStripeY(9, 150, 50, 50, 55, 255);
  //drawStripeX(17, 80,  70, 0, 180, 0);
  
  // sectionsInTime();

  rgbwSnake(0, 10);   // crawling with ants!
  rgbwSnake(100, 5);
  rgbwSnake(200, 20);
  rgbwSnake(1100, 15);
  rgbwSnake(1200, 10); */

  LEDS.show();
}

void drawMovingPatternX(int speedFactor) {
  int ticko = (timey / speedFactor) % 800;
  drawLightsBetween(ticko-200, ticko, 0, 2000, true, true, 0, 255, 0, 0);  
}
void drawMovingPattern(int speedFactor) {
  int ticko = (timey / speedFactor) % 2000;
  drawLightsBetween(0, 800, ticko-300, ticko, true, true, 0, 0, 255, 0);  
}

void drawStripeX(int speedFactor, int width, int r, int g, int b, int w) {

  int ticko = (timey / speedFactor) % 1000;

  drawLightsBetween((ticko - width) > 0 ? (ticko - width) : 0, ticko, 0, 2000, true, true, r, g, b, w);
  
}

void drawStripeY(int speedFactor, int width, int r, int g, int b, int w) {

  int ticko = (timey / speedFactor) % 2000;

  drawLightsBetween(0, 800, (ticko - width) > 0 ? (ticko - width) : 0, ticko, true, true, r, g, b, w);
  
}

void doLightsOld() {

  allOff();

  //setLedDirect(7, 255 , 0, 0, 0, false);
  
  //lightEyes(25, 25, 200, 10);
  
  //everySingleLight(200, 0, 0, 0);

  //sweepTestRainbowTorso(20);

  setSection(0, 0, 0, 0, 255);
  setSection(1, 255, 0, 0, 0);
  setSection(2, 0, 255, 0, 0);
  setSection(3, 0, 0, 255, 0);
  setSection(4, 0, 255, 0, 0);

  doEyes();
  // setSection(5, 255, 0, 0, 0);
  // setSection(6, 0, 255, 0, 0);

  doTalkingLights();
  //setSection(7, 0, 0, 255, 0);
  setSection(8, 0, 0, 0, 255);
  
  setSection(9, 255, 0, 0, 0);
  setSection(10, 0, 255, 0, 0);
  setSection(11, 0, 0, 255, 0);
  setSection(12, 0, 0, 0, 255);
  
  setSection(13, 255, 0, 0, 0);
  setSection(14, 0, 255, 0, 0);
  setSection(15, 0, 0, 255, 0);
  setSection(16, 0, 0, 0, 255);
  
  setSection(17, 255, 0, 0, 0);
  setSection(18, 0, 255, 0, 0);
  
  //sectionsInTime();

  /*drawMovingStripe(60, 300, 1, 10, 0, 100, 0, 0,  0);
  drawMovingStripe(30, 150, 2, 50, 0, 0, 100,  0, 0);
  drawMovingStripe(23, 300, 3, 10, 12, 0, 0,120,  0);
  drawMovingStripe(12, 500, 2, 15, 12, 0, 80,30,  0);
  drawMovingStripe(22, 700, 4, 20, 24, 20, 30,  80,0);
  drawMovingStripe(40, 950, 3, 5, 24,  30, 80,  0,  0);*/

  rgbwSnake(0, 10);   // crawling with ants!
  rgbwSnake(100, 5);
  rgbwSnake(200, 20);
  rgbwSnake(300, 40);
  rgbwSnake(400, 10);
  rgbwSnake(500, 25);
  rgbwSnake(600, 20);
  rgbwSnake(700, 5);
  rgbwSnake(800, 10);
  rgbwSnake(900, 50);
  rgbwSnake(1000, 20);
  rgbwSnake(1100, 15);
  rgbwSnake(1200, 10);

  LEDS.show();
}

void doEyes() {

  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, 50, 50, 50, 0);
    setSectionLed(6, j, 50, 50, 50, 0);
  }

  doBlinking();

  // dark eye squares
  drawLightsNear(ledSections[5], 55+leftEyeX, 55-leftEyeY, 30, 0, 0, 0, 0);
  drawLightsNear(ledSections[6], 55+rightEyeX, 55-rightEyeY, 30, 0, 0, 0, 0);

  // pupil
  drawLightsNear(ledSections[5], 55+leftEyeX, 55-leftEyeY, 7, 80, 80, 80, 0);
  drawLightsNear(ledSections[6], 55+rightEyeX, 55-rightEyeY, 7, 80, 80, 80, 0);
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
int blinkLength=220;

void doBlinking() {
  int drawTo = 0;
  int blinkHeight = 120;
  
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
      drawTo = ((blinkHeight * percIntoBlink)/100)-blinkHeight;
    } else {
      // on way down
      drawTo = blinkHeight-((blinkHeight * percIntoBlink)/100);
    }
    for(int j = 0; j < 93; j++) {
      if (eyeCoords[j][1] > drawTo) {
          setSectionLed(5, j, 0, 0, 0, 0);
      }
    }
    for(int j = 0; j < 93; j++) {
      if (eyeCoords[j][1] > drawTo) {
          setSectionLed(6, j, 0, 0, 0, 0);
      }
    }
  }

  
}


void drawLightsNear(int offSet, int xCoord, int  yCoord, int radius, int r, int g, int b, int w) {

  for(int j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setLedDirect(offSet+j, r, g, b, w, false);
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


void drawLightsBetween(int startX, int endX, int startY, int endY, bool includeEyes, bool includeMouth, int r, int g, int b, int w) {
  int j = 0;
  
  // 0 bottomRing
  for(j = 0; j < 204; j++)
    if (binCoords[j][0]+ledPosOffset[0][0] > startX && binCoords[j][0]+ledPosOffset[0][0] < endX && binCoords[j][1]+ledPosOffset[0][1] > startY && binCoords[j][1]+ledPosOffset[0][1] < endY)
        setSectionLed(0, j, r, g, b, w);
  
  // 1 bigHeart
  for(j = 0; j < 176; j++)
    if (bigHeartCoords[j][0]+ledPosOffset[1][0] > startX && bigHeartCoords[j][0]+ledPosOffset[1][0] < endX && bigHeartCoords[j][1]+ledPosOffset[1][1] > startY && bigHeartCoords[j][1]+ledPosOffset[1][1] < endY)
        setSectionLed(1, j, r, g, b, w);
  
  // 2 smallHeart
  for(j = 3; j < 86; j++)
    if (smHeartCoords[j][0]+ledPosOffset[2][0] > startX && smHeartCoords[j][0]+ledPosOffset[2][0] < endX && smHeartCoords[j][1]+ledPosOffset[2][1] > startY && smHeartCoords[j][1]+ledPosOffset[2][1] < endY)
        setSectionLed(2, j, r, g, b, w);

  // 3 underArmLeft
  for(j = 0; j < 24; j++)
    if (armCoords[j][0]+ledPosOffset[3][0] > startX && armCoords[j][0]+ledPosOffset[3][0] < endX && armCoords[j][1]+ledPosOffset[3][1] > startY && armCoords[j][1]+ledPosOffset[3][1] < endY)
        setSectionLed(3, j, r, g, b, w);

  // 4 overArmLeft
  for(j = 0; j < 24; j++)
    if (armCoords[j][0]+ledPosOffset[4][0] > startX && armCoords[j][0]+ledPosOffset[4][0] < endX && armCoords[j][1]+ledPosOffset[4][1] > startY && armCoords[j][1]+ledPosOffset[4][1] < endY)
        setSectionLed(4, j, r, g, b, w);

  if (includeEyes) {
    // 5 rightEye
    for(j = 0; j < 94; j++)
      if (eyeCoords[j][0]+ledPosOffset[5][0] > startX && eyeCoords[j][0]+ledPosOffset[5][0] < endX && eyeCoords[j][1]+ledPosOffset[5][1] > startY && eyeCoords[j][1]+ledPosOffset[5][1] < endY)
          setSectionLed(5, j, r, g, b, w);
  
    // 6 leftEye
    for(j = 0; j < 94; j++)
      if (eyeCoords[j][0]+ledPosOffset[6][0] > startX && eyeCoords[j][0]+ledPosOffset[6][0] < endX && eyeCoords[j][1]+ledPosOffset[6][1] > startY && eyeCoords[j][1]+ledPosOffset[6][1] < endY)
          setSectionLed(6, j, r, g, b, w);
  }
  
  // 7 mouth
  if (includeMouth) {
    for(j = 0; j < 18; j++)
      if (horizCoords[j][0]+ledPosOffset[7][0] > startX && horizCoords[j][0]+ledPosOffset[7][0] < endX && horizCoords[j][1]+ledPosOffset[7][1] > startY && horizCoords[j][1]+ledPosOffset[7][1] < endY)
          setSectionLed(7, j, r, g, b, w);
  }
    
  // 8 tape 
  for(j = 0; j < 34; j++)
    if (tapeCoords[j][0]+ledPosOffset[8][0] > startX && tapeCoords[j][0]+ledPosOffset[8][0] < endX && tapeCoords[j][1]+ledPosOffset[8][1] > startY && tapeCoords[j][1]+ledPosOffset[8][1] < endY)
        setSectionLed(8, j, r, g, b, w);

  // 09 tuner
  for(j = 0; j < 26; j++)
    if (horizCoords[j][0]+ledPosOffset[9][0] > startX && horizCoords[j][0]+ledPosOffset[9][0] < endX && horizCoords[j][1]+ledPosOffset[9][1] > startY && horizCoords[j][1]+ledPosOffset[9][1] < endY)
        setSectionLed(9, j, r, g, b, w);

  // 10 indicator
  for(j = 0; j < 4; j++)
    if (horizCoords[j][0]+ledPosOffset[10][0] > startX && horizCoords[j][0]+ledPosOffset[10][0] < endX && horizCoords[j][1]+ledPosOffset[10][1] > startY && horizCoords[j][1]+ledPosOffset[10][1] < endY)
        setSectionLed(10, j, r, g, b, w);

  // 11 underArmRight
  for(j = 0; j < 24; j++)
    if (armCoords[j][0]+ledPosOffset[11][0] > startX && armCoords[j][0]+ledPosOffset[11][0] < endX && armCoords[j][1]+ledPosOffset[11][1] > startY && armCoords[j][1]+ledPosOffset[11][1] < endY)
        setSectionLed(11, j, r, g, b, w);

  // 12 overArmRight
  for(j = 0; j < 24; j++)
    if (armCoords[j][0]+ledPosOffset[12][0] > startX && armCoords[j][0]+ledPosOffset[12][0] < endX && armCoords[j][1]+ledPosOffset[12][1] > startY && armCoords[j][1]+ledPosOffset[12][1] < endY)
        setSectionLed(12, j, r, g, b, w);

  // 13 tube bottom right
  for(j = 0; j < 90; j++)
    if (tubeCoords[j][0]+ledPosOffset[13][0] > startX && tubeCoords[j][0]+ledPosOffset[13][0] < endX && tubeCoords[j][1]+ledPosOffset[13][1] > startY && tubeCoords[j][1]+ledPosOffset[13][1] < endY)
        setSectionLed(13, j, r, g, b, w);

  // 14 tube bottom left
  for(j = 0; j < 90; j++)
    if (tubeCoords[j][0]+ledPosOffset[14][0] > startX && tubeCoords[j][0]+ledPosOffset[14][0] < endX && tubeCoords[j][1]+ledPosOffset[14][1] > startY && tubeCoords[j][1]+ledPosOffset[14][1] < endY)
        setSectionLed(14, j, r, g, b, w);

  // 15 tube top left
  for(j = 0; j < 90; j++)
    if (tubeCoords[j][0]+ledPosOffset[15][0] > startX && tubeCoords[j][0]+ledPosOffset[15][0] < endX && tubeCoords[j][1]+ledPosOffset[15][1] > startY && tubeCoords[j][1]+ledPosOffset[15][1] < endY)
        setSectionLed(15, j, r, g, b, w);

  // 16 tube top right
  for(j = 0; j < 90; j++)
    if (tubeCoords[j][0]+ledPosOffset[16][0] > startX && tubeCoords[j][0]+ledPosOffset[16][0] < endX && tubeCoords[j][1]+ledPosOffset[16][1] > startY && tubeCoords[j][1]+ledPosOffset[16][1] < endY)
        setSectionLed(16, j, r, g, b, w);

  // 17 left port
  for(j = 0; j < 140; j++)
  {
    int ledPos = j % 19;
    if (portLCoords[ledPos][0]+ledPosOffset[17][0] > startX && portLCoords[ledPos][0]+ledPosOffset[17][0] < endX && portLCoords[ledPos][1]+ledPosOffset[17][1] > startY && portLCoords[ledPos][1]+ledPosOffset[17][1] < endY)
        setSectionLed(17, j, r, g, b, w);
  }

  // 18 right port
  for(j = 0; j < 140; j++)
  {
    int ledPos = j % 19;
    if (portRCoords[ledPos][0]+ledPosOffset[18][0] > startX && portRCoords[ledPos][0]+ledPosOffset[18][0] < endX && portRCoords[ledPos][1]+ledPosOffset[18][1] > startY && portRCoords[ledPos][1]+ledPosOffset[18][1] < endY)
        setSectionLed(18, j, r, g, b, w);
  }


}



