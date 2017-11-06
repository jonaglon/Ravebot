int ledSections[20] = {0,203,347,453,553,603,700,800,900,1000,1050,1100,1200,1250,1300,1325,1350,1375,1400,1441};

void doLights() {
  
  allOff();
  
  //lightEyes(25, 25, 200, 10);
  
  //everySingleLight(200, 0, 0, 0);

  sweepTestRainbowTorso(20);

  setSection(0, 0, 0, 0, 255);
  setSection(1, 255, 0, 0, 0);
  setSection(2, 0, 255, 0, 0);
  //setSection(3, 0, 0, 255, 0);
  setSection(4, 0, 0, 0, 255);
  
  setSection(5, 255, 0, 0, 0);
  //setSection(6, 0, 255, 0, 0);
  setSection(7, 0, 0, 255, 0);
  setSection(8, 0, 0, 0, 255);
  
  setSection(9, 255, 0, 0, 0);
  setSection(10, 0, 255, 0, 0);
  //setSection(11, 0, 0, 255, 0);
  setSection(12, 0, 0, 0, 255);
  
  setSection(13, 255, 0, 0, 0);
  setSection(14, 0, 255, 0, 0);
  setSection(15, 0, 0, 255, 0);
  setSection(16, 0, 0, 0, 255);
  
  setSection(17, 0, 255, 0, 0);
  setSection(18, 0, 255, 0, 0); 

  LEDS.show();
}

void setSection(int section, int r, int g, int b, int w) {
  
  // bottom ring
  // underarm left
  // overarm left
  // eye left 
  // eye right
  // mouth
  // tape
  // tuner
  // indiciator
  // overarm right
  // underarm right
  // big heart
  // small heart
  // tube topleft
  // tube topright
  // tube bottomleft
  // tube bottomright
  // port left
  // port right
  
  for(int j = ledSections[section]; j < ledSections[section+1]+1; j++) { 
    setLedDirect(j, r, g, b, w);
  }
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


void setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal) {
  if (ledNum < 0)
    return;

  //if (ledNum == 506 || ledNum == 507)
  //  return;

  if (ledNum < 203)
  {
    // Big bottom ring
    setRgbwLed(ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 463) {
    // Body hearts
    setRgbwLed(ledNum+170, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 506) {
    // Left arm
    setRgbwLed(ledNum+275, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 692) 
  {  
    // Eyes!693
    rgbwLeds[ledNum+536].b = gVal % 256;
    rgbwLeds[ledNum+537].g = rVal % 256;
    rgbwLeds[ledNum+537].r = bVal % 256;
  }
  else if (ledNum < 821)
  {
    // Rest of head and right arm
    setRgbwLedAfterEyes(ledNum+230, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1179)
  {
    // Body tubes
    setRgbwLed(ledNum+282, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1442)
  {
    // Bass holes!
    setRgbwLed(ledNum+285, rVal, gVal, bVal, wVal);
  }
                                     
}

void setRgbwLed(int ledNumber, int rVal, int gVal, int bVal, int wVal) {
  int newNumber = (ledNumber * 4) / 3;
  short mod = ledNumber % 3;

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




