const short speedDivisor = 64;  /* small numbers equals faster strips! */
int ledToLight;

void doTwinkles() {

  for (int twinky = 0; twinky < usedTwinkleCount[currentPattern]; twinky++) {

    int newLedNum = myTwinkles[twinky].ledNum;

    if (myTwinkles[twinky].speedy != 0)
    {
        int ticky = ((timeyInTime/16) / speedDivisor)/quickAbsolute(myTwinkles[twinky].speedy);
        if (myTwinkles[twinky].speedy < 0) {
          newLedNum = numLeds-((myTwinkles[twinky].ledNum + ticky)%numLeds);
        } else {
          newLedNum = (myTwinkles[twinky].ledNum + ticky)%numLeds;
        }
    }
    
    int twinkLength = myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut;

    if ((twinkleTime > (myTwinkles[twinky].start)) && (twinkleTime < (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn))) {
      setLedsFadeIn(newLedNum, twinky, false);
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn) > animLength) && (twinkleTime < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn) % animLength))) {
      setLedsFadeIn(newLedNum, twinky, true);
    } else if ((twinkleTime >= (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn)) && (twinkleTime < (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy))) {
      setLedsOnFull(newLedNum, twinky, false);
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy) > animLength) && (twinkleTime < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy) % animLength))) {
      setLedsOnFull(newLedNum, twinky, true);
    } else if ((twinkleTime >= (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy)) && (twinkleTime < (myTwinkles[twinky].start + twinkLength)) ) {
      setLedsFadeOut(newLedNum, twinky, false);
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) > animLength) && (twinkleTime < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) % animLength))) {
      setLedsFadeOut(newLedNum, twinky, true);
    } else if ((twinkleTime >= (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) % animLength))) && myTwinkles[twinky].hasTwinked) {
      if (testMode) {
        Serial.print("RESET tw:");
        Serial.print(twinky);
        Serial.print(" oldl:");
        Serial.print(myTwinkles[twinky].ledNum);
      }
      resetTwink(twinky);
      if (testMode) {
        Serial.print("  newl:");
        Serial.print(myTwinkles[twinky].ledNum);
        Serial.print("  twinkleT:");
        Serial.print(twinkleTime);
        Serial.print("  stt:");
        Serial.println(myTwinkles[twinky].start);
      }
    }
  }
}

void setupNewTwinklePattern(int newPattern) {
  for (int twink = 0; twink < usedTwinkleCount[currentPattern]; twink++) {
    switch (newPattern) {
      case 5:
        setupTwinkle1(twink);
        break;
      case 6:
        setupTwinkle2(twink);
        break;
      case 7:
        setupTwinkle3(twink);
        break;
      case 8:
        setupTwinkle4(twink);
        break;
      case 9:
        setupTwinkle5(twink);
        break;
      case 10:
        setupTwinkle6(twink);
        break;
      default:
        setupTwinkle7(twink);
        break;
    }
  }
}

void resetTwink(int twink) {
  switch (currentPattern) {
    case 5:
      setupTwinkle1(twink);
      break;
    case 6:
      setupTwinkle2(twink);
      break;
    case 7:
      setupTwinkle3(twink);
      break;
    case 8:
      setupTwinkle4(twink);
      break;
    case 9:
      setupTwinkle5(twink);
      break;
    case 10:
      setupTwinkle6(twink);
      break;
    default:
      setupTwinkle7(twink);
      break;
  }
}


