
void doLights() {
  
  allOff();
  //everySingleLight();
  //everySingleLightRed();
  //sweepTestRainbowTorso(50);

  /*for(int j = 0; j < 8; j++) {
    setRgbwLed(j, 80, 18, 20, 5);
  }*/
  
  int x = 690;
  for(int j = 0; j < 10; j++) {
    setRgbwLed(j+x, 0, 50, 0, 0);
  }
  setLedDirect(x + 0, 255, 0, 0, 0);
  setLedDirect(x + 1, 255, 0, 0, 0);
  setLedDirect(x + 2, 255, 0, 0, 0);
  setLedDirect(x + 3, 255, 0, 0, 0);

  setLedDirect(x + 4, 0, 255, 0, 0);
  setLedDirect(x + 5, 0, 255, 0, 0);
  setLedDirect(x + 6, 0, 255, 0, 0);
  setLedDirect(x + 7, 0, 255, 0, 0);
  
  setLedDirect(x + 8, 0, 0, 255, 0);
  setLedDirect(x + 9, 0, 0, 255, 0);
  setLedDirect(x +10, 0, 0, 255, 0);
  setLedDirect(x +11, 0, 0, 255, 0);
  
  setLedDirect(x +12, 0, 0, 0, 255);
  setLedDirect(x +13, 0, 0, 0, 255);
  setLedDirect(x +14, 0, 0, 0, 255);
  setLedDirect(x +15, 0, 0, 0, 255);

  //setLedDirect(695, 0, 255, 0, 0);

  LEDS.show();
}

int start=1;
void everySingleLight() {
  int ledNumber = (start / 3) % 3000;
  short mod = ledNumber % 3;
  if (mod == 0)
    rgbwLeds[ledNumber].r = 255;
  else if (mod == 1)
    rgbwLeds[ledNumber].g = 255;
  else 
    rgbwLeds[ledNumber].b = 255;
  start++;
}
void everySingleLightRed() {
  rgbwLeds[start%2440].r = 255;
  start++;
}

void setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal) {
  if (ledNum < 0)
    return;

  if (ledNum < 203)
  {
    // Big bottom ring
    setRgbwLed(ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 463) {
    // Body hearts
    setRgbwLed(ledNum+170, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 507) {
    // Left arm
    setRgbwLed(ledNum+274, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 693) // Eyes!693
  {  
    rgbwLeds[ledNum+535].b = gVal;
    rgbwLeds[ledNum+536].g = rVal;
    rgbwLeds[ledNum+536].r = bVal;
  }
  else if (ledNum < 9999)
  {
    //setRgbwLed(3, 80, 18, 20, 5);
    setRgbwLedAfterEyes(ledNum+229, rVal, gVal, bVal, wVal);
    //setRgbwLedAfterEyes(694, 0, 0, 255, 0);
  }
  else
  {
    return;
  }
                                     
}

void setRgbwLedAfterEyes(int ledNumber, int rVal, int gVal, int bVal, int wVal) {
  int newNumber = (ledNumber * 4) / 3;
  short mod = ledNumber % 3;

  if (mod == 0)
  {
    rgbwLeds[newNumber-1].b = rVal;
    rgbwLeds[newNumber-1].r = gVal;
    rgbwLeds[newNumber].g = bVal;
    rgbwLeds[newNumber].r = wVal;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].g = rVal;
    rgbwLeds[newNumber-1].b = gVal;
    rgbwLeds[newNumber].r = bVal;
    rgbwLeds[newNumber].b = wVal;
  }
  else 
  {
    rgbwLeds[newNumber].r = rVal;
    rgbwLeds[newNumber].g = gVal;
    rgbwLeds[newNumber].b = bVal;
    rgbwLeds[newNumber+1].g = wVal;
  }
}

void setRgbwLed(int ledNumber, int rVal, int gVal, int bVal, int wVal) {
  int newNumber = (ledNumber * 4) / 3;
  short mod = ledNumber % 3;

  if (mod == 0)
  {
    rgbwLeds[newNumber].r = rVal;
    rgbwLeds[newNumber].g = gVal;
    rgbwLeds[newNumber].b = bVal;
    rgbwLeds[newNumber+1].g =wVal;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].r = gVal;
    rgbwLeds[newNumber].b = rVal;
    rgbwLeds[newNumber+1].r =wVal;
    rgbwLeds[newNumber+1].g =bVal;
  }
  else 
  {
    rgbwLeds[newNumber].b = gVal;
    rgbwLeds[newNumber+1].r =bVal;
    rgbwLeds[newNumber+1].g =rVal;
    rgbwLeds[newNumber+1].b =wVal;
  }
}
 
void allOff() {
  for(int j = 0; j < numLeds; j++) { // JR TODO - put num leds here
    setRgbwLed(j, 0, 0, 0, 0);
  }
}




