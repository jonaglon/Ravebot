
void SetRgbwWheel(int pixNum, byte WheelPos, short whiteVal) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    setLedDirect(pixNum, 255 - WheelPos * 3, 0, WheelPos * 3, whiteVal, false);
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    setLedDirect(pixNum, 0, WheelPos * 3, 255 - WheelPos * 3, whiteVal, false);
    return;
  }
  WheelPos -= 170;
  setLedDirect(pixNum, WheelPos * 3, 255 - WheelPos * 3, 0, whiteVal, false);
  return;
}


void SetRgbwWheelVars(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    wheelR = 255 - WheelPos * 3;
    wheelG = 0;
    wheelB = WheelPos * 3;
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    wheelR = 0;
    wheelG = WheelPos * 3;
    wheelB = 255 - WheelPos * 3;
    return;
  }
  WheelPos -= 170;
  wheelR = WheelPos * 3;
  wheelG = 255 - WheelPos * 3;
  wheelB = 0;
  return;
}


void rgbwRainbow(int speedFactor) {
  int ticky = (timey / speedFactor);

  // forward
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    SetRgbwWheel(pixNum, (pixNum + ticky) % 255, 0);
  }
}


int getCoord(int ledNum, int xOrY) {
  if (ledNum < 203)
     return binCoords[ledNum][xOrY]+ledPosOffset[0][xOrY];
  else if (ledNum < 378)
    return bigHeartCoords[ledNum-203][xOrY]+ledPosOffset[1][xOrY];
  else if (ledNum < 463)
    return smHeartCoords[ledNum-378][xOrY]+ledPosOffset[2][xOrY];
  else if (ledNum < 482)
    return armCoords[ledNum-463][xOrY]+ledPosOffset[3][xOrY];
  else if (ledNum < 506)
    return armCoords[ledNum-482][xOrY]+ledPosOffset[4][xOrY];
  else if (ledNum < 599)
    return eyeCoords[ledNum-506][xOrY]+ledPosOffset[5][xOrY];
  else if (ledNum < 692)
    return eyeCoords[ledNum-599][xOrY]+ledPosOffset[6][xOrY];
  else if (ledNum < 710)
    return horizCoords[ledNum-692][xOrY]+ledPosOffset[7][xOrY];
  else if (ledNum < 744)
    return tapeCoords[ledNum-710][xOrY]+ledPosOffset[8][xOrY];
  else if (ledNum < 770)
    return horizCoords[ledNum-744][xOrY]+ledPosOffset[9][xOrY];
  else if (ledNum < 774)
    return horizCoords[ledNum-770][xOrY]+ledPosOffset[10][xOrY];
  else if (ledNum < 797)
    return armCoords[ledNum-774][xOrY]+ledPosOffset[11][xOrY];
  else if (ledNum < 821)
    return armCoords[ledNum-797][xOrY]+ledPosOffset[12][xOrY];
  else if (ledNum < 911)
    return tubeCoords[ledNum-821][xOrY]+ledPosOffset[13][xOrY];
  else if (ledNum < 1001)
    return tubeCoords[ledNum-911][xOrY]+ledPosOffset[14][xOrY];
  else if (ledNum < 1090)
    return tubeCoords[ledNum-1001][xOrY]+ledPosOffset[15][xOrY];
  else if (ledNum < 1179)
    return tubeCoords[ledNum-1090][xOrY]+ledPosOffset[16][xOrY];
  else if (ledNum < 1302)
    return portLCoords[(ledNum-1179)%19][xOrY]+ledPosOffset[17][xOrY];
  else if (ledNum < 1441)
    return portRCoords[(ledNum-1302)%19][xOrY]+ledPosOffset[18][xOrY];
}


int quickAbsolute(int number) {
  if (number < 0)
    return number * (-1);
  else
    return number;
}


void drawSquare(int offSet, int xCoord, int  yCoord, int radius, int r, int g, int b, int w) {
  for(int j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setLedDirect(offSet+j, r, g, b, w, false);
      }
    }
  }
}