void setLedsFadeIn(int ledNum, int twinky, bool rolledOver) {

  int percentThroughFade = 0;
  if (rolledOver) {
    percentThroughFade = (((twinkleTime + animLength) - myTwinkles[twinky].start) * 100) / myTwinkles[twinky].fadeIn;
  } else {
    percentThroughFade = ((twinkleTime - myTwinkles[twinky].start) * 100) / myTwinkles[twinky].fadeIn;
  }

  int percentThroughPatternCalc = 0;
  if (rolledOver) {
    percentThroughPatternCalc = ((twinkleTime + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughPatternCalc = (twinkleTime - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = percentThroughPatternCalc / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);
  
  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  if (testMode)
    showTestTwink('S' ,rolledOver, twinkleTime, twinky, myTwinkles[twinky].ledNum, percentThroughFade, percentThroughPattern, newRed, newGreen, newBlue);
  
  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    int offsetPlus = ledNum + ledToLight;
    int offsetMinus = ledNum - ledToLight;
    if (rainbowTwinkleMode) {
      setLedDirect(offsetPlus, returnRainbowColor(offsetPlus, minusFade, newRed), returnRainbowColor(offsetPlus, minusFade, newGreen), returnRainbowColor(offsetPlus, minusFade, newBlue), 0, false);
      setLedDirect(offsetMinus, returnRainbowColor(offsetMinus, minusFade, newRed), returnRainbowColor(offsetMinus, minusFade, newGreen), returnRainbowColor(offsetMinus, minusFade, newBlue), 0, false);
    } else {
      setLedDirect(offsetPlus, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0, false);
      setLedDirect(offsetMinus, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0, false);
    }
  }
  if (!myTwinkles[twinky].hasTwinked)
    myTwinkles[twinky].hasTwinked = true;
}

void setLedsOnFull(int ledNum, int twinky, bool rolledOver) {

  int percentThroughFade = 0;
  if (rolledOver) {
    percentThroughFade = ((twinkleTime + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughFade = (twinkleTime - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = percentThroughFade / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);

  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)));
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)));
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)));

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  if (testMode)
    showTestTwink('M' ,rolledOver, twinkleTime, twinky, myTwinkles[twinky].ledNum, percentThroughFade, percentThroughPattern, newRed, newGreen, newBlue);

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    int offsetPlus = ledNum + ledToLight;
    int offsetMinus = ledNum - ledToLight;
    if (rainbowTwinkleMode) {
      setLedDirect(offsetPlus, returnRainbowColor(offsetPlus, minusFade, newRed), returnRainbowColor(offsetPlus, minusFade, newGreen), returnRainbowColor(offsetPlus, minusFade, newBlue), 0, false);
      setLedDirect(offsetMinus, returnRainbowColor(offsetMinus, minusFade, newRed), returnRainbowColor(offsetMinus, minusFade, newGreen), returnRainbowColor(offsetMinus, minusFade, newBlue), 0, false);
    } else {
      setLedDirect(offsetPlus, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0, false);
      setLedDirect(offsetMinus, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0, false);
    }
  }
  if (!myTwinkles[twinky].hasTwinked)
    myTwinkles[twinky].hasTwinked = true;
}


