

void doPatternStripes() {

  leftRightStripes();
  sectionsInTime();
  
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

