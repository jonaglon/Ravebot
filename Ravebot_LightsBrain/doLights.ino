
void doLights() {
  
  allOff();

  for(int j = 0; j < 78; j++) {
    setRgbwLed(j, 0, 0, 80, 0);
  }
  
  int x = 500;
  /*for(int j = 0; j < 10; j++) {
    setRgbwLed(j+x, 0, 50, 0, 0);
  }*/

  setLedDirect(x + 0, 0, 255, 0, 0);
  setLedDirect(x + 1, 0, 255, 0, 0);
  setLedDirect(x + 2, 0, 255, 0, 0);
  setLedDirect(x + 3, 0, 255, 0, 0);
  setLedDirect(x + 4, 0, 255, 0, 0);
  setLedDirect(x + 5, 0, 255, 0, 0);
  setLedDirect(x + 6, 0, 255, 0, 0);
  setLedDirect(x + 7, 0, 255, 0, 0);
  setLedDirect(x + 8, 0, 255, 0, 0);
  setLedDirect(x + 9, 0, 255, 0, 0);
  
  /* setLedDirect(x + 4, 0, 255, 0, 0);
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
  setLedDirect(x +15, 0, 0, 0, 255); */

  LEDS.show();
}

void setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal) {
  if (ledNum < 0)
    return;

  if (ledNum < 203) // Big bottom ring
    setRgbwLed(ledNum, rVal, gVal, bVal, wVal);
  else if (ledNum < 463) // Body hearts
    setRgbwLed(ledNum+166, rVal, gVal, bVal, wVal);
  else if (ledNum < 507) // Left arm
    setRgbwLed(ledNum+268, rVal, gVal, bVal, wVal);
  else if (ledNum < 9999) // Eyes!
  {    
    rgbwLeds[ledNum+528].r = bVal;
    rgbwLeds[ledNum+528].g = rVal;
    rgbwLeds[ledNum+529].r = gVal;
  }
  
  /*if (ledNum < 882)
    setRgbwLed(ledNum, rVal, gVal, bVal, wVal);
  else if (ledNum < 966)
  {
    rgbwLeds[ledNum+295].b = rVal;
    rgbwLeds[ledNum+295].g = gVal;
    rgbwLeds[ledNum+296].r = bVal;
  }
  else if (ledNum < 1200)
    setRgbwLed(ledNum-42, rVal, gVal, bVal, wVal);
  else if (ledNum < 1966)
  {
    rgbwLeds[ledNum+10].r = rVal;
    rgbwLeds[ledNum+10].g = bVal;
    rgbwLeds[ledNum+9].b = gVal;    
  }*/
                                     
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
  for(int j = 0; j < numLeds; j++) {
    setRgbwLed(j, 0, 0, 0, 0);
  }
}