void setLedsFadeOut(int ledNum, int twinky, bool rolledOver) {
  int percentThroughFade = 0;
  int start = (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy);
  int endy = (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);
  if (rolledOver) {
    percentThroughFade = 100 - quickAbsolute((((twinkleTime + animLength) - start) * 100) / (endy-start));
  } else {
    percentThroughFade = 100 - quickAbsolute(((twinkleTime - start) * 100) / (endy-start));
  }

  int percentThroughPatternCalc = 0;
  if (rolledOver) {
    percentThroughPatternCalc = ((twinkleTime + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughPatternCalc = (twinkleTime - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = (percentThroughPatternCalc / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut));

  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  if (testMode)
    showTestTwink('E' ,rolledOver, twinkleTime, twinky, myTwinkles[twinky].ledNum, percentThroughFade, percentThroughPattern, newRed, newGreen, newBlue);

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    int offsetPlus = ledNum + ledToLight;
    int offsetMinus = ledNum - ledToLight;
    if (rainbowTwinkleMode) {
      setLedDirect(offsetPlus, returnRainbowColor(offsetPlus, minusFade, newRed), returnRainbowColor(offsetPlus, minusFade, newGreen), returnRainbowColor(offsetPlus, minusFade, newBlue), 0, false);
      setLedDirect(offsetMinus, returnRainbowColor(offsetMinus, minusFade, newRed), returnRainbowColor(offsetMinus, minusFade, newGreen), returnRainbowColor(offsetMinus, minusFade, newBlue), 0, false);
    } else {
      // setLedDirect(int ledNum, int rVal, int gVal, int bVal, int wVal, bool showMouth)
      setLedDirect(offsetPlus, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0, false);
      setLedDirect(offsetMinus, newRed-minusFade, newGreen-minusFade, newBlue-minusFade, 0, false);
    }
  }
  if (!myTwinkles[twinky].hasTwinked)
    myTwinkles[twinky].hasTwinked = true;
}


int findNewStart(int newTwinkleLength) {
  int newRandom = random(0, (animLength - newTwinkleLength));
  return ((twinkleTime + newRandom) % animLength);
}

int findNewStartInTime() {
  int randomTime = random(32);
  return 16384*randomTime;
}

int findNewStartInTime2() {
  int randomTing = random(3);
  if (randomTing == 0) {
    int randomTime = random(8);
    return 65536*randomTime;
  } else {
    int randomTime = random(32);
    return 16384*randomTime;
  }
}

int findLengthInTime() {
  int randomTing = random(3);
  if (randomTing == 0) {
    return 16384;
  } else if (randomTing == 1) {
    return 32768;
  } else if (randomTing == 2) {
    return 65536;
  } else if (randomTing == 3) {
    return 131072;
  }
}

byte returnRainbowColor(int offset, int minusFade, byte wheelCol) {
  return ((wheelCol-minusFade)+offset)%255;
}


void setupTwinkle1(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(240);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].rToCol =  random(240);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].lengthy = 65536;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut = 0;
  myTwinkles[twinky].start = findNewStartInTime2();
  myTwinkles[twinky].widthy =  1;
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle2(int twinky) {

  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(240);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].rToCol =  random(240);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].lengthy = findLengthInTime();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut = 0;
  myTwinkles[twinky].start = findNewStartInTime2();
  myTwinkles[twinky].widthy =  1;
  myTwinkles[twinky].speedy = random(-30, 30);
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle3(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(220);
  myTwinkles[twinky].gCol =  random(200);
  myTwinkles[twinky].bCol =  random(210);
  myTwinkles[twinky].rToCol = myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].lengthy = 65536;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  random(2000, 5000);
  myTwinkles[twinky].start = findNewStartInTime2(); // findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut,false); 
  myTwinkles[twinky].widthy = random(2,5);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 20;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle4(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(200);
  myTwinkles[twinky].gCol =  random(180);
  myTwinkles[twinky].bCol =  random(200);
  myTwinkles[twinky].rToCol =  random(200);
  myTwinkles[twinky].gToCol =  random(180);
  myTwinkles[twinky].bToCol =  random(200);
  myTwinkles[twinky].lengthy = findLengthInTime();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  random(2000, 5000);
  myTwinkles[twinky].start = findNewStartInTime2(); 
  myTwinkles[twinky].widthy =  random(1, 10);
  myTwinkles[twinky].speedy = random(-20, 20); // larger numbers are slower!
  myTwinkles[twinky].sideFade = 18;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle5(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(200);
  myTwinkles[twinky].gCol =  random(100);
  myTwinkles[twinky].bCol =  random(150);
  myTwinkles[twinky].rToCol =  myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].lengthy = findLengthInTime();
  myTwinkles[twinky].fadeIn =  random(0, 2000);
  myTwinkles[twinky].fadeOut =  random(2000, 5000);
  myTwinkles[twinky].start = findNewStartInTime2(); 
  myTwinkles[twinky].widthy =  random(3, 23);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 28;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle6(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(220);
  myTwinkles[twinky].gCol =  random(170);
  myTwinkles[twinky].bCol =  random(180);
  myTwinkles[twinky].rToCol =  random(170);
  myTwinkles[twinky].gToCol =  random(140);
  myTwinkles[twinky].bToCol =  random(190);
  myTwinkles[twinky].lengthy = findLengthInTime();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut = random(2048);
  myTwinkles[twinky].start = findNewStartInTime2(); 
  myTwinkles[twinky].widthy =  random(1, 5);
  myTwinkles[twinky].speedy = random(-14, 14); // larger numbers are slower!
  myTwinkles[twinky].sideFade = random(2, 20);
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle7(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  
  myTwinkles[twinky].rCol =  70;
  myTwinkles[twinky].gCol =  70;
  myTwinkles[twinky].bCol =  70;
  myTwinkles[twinky].rToCol =  110;
  myTwinkles[twinky].gToCol =  110;
  myTwinkles[twinky].bToCol =  110;
  myTwinkles[twinky].lengthy = random(2048);
  myTwinkles[twinky].fadeIn =  random(0);
  myTwinkles[twinky].fadeOut = random(4000);
  myTwinkles[twinky].start = findNewStartInTime2(); // findNewStart(myTwinkles[twinky].fadeIn+myTwinkles[twinky].lengthy+myTwinkles[twinky].fadeOut,false); 
  myTwinkles[twinky].widthy =  random(3);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}


void showTestTwink(char state ,bool rolledOver, int twinkleTime, int twinky, int ledNum, int percentThroughFade, int percentThroughPattern, int newRed, int newGreen, int newBlue) {
    if (rolledOver)
      Serial.print(".");
    else
      Serial.print(" ");
    Serial.print(state);
    Serial.print("  tt:");
    Serial.print(twinkleTime);
    Serial.print("  tit:");
    Serial.print(timeyInTime);
    Serial.print("  tw:");
    Serial.print(twinky);
    Serial.print("  ln:");
    Serial.print(ledNum);
    Serial.print("  f:");
    Serial.print(percentThroughFade);
    Serial.print("%  p:");
    Serial.print(percentThroughPattern);
    Serial.print("%   r:");
    Serial.print(newRed);
    Serial.print("   b:");
    Serial.print(newBlue);
    Serial.print("   g:");
    Serial.println(newGreen);

  
}
 
