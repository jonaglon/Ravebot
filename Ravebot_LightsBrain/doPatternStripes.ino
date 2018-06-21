
void doPatternStripes() {

  //horizontalRainbow(false, false, 200);
  //fullLeftRightStripeInTime();
  testStripe();
}


void testStripe() {


  int stripeBeatPos = (timeyInTime / 16)%2048;

  if ((sixteenBeats/2) % 2 == 0) {
    for(int j = 0; j < numLeds; j++) {
      int xCoord = getCoord(j,1);
      if (xCoord < stripeBeatPos)
        setLedDirect(j, 255, 0, 0, 0, true);
      else
        setLedDirect(j, 0, 255, 0, 0, true);      
    }
  } else {
    for(int j = 0; j < numLeds; j++) {
      int xCoord = getCoord(j,1);
      if (xCoord < stripeBeatPos)
        setLedDirect(j, 0, 255, 0, 0, true);      
      else
        setLedDirect(j, 255, 0, 0, 0, true);
    }
  }
    
  

}

