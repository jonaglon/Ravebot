

void doPatternStripes() {

  //horizontalRainbow(false, false, 200);
  //fullLeftRightStripeInTime();
  leftRightStripes();
  sectionsInTime();
  
}


void testStripe() {


  int stripeBeatPos = (timeyInTime / 16)%2048;

  if ((sixteenBeats/2) % 2 == 0) {
    for(int j = 0; j < numLeds; j++) {
      int xCoord = getCoord(j,1);
      if (xCoord < stripeBeatPos)
        setLedDirect(j, 0, 0, 0, 0, false);
      else if (xCoord < stripeBeatPos+200)
        setLedDirect(j, 0, 0, 255, 0, false);
      else
        setLedDirect(j, 0, 0, 0, 0, false);      
    }
  } else {
    for(int j = 0; j < numLeds; j++) {
      int xCoord = getCoord(j,1);
      if (xCoord < stripeBeatPos)
        setLedDirect(j, 0, 255, 0, 0, false);      
      else
        setLedDirect(j, 255, 0, 0, 0, false);
    }
  }
    
  

}

int stripeBeatPos=0;
int xyCord=0;
void leftRightStripes() {

  SetRgbwWheelVars((timeyInTime / 400)%256);

  int sixteenBeatPos = (sixteenBeats/4) % 4;
  
  if (sixteenBeatPos == 0) {
    stripeBeatPos = (timeyInTime / 32)%1024;
    xyCord=0;
  } else if (sixteenBeatPos == 1) {
    stripeBeatPos = 2048-((timeyInTime / 32)%2048);
    xyCord=1;
  } else if (sixteenBeatPos == 2) {
    stripeBeatPos = 615-((timeyInTime / 32)%1024);
    xyCord=0;
  } else if (sixteenBeatPos == 3) {
    stripeBeatPos = (timeyInTime / 32)%2048;
    xyCord=1;
  }
    
  for(int j = 0; j < numLeds; j++) {
    int yCoord = getCoord(j,xyCord);
    if (yCoord < stripeBeatPos)
      setLedDirect(j, 0, 0, 0, 0, false);
    else if (yCoord < stripeBeatPos+200)
      setLedDirect(j, wheelR, wheelG, wheelB, 0, false);
    else
      setLedDirect(j, 0, 0, 0, 0, false);      
  }
}

