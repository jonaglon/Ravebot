int currentPattern = 1;

void doLights() {

  allOff();
  // allOffBySection();

  if (currentPattern == 1) {
    horizontalRainbow(false, false, 10);
    sectionsInTime2();
    doEyes();
    doTalkingLights();
  } else if (currentPattern == 2) {
    horizontalRainbow(false, false, 10);
  } else {
    horizontalRainbow(false, false, 10);
  }
  LEDS.show();  
}



void horizontalRainbow(bool includeEyes, bool includeMouth, int speedFactor) {
  int ticko = (timey / speedFactor) % 1024;
  int j = 0;
  
  for(j = 0; j < numLeds; j++) {
    int xCoord = (getLCoord(j)+ticko)%1024;
    SetRgbwWheelVars(xCoord/4);
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}

// so we can do x y patterns for each led on the bot we need a lookup
int getLCoord(int j) {
  if (j < 203)
     return binCoords[j][0];
  else if (j < 378)
    return bigHeartCoords[j-203][0];
  else if (j < 463)
    return smHeartCoords[j-378][0];
  else if (j < 482)
    return armCoords[j-463][0];
  else if (j < 506)
    return armCoords[j-482][0];
  else if (j < 599)
    return eyeCoords[j-506][0];
  else if (j < 692)
    return eyeCoords[j-599][0];
  else if (j < 710)
    return horizCoords[j-692][0];
  else if (j < 744)
    return tapeCoords[j-710][0];
  else if (j < 770)
    return horizCoords[j-744][0];
  else if (j < 774)
    return horizCoords[j-770][0];
  else if (j < 797)
    return armCoords[j-774][0];
  else if (j < 821)
    return armCoords[j-797][0];
  else if (j < 911)
    return tubeCoords[j-821][0];
  else if (j < 1001)
    return tubeCoords[j-911][0];
  else if (j < 1090)
    return tubeCoords[j-1001][0];
  else if (j < 1179)
    return tubeCoords[j-1090][0];
  else if (j < 1302)
    return portLCoords[j-1179][0];
  else if (j < 1441)
    return portRCoords[j-1302][0];
  
}

void doLightsLessOld() {

  allOff();
  //allOffBySection();

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

  drawStripeX(3, 200, 255, 0, 0, 0);
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
  
  sectionsInTime();

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
  drawLightsNear(ledSections[5], 55, 55, 30);
  drawLightsNear(ledSections[6], 55, 55, 30);
}


void drawLightsNear(int offSet, int xCoord, int  yCoord, int radius) {

  for(int j = 0; j < 94; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setLedDirect(offSet+j, 0, 0, 0, 0, false);
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



