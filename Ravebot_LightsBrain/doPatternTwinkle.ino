const short speedDivisor = 64;  /* small numbers equals faster strips! */
int currentTwinklePattern = 0;
int ledToLight;

void doTwinkles() {

  for (int twinky = 0; twinky < usedTwinkleCount[currentTwinklePattern]; twinky++) {

    int newLedNum = myTwinkles[twinky].ledNum;

    if (myTwinkles[twinky].speedy != 0)
    {
        int ticky = (timeyInTime / speedDivisor)/quickAbsolute(myTwinkles[twinky].speedy);
        if (myTwinkles[twinky].speedy < 0) {
          newLedNum = numLedsStrip-((myTwinkles[twinky].ledNum + ticky)%numLedsStrip);
        } else {
          newLedNum = (myTwinkles[twinky].ledNum + ticky)%numLedsStrip;
        }
    }
    
    int twinkLength = myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut;

    if ((timey > (myTwinkles[twinky].start)) && (timey < (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn))) {
      setLedsFadeIn(newLedNum, twinky, false);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn) > animLength) && (timey < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn) % animLength))) {
      setLedsFadeIn(newLedNum, twinky, true);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if ((timey >= (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn)) && (timey < (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy))) {
      setLedsOnFull(newLedNum, twinky, false);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy) > animLength) && (timey < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy) % animLength))) {
      setLedsOnFull(newLedNum, twinky, true);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if ((timey >= (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy)) && (timey < (myTwinkles[twinky].start + twinkLength)) ) {
      setLedsFadeOut(newLedNum, twinky, false);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) > animLength) && (timey < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) % animLength))) {
      setLedsFadeOut(newLedNum, twinky, true);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if ((timey >= (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) % animLength))) && myTwinkles[twinky].hasTwinked) {
      resetTwink(twinky);
    }
  }
}

void setupNewTwinklePattern(int newTwinklePattern) {
  currentTwinklePattern = newTwinklePattern;
  for (int twink = 0; twink < usedTwinkleCount[currentTwinklePattern]; twink++) {
    switch (newTwinklePattern) {
      case 1:
        setupTwinkle1(twink);
        break;
      case 2:
        setupTwinkle2(twink);
        break;
      case 3:
        setupTwinkle3(twink);
        break;
      case 4:
        setupTwinkle4(twink);
        break;
      case 5:
        setupTwinkle5(twink);
        break;
      case 6:
        setupTwinkle6(twink);
        break;
      case 7:
        setupTwinkle7(twink);
        break;
    }
  }
}

void resetTwink(int twink) {
  switch (currentTwinklePattern) {
    case 1:
      setupTwinkle1(twink);
      break;
    case 2:
      setupTwinkle2(twink);
      break;
    case 3:
      setupTwinkle3(twink);
      break;
    case 4:
      setupTwinkle4(twink);
      break;
    case 5:
      setupTwinkle5(twink);
      break;
    case 6:
      setupTwinkle6(twink);
      break;
    case 7:
      setupTwinkle7(twink);
      break;
  }
}


void setLedsFadeIn(int ledNum, int twinky, bool rolledOver) {

  int percentThroughFade = 0;
  if (rolledOver) {
    percentThroughFade = (((timey + animLength) - myTwinkles[twinky].start) * 100) / myTwinkles[twinky].fadeIn;
  } else {
    percentThroughFade = ((timey - myTwinkles[twinky].start) * 100) / myTwinkles[twinky].fadeIn;
  }

  int percentThroughPatternCalc = 0;
  if (rolledOver) {
    percentThroughPatternCalc = ((timey + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughPatternCalc = (timey - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = percentThroughPatternCalc / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);
  
  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    setLedDirectStrip(ledNum + ledToLight, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0);
    setLedDirectStrip(ledNum - ledToLight, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0);
  }
}

void setLedsOnFull(int ledNum, int twinky, bool rolledOver) {

  int percentThroughFade = 0;
  if (rolledOver) {
    percentThroughFade = ((timey + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughFade = (timey - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = percentThroughFade / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);

  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)));
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)));
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)));

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    setLedDirectStrip(ledNum + ledToLight, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0);
    setLedDirectStrip(ledNum - ledToLight, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0);
  }
}


