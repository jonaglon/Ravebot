
void doMixing() {

  int mixStart = (tunesLibrary[currentGenre][currentTrack].tuneLength * 16) - nextMixDuration16;
  int sixteenthsIntoMix = ((currentBar * 16) + sixteenth) - mixStart;
  float percentThroughMix = sixteenthsIntoMix / nextMixDuration16;
  int bpmDifference = tunesLibrary[nextGenre][nextTrack].bpm - tunesLibrary[currentGenre][currentTrack].bpm;
  int newBpm = (bpmDifference * percentThroughMix) + tunesLibrary[currentGenre][currentTrack].bpm;
  if (currentBpm != newBpm)
    setSongTempo(newBpm);

  // Now do the actual mixing
  if (deckASelected) {
    setCrossfader(127 * percentThroughMix);
  } else () {
    setCrossfader(127 - (127 * percentThroughMix));
  }
}

// Maybe trigger this when you receive a sixteenth
void doMixingOld() {

  // find the percentage through the mix
  // (tunesLibrary[currentGenre][currentTrack].maxFadeOut * 1600) - ((currentBar * 1600) + (sixteenth*100))
  // tune length = 100, mix length=16bars. we are at bar 88 so 25% of the way through the mix
  // percentThrough = 25600 / -44800; //  25600 / 140800 - 160000 - 25600
  int percentageThroughMix = nextMixDuration16 / (tunesLibrary[currentGenre][currentTrack].tuneLength * 16) - ((currentBar * 1600) + (sixteenth*100));
 //int percentageThroughMix = (nextMixDuration16 * 100) / (((currentBar * 1600) + (sixteenth*100)) - (tunesLibrary[currentGenre][currentTrack].tuneLength * 1600) - (nextMixDuration16 * 100))
  
  // old bpm=100 new=120 we need to get a value of 105 for the newBpm;
  int bpmDifference = (tunesLibrary[nextGenre][nextTrack].bpm - tunesLibrary[currentGenre][currentTrack].bpm) * 100; // (120 - 100) * 100 = 2000
  int newBpm = 12; 
  
}

void chooseNextTrack() {
  bool nextTrackPicked = false;

  while (!nextTrackPicked) {
    pickNewGenre();
    
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
  nextMixDuration16 = (((tunesLibrary[currentGenre][currentTrack].maxFadeOut) < (tunesLibrary[nextGenre][nextTrack].minFadeIn)) ? 
    (tunesLibrary[currentGenre][currentTrack].maxFadeOut) : (tunesLibrary[nextGenre][nextTrack].minFadeIn)) * 16;
}

void pickNewGenre() {
  if (!stayWithinGenre)
    nextGenre = random(10);
  else
    nextGenre = currentGenre;
}

