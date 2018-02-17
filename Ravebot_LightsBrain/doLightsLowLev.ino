
void SetRgbwWheel(int pixNum, byte WheelPos, short whiteVal) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    setLedDirect(pixNum, 255 - WheelPos * 3, 0, WheelPos * 3, whiteVal);
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    setLedDirect(pixNum, 0, WheelPos * 3, 255 - WheelPos * 3, whiteVal);
    return;
  }
  WheelPos -= 170;
  setLedDirect(pixNum, WheelPos * 3, 255 - WheelPos * 3, 0, whiteVal);
  return;
}

void doTalkingLights() {

  if (robotTalking) {
    setLedDirect(ledSections[7]+8, 255, 60, 60, 100);
    setLedDirect(ledSections[7]+9, 255, 60, 60, 100);
    
    if (timey > (robotTalkingOnTime + 40)) {
      setLedDirect(ledSections[7]+7, 255, 60, 60, 100);
      setLedDirect(ledSections[7]+10, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 80)) {
      setLedDirect(ledSections[7]+6, 255, 60, 60, 100);
      setLedDirect(ledSections[7]+11, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 110)) {
      setLedDirect(ledSections[7]+5, 255, 60, 60, 100);
      setLedDirect(ledSections[7]+12, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 135)) {
      setLedDirect(ledSections[7]+4, 255, 60, 60, 100);
      setLedDirect(ledSections[7]+13, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 150)) {
      setLedDirect(ledSections[7]+3, 255, 60, 60, 100);
      setLedDirect(ledSections[7]+14, 255, 60, 60, 100);
    }
  }
  
}

void rgbwRainbow(int speedFactor) {

  int ticky = (timey / speedFactor);

  // forward
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    SetRgbwWheel(pixNum, (pixNum + ticky) % 255, 0);
  }
}

void rgbwSnake(int offSet, int speedFactor) {

  int rainbowFactor = (timey / speedFactor);

  /*setLedDirect((test % numLeds) + 4 + offSet, 255, 10, 10, 5);
  setLedDirect((test % numLeds) + 3 + offSet, 80, 155, 0, 50);
  setLedDirect((test % numLeds) + 2 + offSet, 80, 10, 255, 60);
  setLedDirect((test % numLeds) + 1 + offSet, 120, 10, 0, 255);*/
  setLedDirect((rainbowFactor + 4 + offSet) % numLeds, 0, 0, 0, 0);
  setLedDirect((rainbowFactor + 3 + offSet) % numLeds, 0, 0, 0, 0);
  setLedDirect((rainbowFactor + 2 + offSet) % numLeds, 0, 0, 0, 0);
  setLedDirect((rainbowFactor + 1 + offSet) % numLeds, 0, 0, 0, 0);
  setLedDirect((rainbowFactor + offSet) % numLeds, 0, 0, 0, 0);

}

void setSection(int section, int r, int g, int b, int w) {
  for(int j = ledSections[section]; j < ledSections[section+1]; j++) { 
    setLedDirect(j, r, g, b, w);
  }
}

void setSectionLed(int section, int ledNum, int r, int g, int b, int w) {
  int j = ledSections[section] + ledNum;
  if (j < ledSections[section+1])
    setLedDirect(j, r, g, b, w);
}

void everySingleLight(int r, int g, int b, int w) {
  for(int j = 0; j < numLeds; j++) { 
    setLedDirect(j, r, g, b, w);
  }
}

void lightEyes(int r, int g, int b, int w) {
  for(int j = 506; j < 693; j++) { 
    setLedDirect(j, r, g, b, w);
  }
}

void allOff() {
  for(int j = 0; j < numLeds; j++) {
    setLedDirect(j, 0, 0, 0, 0);
  }
}

void allOffBySection() {
  for(int j = 0; j < 19; j++) {
    setSection(j, 0, 0, 0, 0);
  }
}


void setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal) {
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
    rgbwLeds[ledNum+536].b = gVal % 256;
    rgbwLeds[ledNum+537].g = rVal % 256;
    rgbwLeds[ledNum+537].r = bVal % 256;
  }
  else if (ledNum < 825) {
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



