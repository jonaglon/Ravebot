int numLedsSet[9] = {84, 11, 18, 84, 11, 34, 4, 24, 120};

void OLDOLDOLDOLD_doRgbwLights()
{
  //rgbwSnake();

  //rgbwRainbow(10);

  //solidHeadColors();

  //rgbwRainbow(40);

  //doTapePattern(80);  

  //rgbwRainbow(20);

  /* drawMovingStripe(60, 300, 1, 10, 0, 100, 0, 0,  0);
  drawMovingStripe(30, 350, 2, 50, 0, 0, 100,  0, 0);
  drawMovingStripe(23, 500, 3, 10, 12, 0, 0,120,  0);
  drawMovingStripe(12, 400, 2, 15, 12, 0, 80,30,  0);
  drawMovingStripe(22, 200, 4, 20, 24, 20, 30,  80,0);
  drawMovingStripe(40, 250, 3, 5, 24,  30, 80,  0,  0);

  //drawMovingStripe(6, 12, 4, 5, 0, 255, 0, 0, 0);
  //drawMovingStripe(32, 166, 3, 20, 0, 255, 0, 0, 0);
  //drawMovingStripe(60, 199, 2, 25, 12, 130, 130, 0, 0);
  //drawMovingStripe(25, 990, 1, 12, 12, 0, 130, 130, 0);
  //drawMovingStripe(12, 220, 4, 4, 24, 0, 0, 0, 255);
  //drawMovingStripe(12, 220, 3, 20, 24, 0, 0, 0, 255); */

   //quarterLights(500);

  //doTalkingLights();

  //tubeTest();

}


void tubeTest() {
  //for (int pixNum = 0; pixNum < 20; pixNum++) {
  //  setLedDirect(270, 255, 0, 0, 0);
  //}
  setLedDirect(271, 0, 0 , 0, 255);
  setLedDirect(274, 0, 0, 0, 255);
}

void drawMovingStripe(int speedFactor, int animationSteps, int stripeDirection, int stripeLength, int offset, int r, int g, int b, int w) {

  int thisFrame = ((timey / speedFactor) % animationSteps) + offset;

  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    if (sweepPatterns[pixNum][stripeDirection] > 0)
      if (thisFrame > sweepPatterns[pixNum][stripeDirection] && thisFrame < (sweepPatterns[pixNum][stripeDirection]+stripeLength))
        setLedDirect(pixNum, r, g, b, w);
  }
}

void drawMovingStripeRev(int speedFactor, int animationSteps, int stripeDirection, int stripeLength, int offset, int r, int g, int b, int w) {

  int thisFrame = ((timey / speedFactor) % animationSteps) + offset;

  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    if (sweepPatterns[pixNum][stripeDirection] > 0)
      if ((animationSteps-thisFrame) > sweepPatterns[pixNum][stripeDirection] && ((animationSteps-thisFrame) < sweepPatterns[pixNum][stripeDirection] + stripeLength))
        setLedDirect(pixNum, r, g, b, w);
  }
}


void sweepTestThree(int speedFactor) {
  int j, pixNum;

  int thisFrame = (timey / speedFactor) % 122;

  // forward
  for (pixNum = 0; pixNum < 270; pixNum++) {
    if (thisFrame > sweepPatterns[pixNum][4] && thisFrame < sweepPatterns[pixNum][4]+20)
      setLedDirect(pixNum, 0, 0, 255, 0);
  }

}

void sweepTestRainbow(int speedFactor) {
  int j, pixNum;

  int thisFrame = (timey / speedFactor) % 130;

  int rainbowFactor = (timey / 5) % 255;

  // forward
  for (pixNum = 0; pixNum < 270; pixNum++) {
    if (thisFrame > sweepPatterns[pixNum][4] && thisFrame < sweepPatterns[pixNum][4]+20)
      SetRgbwWheel(pixNum, rainbowFactor, 20);
  }
}


