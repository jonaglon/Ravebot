
int ledSections[20] = {
  0,     // 0  bottom ring *
  203,   // 1  big heart
  378,   // 2  small heart
  463,   // 3 underarm left
  482,   // 4 overarm left
  506,   // 5  eye left 
  599,   // 6  eye right
  692,   // 7  mouth
  710,   // 8  tape
  744,   // 9  tuner *
  770,   // 10 indiciator *
  774,   // 11 underarm right
  797,   // 12 overarm right
  821,   // 13 tube bottomright *
  911,   // 14 tube bottomleft *
  1001,  // 15 tube topleft *
  1090,  // 16 tube topright * starred sections are shifted and / or reversed
  1179,  // 17 port left
  1302,  // 18 port right
  1441};

void doLights() {

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
  
  setSection(5, 255, 0, 0, 0);
  setSection(6, 0, 255, 0, 0);
  setSection(7, 0, 0, 255, 0);
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

void setSection(int section, int r, int g, int b, int w) {
  for(int j = ledSections[section]; j < ledSections[section+1]; j++) { 
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
    if (ledNum > 743 && ledNum < 774)
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




