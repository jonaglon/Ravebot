
void doLights() {
  
  allOff();

  // make the first led red
  setLedDirect(1, 255, 0, 0, 0);
  
  eyeSweep(10);

  LEDS.show();
}

void eyeSweep(int speedFactor) {
  int rainbowFactor = (timey / speedFactor) % 44;

  for(int j = 0; j < 94; j++) { 
    if (eyeCoords[j][0] < rainbowFactor) {
      setLedDirect(j, 255, 0, 0, 0);
    } else {
      setLedDirect(j, 0, 255, 0, 0);
    }
  }
}


void everySingleLight(int r, int g, int b, int w) {
  for(int j = 0; j < 93; j++) { 
    allOff();
    setLedDirect(j, r, g, b, w);
    LEDS.show();
    //delay(100);
  }
}

void allOff() {
  for(int j = 0; j < numLeds; j++) {
    rgbwLeds[j].r = 0;
    rgbwLeds[j].g = 0;
    rgbwLeds[j].b = 0;  }
}

// There are no white leds on the eyes but leave this in please
// There is one more rule - no fractions if possible - just use ints!
void setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal) {
    rgbwLeds[ledNum].r = rVal % 256;
    rgbwLeds[ledNum].g = gVal % 256;
    rgbwLeds[ledNum].b = bVal % 256;
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




