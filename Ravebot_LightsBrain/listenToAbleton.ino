byte incomingByte;
byte note;
byte velocity;
int channel = 1;
int noteDown = LOW;
int state=0;  // state machine variable 0 = command waiting : 1 = note waitin : 2 = velocity waiting

// Receive midi from ableton
void listenToAbleton() {

  if (testMode)
  {
    doFakeBeatMessageFromAbleton();
    return;
  }

  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    switch (state){
    case 0:
      // look for as status-byte, our channel, note on
      if (incomingByte== (144 | channel)){ 
        state=1;
      }
      // look for as status-byte, our channel, note off
      if (incomingByte== (128 | channel)){ 
        state=1;
      }

    case 1:
      // get the note to play or stop
      if(incomingByte < 128) {
        note=incomingByte;
        state=2; 
      }
      else{
        state = 0;  // reset state machine as this should be a note number
      }
      break;

    case 2:
      // get the velocity
      if(incomingByte < 128) {
        processMessageFromAbleton(note, incomingByte, noteDown);
      }
      state = 0;  // reset state machine to start            
    }
  }
}

void processMessageFromAbleton(byte note, byte velocity, int down) {
  if ((note>=24 && note<88) && (velocity == 100)) {
    sixteenBeats = note - 24; // from 0 to 63 
    sendBeatToMega();
    if (dropCountdown != 0)
      dropCountdown--;

    if (currentlyMixing) {
      doMixing();
    }
    
    if (sixteenBeats % 4 == 0) {
      // This is the beginning of a new bar, we set beat times and might need to start a mix or drop countdown
      currentBar++;
      newCurrentBar++;
      setBeatTimes();
      checkForMixStart();
      checkForMixEnd();
      checkForDropCountdownStart();
      if (testMode) {
        Serial.print("New bar: ");
        Serial.println(currentBar);
      }
    }         
  }
}

void checkForMixStart() {
  if (currentBar == tunesLibrary[currentGenre][currentTrack].tuneLength - nextMixDuration) {
    if (nextMixDuration == 0) {
      playTune(nextGenre, nextTrack);
    } else {
      startNewMix();
    }
  }
}

void checkForMixEnd() {
  // pick a new song if a mix has ended
  if (currentBar > tunesLibrary[currentGenre][currentTrack].tuneLength)
  {
    if (testMode) {
      Serial.println("Ending mix");
    }
    endMixAndPickNewTune();
  }
}

void checkForDropCountdownStart() {
  if (currentBar+4 ==  tunesLibrary[currentGenre][currentTrack].drop1)
    dropCountdown = 64;
  
  if (currentBar+2 ==  tunesLibrary[currentGenre][currentTrack].drop1)
    dropCountdown = 32;
}

void setBeatTimes() {

  for (int x = 0; x < 9; x++)
    beatTimes[x+1] = beatTimes[x];

  beatTimes[0] = timey;
}


/* Below is the fake beat control code */
unsigned long nextBeat = 0;

void doFakeBeatMessageFromAbleton() {
  if (timey > nextBeat) {
    processMessageFromAbleton((fakeBeatCount%16)+24, 100, 0);
    nextBeat = timey+fakeBeatLengh;
    fakeBeatCount++;
  }
}