void doTapePattern(int speedFactor) {
  int animSteps = 224;

  int ticky = (timey / speedFactor) % animSteps;

  for (int i = 0; i < 122; i++)
  {
    //setLedBySet(tapePattern[(ticky+i)%animSteps][0], tapePattern[(ticky+i)%animSteps][1], 255, 0, 0, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i)%animSteps][0], tapePattern[(ticky+i)%animSteps][1], i, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i+56)%animSteps][0], tapePattern[(ticky+i+56)%animSteps][1], (i+80) % animSteps, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i+112)%animSteps][0], tapePattern[(ticky+i+112)%animSteps][1], (i+160) % animSteps, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i+168)%animSteps][0], tapePattern[(ticky+i+168)%animSteps][1], (i+240) % animSteps, 0);
  } 
}

void rgbwRainbow(int speedFactor) {

  int ticky = (timey / speedFactor);

  // forward
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    SetRgbwWheel(pixNum, (pixNum + ticky) % 255, 0);
  }
}

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

void SetRgbwWheelSet(int ledSet, int pixNum, byte WheelPos, short whiteVal) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    setLedBySet(ledSet, pixNum, 255 - WheelPos * 3, 0, WheelPos * 3, whiteVal);
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    setLedBySet(ledSet, pixNum, 0, WheelPos * 3, 255 - WheelPos * 3, whiteVal);
    return;
  }
  WheelPos -= 170;
  setLedBySet(ledSet, pixNum, WheelPos * 3, 255 - WheelPos * 3, 0, whiteVal);
  return;
}

int test=0;
void rgbwSnake() {
  setLedDirect((test % numLeds) + 4, 40, 10, 10, 5);
  setLedDirect((test % numLeds) + 3, 80, 10, 0, 50);
  setLedDirect((test % numLeds) + 2, 80, 10, 0, 60);
  setLedDirect((test % numLeds) + 1, 120, 10, 0, 50);
  setLedDirect((test % numLeds) + 0, 0, 0, 0, 0);
  test++;
}




void solidHeadColors() {

  /*for(int j = 0; j < numLedsSet[0]; j++) {
    setLedBySet(0, j, 255, 0, 255, 0);
  }

  for(int j = 0; j < numLedsSet[1]; j++) {
    setLedBySet(1, j, 0, 255, 0, 0);
  }

  for(int j = 0; j < numLedsSet[2]; j++) {
    setLedBySet(2, j, 150, 30, 0, 0);
  }

  for(int j = 0; j < numLedsSet[3]; j++) {
    setLedBySet(3, j, 0, 0, 100, 0);
  }

  for(int j = 0; j < numLedsSet[4]; j++) {
    setLedBySet(4, j, 2, 0, 0, 255);
  }

  for(int j = 0; j < numLedsSet[5]; j++) {
    setLedBySet(5, j, 255, 0, 0, 0);
  }

  for(int j = 0; j < numLedsSet[6]; j++) {
    setLedBySet(6, j, 0, 80, 0, 0);
  }

  for(int j = 0; j < numLedsSet[7]; j++) {
    setLedBySet(7, j, 0, 0, 255, 0);
  }

  for(int j = 0; j < numLedsSet[8]; j++) {
    setLedBySet(8, j, 0, 0, 0, 255);
  }*/
  for(int j = 0; j < numLedsSet[8]; j++) {
    setLedBySet(8, j, 255, 0, 0, 0);
  }  
}

/* 0  - RGB   Left Eye Outer  84
 * 1  - RGBW  Left Eye Inner  11
 * 2  - RGBW  Mouth           18
 * 3  - RGB   Right Eye Outer 84
 * 4  - RGBW  Right Eye Inner 11
 * 5  - RGBW  Casette         34
 * 6  - RGBW  4                4
 * 7  - RGBW  Dial            24       */