void setLedsFadeOut(int ledNum, int twinky, bool rolledOver) {
  int percentThroughFade = 0;
  int start = (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy);
  int endy = (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);
  if (rolledOver) {
    percentThroughFade = 100 - quickAbsolute((((timey + animLength) - start) * 100) / (endy-start));
  } else {
    percentThroughFade = 100 - quickAbsolute(((timey - start) * 100) / (endy-start));
  }

  int percentThroughPatternCalc = 0;
  if (rolledOver) {
    percentThroughPatternCalc = ((timey + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughPatternCalc = (timey - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = (percentThroughPatternCalc / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut));

  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    setLedDirectStrip(ledNum + ledToLight, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0);
    setLedDirectStrip(ledNum - ledToLight, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0);
  }
}

int findNewStart(int newTwinkleLength) {
  int newRandom = random(0, (animLength - newTwinkleLength));
  return ((timey + newRandom) % animLength);
}

void setupTwinkle1(int twinky) {
  myTwinkles[twinky].ledNum = random(numLedsStrip);
  myTwinkles[twinky].rCol =  random(240);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].rToCol =  random(240);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].lengthy = random(5000,10000);
  myTwinkles[twinky].fadeIn =  700;
  myTwinkles[twinky].fadeOut = 700;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut); 
  myTwinkles[twinky].widthy =  1;
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle2(int twinky) {
  myTwinkles[twinky].ledNum = random(numLedsStrip);
  myTwinkles[twinky].rCol =  random(240);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].rToCol =  random(240);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].lengthy = random(5000,20000);
  myTwinkles[twinky].fadeIn =  random(1000,5000); //
  myTwinkles[twinky].fadeOut = random(1000,5000); // 
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut); 
  myTwinkles[twinky].widthy =  1;
  myTwinkles[twinky].speedy = random(-30, 30);
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle3(int twinky) {
  myTwinkles[twinky].ledNum = random(numLedsStrip);
  myTwinkles[twinky].rCol =  random(220);
  myTwinkles[twinky].gCol =  random(200);
  myTwinkles[twinky].bCol =  random(210);
  myTwinkles[twinky].rToCol = myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].lengthy =  random(2000, 10000);
  myTwinkles[twinky].fadeIn =  random(2000, 5000);
  myTwinkles[twinky].fadeOut =  random(2000, 5000);
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut); 
  myTwinkles[twinky].widthy = random(2,5);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 20;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle4(int twinky) {
  myTwinkles[twinky].ledNum = random(numLedsStrip);
  myTwinkles[twinky].rCol =  random(200);
  myTwinkles[twinky].gCol =  random(180);
  myTwinkles[twinky].bCol =  random(200);
  myTwinkles[twinky].rToCol =  random(200);
  myTwinkles[twinky].gToCol =  random(180);
  myTwinkles[twinky].bToCol =  random(200);
  myTwinkles[twinky].lengthy = random(2000, 5000);
  myTwinkles[twinky].fadeIn =  random(2000, 5000);
  myTwinkles[twinky].fadeOut =  random(2000, 5000);
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut); 
  myTwinkles[twinky].widthy =  random(1, 10);
  myTwinkles[twinky].speedy = random(-20, 20); // larger numbers are slower!
  myTwinkles[twinky].sideFade = 18;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle5(int twinky) {
  myTwinkles[twinky].ledNum = random(numLedsStrip);
  myTwinkles[twinky].rCol =  random(200);
  myTwinkles[twinky].gCol =  random(100);
  myTwinkles[twinky].bCol =  random(150);
  myTwinkles[twinky].rToCol =  myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].lengthy = random(2000, 5000);
  myTwinkles[twinky].fadeIn =  random(2000, 5000);
  myTwinkles[twinky].fadeOut =  random(2000, 5000);
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut); 
  myTwinkles[twinky].widthy =  random(3, 23);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 28;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle6(int twinky) {
  myTwinkles[twinky].ledNum = random(numLedsStrip);
  myTwinkles[twinky].rCol =  random(220);
  myTwinkles[twinky].gCol =  random(170);
  myTwinkles[twinky].bCol =  random(180);
  myTwinkles[twinky].rToCol =  random(170);
  myTwinkles[twinky].gToCol =  random(140);
  myTwinkles[twinky].bToCol =  random(190);
  myTwinkles[twinky].lengthy = random(4000, 10000);
  myTwinkles[twinky].fadeIn =  random(2000, 4000);
  myTwinkles[twinky].fadeOut = random(2000, 4000);
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut); 
  myTwinkles[twinky].widthy =  random(1, 5);
  myTwinkles[twinky].speedy = random(-14, 14); // larger numbers are slower!
  myTwinkles[twinky].sideFade = random(2, 20);
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle7(int twinky) {
  myTwinkles[twinky].ledNum = random(numLedsStrip);
  
  myTwinkles[twinky].rCol =  70;
  myTwinkles[twinky].gCol =  70;
  myTwinkles[twinky].bCol =  70;
  myTwinkles[twinky].rToCol =  110;
  myTwinkles[twinky].gToCol =  110;
  myTwinkles[twinky].bToCol =  110;
  myTwinkles[twinky].lengthy = random(500,1000);
  myTwinkles[twinky].fadeIn =  random(0,800);
  myTwinkles[twinky].fadeOut = random(0,800);
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut); 
  myTwinkles[twinky].widthy =  1;
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;

}

