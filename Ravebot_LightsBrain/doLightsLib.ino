
void sweepTestRainbowTorso(int speedFactor) {
  int j;
  int rainbowFactor = (timey / speedFactor) % 255;

  // forward
  for(int j = 0; j < numLeds; j++) { 
    SetRgbwWheel(j, (rainbowFactor+(j*8)) % 255, 0);
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

