
void doMixing() {

  int mixStart = (tunesLibrary[currentGenre][currentTrack].tuneLength * 16) - nextMixDuration16;
  int sixteenthsIntoMix = ((currentBar * 16) + sixteenth) - mixStart;
  int bpmDifference = tunesLibrary[nextGenre][nextTrack].bpm - tunesLibrary[currentGenre][currentTrack].bpm;

  // Not good to use floats, we're not calling this too often (once per 16th).
  float percentThroughMix = (float)sixteenthsIntoMix / nextMixDuration16;
  
  int newBpm = (bpmDifference * percentThroughMix) + tunesLibrary[currentGenre][currentTrack].bpm;
  if (currentBpm != newBpm)
    setAbletonTempo(newBpm);

  // Now do the actual mixing
  if (deckASelected) {
    setCrossfader(127 * percentThroughMix);
  } else {
    setCrossfader(127 - (127 * percentThroughMix));
  }
}

void startNewMix() {
  
  // send stuff to ableton to start the new track  
  playAbletonTrack(nextGenre, nextTrack, !deckASelected);
    
  // change the current track in this program
  newCurrentBar = 0;
  currentGenre = nextGenre;
  currentTrack = nextTrack;
  currentBpm=tunesLibrary[currentGenre][currentTrack].bpm;
  inTheMix=true;

  // tell the other arduino what you're doing
  sendSerialToMega(2,(currentGenre*100)+currentTrack);

}


void chooseNextTrack() {
  bool nextTrackPicked = false;

  while (!nextTrackPicked) {
    pickNewGenre();
    
    nextTrack = random(3); // random(numTunesByGenre[nextGenre]);
    
    // is next track compatible? 
    if (tunesLibrary[nextGenre][nextTrack].minFadeIn > tunesLibrary[currentGenre][currentTrack].maxFadeOut)
      continue;
    else if (tunesLibrary[nextGenre][nextTrack].maxFadeIn < tunesLibrary[currentGenre][currentTrack].minFadeOut)         
      continue;
    else
      nextTrackPicked = true;    
  }

  // set the amount of time we are going to mix from one tune to the other.
  nextMixDuration16 = (((tunesLibrary[currentGenre][currentTrack].maxFadeOut) < (tunesLibrary[nextGenre][nextTrack].minFadeIn)) ? 
    (tunesLibrary[currentGenre][currentTrack].maxFadeOut) : (tunesLibrary[nextGenre][nextTrack].minFadeIn)) * 16;
}

void pickNewGenre() {
  if (!stayWithinGenre)
    nextGenre = random(10);
  else
    nextGenre = currentGenre;
}

