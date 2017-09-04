
void doMixing() {

  float percentThroughMix = getPercentThroughMix();
  
  int bpmDifference = nextTune.bpm - currentTune.bpm;
  int newBpm = ((float)bpmDifference * percentThroughMix) + currentTune.bpm;
  setAbletonTempo(newBpm);

  // Now do the actual mixing
  int crossfaderValue = 127 * percentThroughMix;
  
  if (deckASelected) {
    setCrossfader(crossfaderValue);
  } else {
    setCrossfader(127 - crossfaderValue);
  } 
}

// Not good to use floats but we're not calling this too often (once per quarter bar).
float getPercentThroughMix() {
  float percentThroughMix = 0.0;

  int mixStart = calculateMixStart();
  int beatsIntoMix = ((currentBar * 4) + ((sixteenBeats+3) % 4)) - (mixStart * 4);

  if (nextMixDuration < 9)
    return (float)beatsIntoMix / (nextMixDuration * 4);

  // if this is a long mix (>8 bars) we'll hold in the middle for a while so we use a different calculation
  if (beatsIntoMix < 16)
    return ((float)beatsIntoMix / 16.0) * 0.5;
  else if (beatsIntoMix > (nextMixDuration * 4) - 16)
    return (((float)(beatsIntoMix - ((nextMixDuration * 4) - 16)) / 16.0) * 0.5) + 0.5;
  else
    return 0.5;
  
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

  updateGenreAndTrackHistory(nextGenre, nextTrack);
    
  // change the current track in this program
  mixCurrentBar = 0;
  currentlyMixing=true;
}

void endMixAndPickNewTune() {
  // finish the mix
  if (testMode) {
    Serial.println("EndingMixPickingNew"); 
  }
  
  stopAbletonChannel(currentGenre, !deckASelected);
  if (deckASelected) {
    setCrossfader(127);
    deckASelected = false;
  } else {
    setCrossfader(0);
    deckASelected = true;
  }
  setAbletonTempo(nextTune.bpm);

  currentGenre = nextGenre;
  currentTrack = nextTrack;
  setCurrentTune(currentGenre, currentTrack);
  chooseNextTrack();

  // tell the other arduino what you're doing
  sendSerialToMega(2,(currentGenre*100)+currentTrack);
  
  currentBar = mixCurrentBar;
  currentlyMixing=false;
}

int calculateMixStart() {
  int lastPossibleMixPoint = currentTune.tuneLength - nextMixDuration;
  int idealMixPoint = (currentTune.tuneLength - currentTune.maxFadeOut) + currentTune.dropOffset;
  if (lastPossibleMixPoint < idealMixPoint)
    return lastPossibleMixPoint;
  else
   return idealMixPoint;
}

void chooseNextTrack() {
  bool nextTrackPicked = false;
  int genre, track;

  while (!nextTrackPicked) {

    // Pick next genre
    if (!stayWithinGenre)
      genre = random(8);
    else
      genre = currentGenre;
 
    // pick next track
    track = random(numberOfTunesInGenre(genre));

    // check it's not in the last 10 tunes played
    if (playedTuneHistoryContainsTrack(genre, track))
      continue;

    setNextTune(genre, track);

    if (nextTune.maxFadeIn < currentTune.minFadeOut)         
      continue;
  
    nextTrackPicked = true;    
  }

  nextMixDuration = (currentTune.maxFadeOut > nextTune.maxFadeIn) ? nextTune.maxFadeIn : currentTune.maxFadeOut;

  if (testMode) {
    Serial.print("current-maxFadeOut:");
    Serial.print(currentTune.maxFadeOut);
    Serial.print("  next-maxFadeIn:");
    Serial.println(nextTune.maxFadeIn);
  }
}

bool playedTuneHistoryContainsTrack(int genre, int track) {  // TODO - il because this never returns false for rave genre sometimes
  bool trackExistsInHistory = false;
  for (int x = 0; x < 9; x++) {
    if ((last10Genres[x] == genre) && (last10Tracks[x] == track)) {
      trackExistsInHistory = true;
      break;
    }
  }
  return trackExistsInHistory;
}

void setNextTune(int genre, int track) {
  nextGenre = genre;
  nextTrack = track;
  if (genre == 0)
    nextTune = tuneLibRave[track];
  else if (genre == 1)
    nextTune = tuneLibDisco[track];
  else if (genre == 2)
    nextTune = tuneLibReggae[track];
  else if (genre == 3)
    nextTune = tuneLibRockAndPop[track];
  else if (genre == 4)
    nextTune = tuneLibEasy[track];
  else if (genre == 5)
    nextTune = tuneLibDance[track];
  else if (genre == 6)
    nextTune = tuneLibDrumAndBass[track];
  else
    nextTune = tuneLibHipHop[track];    
}

void setCurrentTune(int genre, int track) {
  if (genre == 0)
    currentTune = tuneLibRave[track];
  else if (genre == 1)
    currentTune = tuneLibDisco[track];
  else if (genre == 2)
    currentTune = tuneLibReggae[track];
  else if (genre == 3)
    currentTune = tuneLibRockAndPop[track];
  else if (genre == 4)
    currentTune = tuneLibEasy[track];
  else if (genre == 5)
    currentTune = tuneLibDance[track];
  else if (genre == 6)
    currentTune = tuneLibDrumAndBass[track];
  else
    currentTune = tuneLibHipHop[track];
}

void playNextTrack() {
  playTune(last10Genres[9], last10Tracks[9], true);
}

void playPreviousTrack() {

  // shuffle the order of the history
  for (int x = 0; x < 9; x++)
    last10Genres[x] = last10Genres[x+1];    
  last10Genres[9] = currentGenre;

  for (int x = 0; x < 9; x++)
    last10Tracks[x] = last10Tracks[x+1];    
  last10Tracks[9] = currentTrack;
  
  // play the tune setting changeHistory to false
  playTune(last10Genres[0], last10Tracks[0], false);

  if (testMode)
    showLast10Tracks();
}

void showLast10Tracks() {
  for  (int x = 0; x < 9; x++) {
    Serial.print(x);
    Serial.print(":");
    Serial.print(last10Tracks[x]);
    Serial.print(" ");    
  }
  Serial.println("");
}

int numberOfTunesInGenre(int genre) {
  if (genre == 0)
    return sizeof(tuneLibRave) / sizeof(tuneInfo);
  else if (genre == 1)
    return sizeof(tuneLibDisco) / sizeof(tuneInfo);
  else if (genre == 2)
    return sizeof(tuneLibReggae) / sizeof(tuneInfo);
  else if (genre == 3)
    return sizeof(tuneLibRockAndPop) / sizeof(tuneInfo);
  else if (genre == 4)
    return sizeof(tuneLibEasy) / sizeof(tuneInfo);
  else if (genre == 5)
    return sizeof(tuneLibDance) / sizeof(tuneInfo);
  else if (genre == 6)
    return sizeof(tuneLibDrumAndBass) / sizeof(tuneInfo);
  else
    return sizeof(tuneLibHipHop) / sizeof(tuneInfo);
}


