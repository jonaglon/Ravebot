
void sweepTestRainbowTorso(int speedFactor) {
  int j;
  int rainbowFactor = (timey / speedFactor) % 255;

  // forward
  for(int j = 0; j < numLeds; j++) { 
    SetRgbwWheel(j, (rainbowFactor+(j)) % 255, 0);
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