void setLedBySet(int ledSet, int ledNum, int rVal, int gVal, int bVal, int wVal)
{
  if (ledNum < 0)
    return;

  if (ledSet == 0 && ledNum < numLedsSet[0])
    setLedDirect(ledNum, rVal, gVal, bVal, wVal);
  else if (ledSet == 1 && ledNum < numLedsSet[1])
    setLedDirect(ledNum + 84, rVal, gVal, bVal, 0);
  else if (ledSet == 2 && ledNum < numLedsSet[2])
    setLedDirect(ledNum + 95, rVal, gVal, bVal, wVal);
  else if (ledSet == 3 && ledNum < numLedsSet[3])
    setLedDirect(ledNum + 113, rVal, gVal, bVal, 0);
  else if (ledSet == 4 && ledNum < numLedsSet[4])
    setLedDirect(ledNum + 197, rVal, gVal, bVal, wVal);
  else if (ledSet == 5 && ledNum < numLedsSet[5])
    setLedDirect(ledNum + 208, rVal, gVal, bVal, wVal);
  else if (ledSet == 6 && ledNum < numLedsSet[6])
    setLedDirect(ledNum + 242, rVal, gVal, bVal, wVal);
  else if (ledSet == 7 && ledNum < numLedsSet[7])
    setLedDirect(ledNum + 246, rVal, gVal, bVal, wVal);
  else if (ledSet == 8 && ledNum < numLedsSet[8])
    setLedDirect(ledNum + 270, rVal, gVal, bVal, wVal);
}


void setLed(int ledNum, int rVal, int gVal, int bVal, int wVal)
{
  setLedDirect(ledNum, rVal, gVal, bVal, wVal);
}

void setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal)
{
  if (true) 
  {
    setRgbwLedNoGhettoHead(ledNum, rVal, gVal, bVal, wVal);
  }
  else 
  {
    setLedDirectGhettoHead(ledNum, rVal, gVal, bVal, wVal);
  }  
}

void setLedDirectGhettoHead(int ledNum, int rVal, int gVal, int bVal, int wVal)
{
  if (ledNum < 0)
    return;
  
  if (ledNum < 84)
  {
    rgbwLeds[ledNum].r = gVal;
    rgbwLeds[ledNum].g = rVal;
    rgbwLeds[ledNum].b = bVal;
  }
  else if (ledNum < 113)
    setRgbwLedGhettoHead(ledNum-21, rVal, gVal, bVal, wVal);
  else if (ledNum < 197)
  {
    rgbwLeds[ledNum+10].r = rVal;
    rgbwLeds[ledNum+10].g = bVal;
    rgbwLeds[ledNum+9].b = gVal;    
  }
  else
    setRgbwLedGhettoHead(ledNum-42, rVal, gVal, bVal, wVal);
                                     
}

void setRgbwLedNoGhettoHead(int ledNumber, int rVal, int gVal, int bVal, int wVal)
{
  int newNumber = (ledNumber * 4) / 3;
  short mod = ledNumber % 3;

  if (mod == 0)
  {
    rgbwLeds[newNumber].r = gVal;
    rgbwLeds[newNumber].g = rVal;
    rgbwLeds[newNumber].b = bVal;
    rgbwLeds[newNumber+1].r =wVal;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].g = gVal;
    rgbwLeds[newNumber].b = rVal;
    rgbwLeds[newNumber+1].r =bVal;
    rgbwLeds[newNumber+1].g =wVal;
  }
  else 
  {
    rgbwLeds[newNumber].b = gVal;
    rgbwLeds[newNumber+1].r =rVal;
    rgbwLeds[newNumber+1].g =bVal;
    rgbwLeds[newNumber+1].b =wVal;
  }
}

void setRgbwLedGhettoHead(int ledNumber, int rVal, int gVal, int bVal, int wVal)
{
  int newNumber = (ledNumber * 4) / 3;
  short mod = ledNumber % 3;

  if (mod == 0)
  {
    rgbwLeds[newNumber].r = gVal;
    rgbwLeds[newNumber].g = rVal;
    rgbwLeds[newNumber].b = bVal;
    rgbwLeds[newNumber+1].r =wVal;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].g = gVal;
    rgbwLeds[newNumber].b = rVal;
    rgbwLeds[newNumber+1].r =bVal;
    rgbwLeds[newNumber+1].g =wVal;
  }
  else 
  {
    rgbwLeds[newNumber].b = gVal;
    rgbwLeds[newNumber+1].r =rVal;
    rgbwLeds[newNumber+1].g =bVal;
    rgbwLeds[newNumber+1].b =wVal;
  }
}


void allOn() {
  for(int j = 0; j < numLeds; j++) {
    setLedDirect(j, 255, 255, 255, 255);
  }
}

void allOff() {
  for(int j = 0; j < numLeds; j++) {
    setLedDirect(j, 0, 0, 0, 0);
  }
}




