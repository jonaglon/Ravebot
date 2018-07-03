void doPatternTrains() {
  tubesInTime();
  bigSpeakerInTime();
}

int numLedsTube = 88;
int numLedsPerBeat=22;
int beatCompNum = 16384/numLedsPerBeat; // this is the 16384 beat% / those 30 leds. (182/546 - for 30/90)
void tubesInTime() {
  for(int j = 0; j < numLedsTube; j++) {
    int distanceFromBeat = quickAbsolute(((j%numLedsPerBeat)*beatCompNum)-percentThroughBeat);

    int ledColour = 255 - (distanceFromBeat/10);
    if (ledColour < 0)
      ledColour = 0;

    setSectionLed(13, j, ledColour, 0, 0, 0);
    setSectionLed(14, j, 0, ledColour, 0, 0);
    setSectionLed(15, j, 0, 0, ledColour, 0);
    setSectionLed(16, j, 0, 0, 0, ledColour);
  }
}

int numLedsPerBeat2=51;
int beatCompNum2 = 16384/numLedsPerBeat2; // this is the 16384 beat% / those 30 leds. (182/546 - for 30/90)
void bigSpeakerInTime() {

  int sixteenBeatPos = (sixteenBeats/2) % 4;

  for(int j = 0; j < 204; j++) {
    int distanceFromBeat = quickAbsolute(((j%numLedsPerBeat2)*beatCompNum2)-percentThroughBeat);

    int ledColour = 255 - (distanceFromBeat/10);
    if (ledColour < 0)
      ledColour = 0;
    
    if (sixteenBeatPos == 0) {
      setSectionLed(0, j, ledColour, 0, 0, 0);
    } else if (sixteenBeatPos == 1) {
      setSectionLed(0, j, 0, ledColour, 0, 0);
    } else if (sixteenBeatPos == 2) {
      setSectionLed(0, j, 0, 0, ledColour, 0);
    } else {
      setSectionLed(0, j, 0, 0, 0, ledColour);
    }
  }  
}

/*
  // 00 bottomRing
  // 01 bigHeart
  // 02 smallHeart
  // 03 underarm left
  // 04 overarm left
  // 05 eyeLeft 
  // 06 rightEye
  // 07 mouth
  // 08 tape
  // 09 tuner 
  // 10 indicator
  // 11 underArm right
  // 12 overArm right
  // 13 tubeBottomright
  // 14 tubeBottomleft
  // 15 tubeTopleft
  // 16 tubeTopright
  // 17 port left
  // 18 port right */
