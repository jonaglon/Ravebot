int lastDropCountdown;

void doLights() {

  allOff();

  //lightsInTime();

  //beatLights();

  //doTalkingLights();
  
  /*setLedDirect(12, 255, 0, 0, 0);
  setLedDirect(13, 0, 255, 0, 0);
  setLedDirect(14, 0, 0, 255, 0);
  setLedDirect(15, 0, 0, 0, 255);   */

  //rgbwRainbow(10);

  //rgbwSnake();
  bassBinRainbow(5);
  LEDS.show();

}

void bassBinRainbow(int speedFactor)
{
  int thisFrame = (timey / speedFactor) % 255;
  
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    SetRgbwWheel(pixNum, (thisFrame + (pixNum * 2)) % 255, 0);
  }

}




void lightsInTime() {

  int thisFrame = sixteenth % 4;

  for (int pixNum = 0; pixNum < 95; pixNum++) {
    if (rightEyeQuartAnim[thisFrame][pixNum]) {
      if (currentBar % 4 == 0) {
        setLedDirect(pixNum, 255, 255, 255, 255);
      } else if (currentBar % 4 == 1) {
        setLedDirect(pixNum, 255, 0, 0, 0);
      } else if (currentBar % 4 == 2) {
        setLedDirect(pixNum, 0, 255, 0, 0);
      } else if (currentBar % 4 == 3) { 
        setLedDirect(pixNum, 0, 0, 255, 0);
      };
    }
  }
  
  if (dropCountdown == 0)
    LEDS.setBrightness(64);
  else 
    LEDS.setBrightness(dropCountdown*4);
}

void beatLights() {

  if (timey - beatTimes[0] < 255) {
    int ledValue = (beatTimes[0] + 255)-timey;
    setLedDirect(dropCountdown+114, 0, ledValue, 0, 0);
  }
  
}




void doTalkingLights() {

  if (robotTalking)
  {
    setLedBySet(2, 8, 255, 60, 60, 100);
    setLedBySet(2, 9, 255, 60, 60, 100);
    if (timey > (robotTalkingOnTime + 40)) 
    {
      setLedBySet(2, 7, 255, 60, 60, 100);
      setLedBySet(2, 10, 255, 60, 60, 100);
    }
    if (timey > (robotTalkingOnTime + 80)) 
    {
      setLedBySet(2, 6, 255, 60, 60, 100);
      setLedBySet(2, 11, 255, 60, 60, 100);
    }
    if (timey > (robotTalkingOnTime + 110)) 
    {
      setLedBySet(2, 5, 255, 60, 60, 100);
      setLedBySet(2, 12, 255, 60, 60, 100);
    }
    if (timey > (robotTalkingOnTime + 135)) 
    {
      setLedBySet(2, 4, 255, 60, 60, 100);
      setLedBySet(2, 13, 255, 60, 60, 100);
    }
    if (timey > (robotTalkingOnTime + 150)) 
    {
      setLedBySet(2, 3, 255, 60, 60, 100);
      setLedBySet(2, 14, 255, 60, 60, 100);
    }
  }
}


