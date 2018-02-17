
void doLights() {

  allOff();
  //allOffBySection();

  drawMovingPattern(3);
  
  //sectionsInTime();

  /*rgbwSnake(0, 10);   // crawling with ants!
  rgbwSnake(100, 5);
  rgbwSnake(200, 20);
  rgbwSnake(1100, 15);
  rgbwSnake(1200, 10);*/

  LEDS.show();
}

void drawMovingPattern(int speedFactor) {

  int ticko = (timey / speedFactor) % 2000;

  drawLightsBetween(0, 800, 0, ticko, true, true, 60, 80, 200, 120);
  
}

void doLightsOld() {

  allOff();

  //setLedDirect(7, 255 , 0, 0, 0);
  
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
  drawLightsNear(ledSections[5], 55, 55, 35);
  drawLightsNear(ledSections[6], 55, 55, 35);
}


void drawLightsNear(int offSet, int xCoord, int  yCoord, int radius) {

  for(int j = 0; j < 94; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setLedDirect(offSet+j, 0, 100, 200, 0);
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


void drawLightsBetween(int startX, int endX, int startY, int endY, bool includeEyes, bool includeMouth, int r, int g, int b, int w) {
  int j = 0;
  
  // 0 bottomRing
  // 1 bigHeart
  // 2 smallHeart

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

}



