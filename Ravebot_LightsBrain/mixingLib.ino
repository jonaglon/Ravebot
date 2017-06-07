
void doMixing() {

  int mixStart = tunesLibrary[currentGenre][currentTrack].tuneLength - nextMixDuration;
  int beatsIntoMix = ((currentBar * 4) + ((sixteenBeats+3) % 4)) - (mixStart * 4);

  // Not good to use floats, we're not calling this too often (once per quarter bar).
  float percentThroughMix = (float)beatsIntoMix / (nextMixDuration * 4);
  
  int bpmDifference = tunesLibrary[nextGenre][nextTrack].bpm - tunesLibrary[currentGenre][currentTrack].bpm;
  int newBpm = ((float)bpmDifference * percentThroughMix) + tunesLibrary[currentGenre][currentTrack].bpm;
  setAbletonTempo(newBpm);

  // Now do the actual mixing
  int crossfaderValue = 127 * percentThroughMix;
  
  if (deckASelected) {
    setCrossfader(crossfaderValue);
  } else {
    setCrossfader(127 - crossfaderValue);
  } 
}

void startNewMix() {
  
  // send stuff to ableton to start the new track  
  playAbletonTrack(nextGenre, nextTrack, !deckASelected);

  if (testMode) {
    Serial.print("JUST STARTED: ");
    Serial.print(nextGenre);
    Serial.print("/");
    Serial.println(nextTrack); 
  }
    
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

  currentGenre = nextGenre;
  currentTrack = nextTrack;
  chooseNextTrack();

  // tell the other arduino what you're doing
  sendSerialToMega(2,(currentGenre*100)+currentTrack);
  
  currentBar = newCurrentBar;
  currentlyMixing=false;
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

    // { 93,  9, 49,  21, 0, 4, 8, 8},  // No Diggidy 
    // {100,  5, 25,  21, 0, 8, 4, 8},  // Like it raw
    // is next track compatible? 
    if (tunesLibrary[nextGenre][nextTrack].minFadeIn > tunesLibrary[currentGenre][currentTrack].maxFadeOut)
      continue;
    else if (tunesLibrary[nextGenre][nextTrack].maxFadeIn < tunesLibrary[currentGenre][currentTrack].minFadeOut)         
      continue;
    else
      nextTrackPicked = true;    
  }

  if (testMode) {
    Serial.print("current-maxFadeOut:");
    Serial.print(tunesLibrary[currentGenre][currentTrack].maxFadeOut);
    Serial.print("  next-maxFadeIn:");
    Serial.print(tunesLibrary[nextGenre][nextTrack].maxFadeIn);
  }

  // set the amount of time we are going to mix from one tune to the other
  nextMixDuration = (tunesLibrary[currentGenre][currentTrack].maxFadeOut > tunesLibrary[nextGenre][nextTrack].maxFadeIn) ? 
    tunesLibrary[nextGenre][nextTrack].maxFadeIn : tunesLibrary[currentGenre][currentTrack].maxFadeOut;

}