//const int pupilRadius=26;
//const int maxRadius=42;
void drawHexagon(int ledNumOffSet, int xCoord, int  yCoord, int pupilRadius, int maxRadius, int r, int g, int b, int w) {
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



void setSection(int section, int r, int g, int b, int w) {
  for(int j = ledSections[section]; j < ledSections[section+1]; j++) { 
    setLedDirect(j, r, g, b, w, true);
  }
}

void setSectionLed(int section, int ledNum, int r, int g, int b, int w) {
  int j = ledSections[section] + ledNum;
  if (j < ledSections[section+1])
    setLedDirect(j, r, g, b, w, true);
}

void everySingleLight(int r, int g, int b, int w) {
  for(int j = 0; j < numLeds; j++) { 
    setLedDirect(j, r, g, b, w, false);
  }
}

void lightEyes(int r, int g, int b, int w) {
  for(int j = 506; j < 693; j++) { 
    setLedDirect(j, r, g, b, w, false);
  }
}

void allOff() {
  for(int j = 0; j < numLeds; j++) {
    setLedDirect(j, 0, 0, 0, 0, true);
  }
}

void allOffBySection() {
  for(int j = 0; j < 19; j++) {
    setSection(j, 0, 0, 0, 0);
  }
}


void setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal, bool showMouth) {
  if (ledNum < 0)
    return;

  //if (ledNum == 506 || ledNum == 507)
  //  return;

  if (ledNum < 203) {
    // Big bottom ring
    setRgbwLed((ledNum+190)%203, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 463) {
    // Body hearts
    setRgbwLed(ledNum+170, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 506) {
    // Left arm
    setRgbwLed(ledNum+275, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 692) {  
    // Eyes!693
    rVal = rVal/ledIntensity;
    gVal = gVal/ledIntensity;
    bVal = bVal/ledIntensity;
    rgbwLeds[ledNum+536].b = gVal % 256;
    rgbwLeds[ledNum+537].g = rVal % 256;
    rgbwLeds[ledNum+537].r = bVal % 256;
  }
  else if (ledNum < 825) {
    if (!showMouth && ledNum < 710) {
      return;
    }
    
    // reverse indicator and tuner direction
    if (ledNum > 744 && ledNum < 774)
      ledNum = 1517-ledNum;

    // Rest of head and right arm
    setRgbwLedAfterEyes(ledNum+230, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 911) {
    // Body tube bottomright - 
    // setRgbwLed(ledNum+282, rVal, gVal, bVal, wVal); - 
    if (ledNum < 866)
      setRgbwLed(1968-ledNum, rVal, gVal, bVal, wVal);
    else
      setRgbwLed(2058-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1001) {
    // Body tube bottomleft
    if (ledNum < 992)
      setRgbwLed(2184-ledNum, rVal, gVal, bVal, wVal);
    else
      setRgbwLed(2274-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1090) {
    // Body tube topleft
    if (ledNum < 1042)
      setRgbwLed(2324-ledNum, rVal, gVal, bVal, wVal);
    else
      setRgbwLed(2413-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1179) {
    // Body tube topright
    if (ledNum < 1160)
      setRgbwLed(2531-ledNum, rVal, gVal, bVal, wVal);
    else
      setRgbwLed(2620-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1442) {
    // Bass holes!
    setRgbwLed(ledNum+285, rVal, gVal, bVal, wVal);
  }
}

void setRgbwLed(int ledNumber, int rVal, int gVal, int bVal, int wVal) {
  int newNumber = (ledNumber * 4) / 3;
  short mod = ledNumber % 3;

  rVal = rVal/ledIntensity;
  gVal = gVal/ledIntensity;
  bVal = bVal/ledIntensity;
  wVal = wVal/ledIntensity;

  if (mod == 0)
  {
    rgbwLeds[newNumber].r = rVal % 256;
    rgbwLeds[newNumber].g = gVal % 256;
    rgbwLeds[newNumber].b = bVal % 256;
    rgbwLeds[newNumber+1].g =wVal % 256;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].r = gVal % 256;
    rgbwLeds[newNumber].b = rVal % 256;
    rgbwLeds[newNumber+1].r =wVal % 256;
    rgbwLeds[newNumber+1].g =bVal % 256;
  }
  else 
  {
    rgbwLeds[newNumber].b = gVal % 256;
    rgbwLeds[newNumber+1].r =bVal % 256;
    rgbwLeds[newNumber+1].g =rVal % 256;
    rgbwLeds[newNumber+1].b =wVal % 256;
  }
}

void setRgbwLedAfterEyes(int ledNumber, int rVal, int gVal, int bVal, int wVal) {
  int newNumber = (ledNumber * 4) / 3;
  short mod = ledNumber % 3;
  
  rVal = rVal/ledIntensity;
  gVal = gVal/ledIntensity;
  bVal = bVal/ledIntensity;
  wVal = wVal/ledIntensity;

  if (mod == 0)
  {
    rgbwLeds[newNumber-1].b = rVal % 256;
    rgbwLeds[newNumber-1].r = gVal % 256;
    rgbwLeds[newNumber].g = bVal % 256;
    rgbwLeds[newNumber].r = wVal % 256;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].g = rVal % 256;
    rgbwLeds[newNumber-1].b = gVal % 256;
    rgbwLeds[newNumber].r = bVal % 256;
    rgbwLeds[newNumber].b = wVal % 256;
  }
  else 
  {
    rgbwLeds[newNumber].r = rVal % 256;
    rgbwLeds[newNumber].g = gVal % 256;
    rgbwLeds[newNumber].b = bVal % 256;
    rgbwLeds[newNumber+1].g = wVal % 256;
  }
}



