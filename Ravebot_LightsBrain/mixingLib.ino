
void doMixing() {

  int mixStart = tunesLibrary[currentGenre][currentTrack].tuneLength - nextMixDuration;
  if (testMode) {
    Serial.print("mixStart:");
    Serial.print(mixStart);
    Serial.print("   currentBar:");
    Serial.print(currentBar);
    Serial.print("   sixteenBeats:");
    Serial.println(sixteenBeats);
  }
  
  int beatsIntoMix = ((currentBar * 4) + ((sixteenBeats+3) % 4)) - (mixStart * 4);

  // Not good to use floats, we're not calling this too often (once per quarter bar).
  float percentThroughMix = (float)beatsIntoMix / (nextMixDuration * 4);
  
  int bpmDifference = tunesLibrary[nextGenre][nextTrack].bpm - tunesLibrary[currentGenre][currentTrack].bpm;
  int newBpm = ((float)bpmDifference * percentThroughMix) + tunesLibrary[currentGenre][currentTrack].bpm;
  setAbletonTempo(newBpm);

  // Now do the actual mixing
  int crossfaderValue = 127 * percentThroughMix;

  if (testMode) {
    Serial.print("next bpm:");
    Serial.print(tunesLibrary[nextGenre][nextTrack].bpm);
    
    Serial.print("  current bpm:");
    Serial.print(tunesLibrary[currentGenre][currentTrack].bpm);
    Serial.print("  diff:");
    Serial.print(bpmDifference);
    Serial.print("  NEW=");
    Serial.println(newBpm);
  }
  
  if (deckASelected) {
    setCrossfader(crossfaderValue);
  } else {
    setCrossfader(127 - crossfaderValue);
  } 
}

void startNewMix() {
  
  // send stuff to ableton to start the new track  
  playAbletonTrack(nextGenre, nextTrack, !deckASelected);
    
  // change the current track in this program
  newCurrentBar = 0;
  currentlyMixing=true;
}

void endMixAndPickNewTune() {
  // finish the mix
  stopAbletonChannel(currentGenre, !deckASelected);
  if (deckASelected) {
    setCrossfader(127);
    deckASelected = false;
  } else {
    setCrossfader(0);
    deckASelected = true;
  }
  setAbletonTempo(tunesLibrary[nextGenre][nextTrack].bpm);

  // choose the next track
  currentGenre = nextGenre;
  currentTrack = nextTrack;
  chooseNextTrack();

  // tell the other arduino what you're doing
  sendSerialToMega(2,(currentGenre*100)+currentTrack);
  
  currentBar = newCurrentBar;
  newCurrentBar=0;
  currentlyMixing=false;
  inTheMix=0;
}

void chooseNextTrack() {
  bool nextTrackPicked = false;

  while (!nextTrackPicked) {
    // Pick next genre
    if (!stayWithinGenre)
      nextGenre = random(8);
    else
      nextGenre = currentGenre;
    
    // Pick next track
    nextTrack = random(numTunesByGenre[nextGenre]);
    
    // is next track compatible? 
    if (tunesLibrary[nextGenre][nextTrack].minFadeIn > tunesLibrary[currentGenre][currentTrack].maxFadeOut)
      continue;
    else if (tunesLibrary[nextGenre][nextTrack].maxFadeIn < tunesLibrary[currentGenre][currentTrack].minFadeOut)         
      continue;
    else
      nextTrackPicked = true;    
  }

  // set the amount of time we are going to mix from one tune to the other.
  nextMixDuration = ((tunesLibrary[currentGenre][currentTrack].maxFadeOut) < (tunesLibrary[nextGenre][nextTrack].minFadeIn)) ? 
    (tunesLibrary[currentGenre][currentTrack].maxFadeOut) : (tunesLibrary[nextGenre][nextTrack].minFadeIn);

  
}

