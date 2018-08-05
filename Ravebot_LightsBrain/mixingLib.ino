
void doMixing() {

  int bpmDifference = nextTune.bpm - currentTune.bpm;
  int newBpm = ((bpmDifference * percentThroughMix) / 256) + currentTune.bpm;
  setAbletonTempo(newBpm);

  // Now do the actual mixing
  int crossfaderValue = (127 * percentThroughMix) / 256;
  if ((crossfaderValue > 63) && currentTune.playOut)
    crossfaderValue = 63;

  if (deckASelected) {
    setCrossfader(crossfaderValue);
  } else {
    setCrossfader(127 - crossfaderValue);
  }
}

// Percent through mix is actually 0-255.
void setPercentThroughMix() {
  int percentThroughCalc = 0;

  if (nextMixDuration == 0) {
    percentThroughMix = 0;
    return;
  }

  int beatsIntoMix = ((currentBar - nextMixStart + 1) * 4) + (sixteenBeats % 4) - 3;

  if (nextMixDuration < 12) {
    // straight mix if less than 12 bars
    percentThroughCalc = (beatsIntoMix  * 255) / (nextMixDuration * 4);
  }
  else if (nextMixDuration < 24) {
    if (beatsIntoMix < 24) {
      // beginning of mix where we hold in the middle for a bit
      percentThroughCalc = ((beatsIntoMix  * 255) / 48);
    }
    else if (beatsIntoMix > (nextMixDuration * 4) - 24) {
      percentThroughCalc = (((beatsIntoMix - ((nextMixDuration * 4) - 24)) * 255) / 48) + 127;
    }
    else {
      percentThroughCalc = 127;
    }
  } else {
    if (beatsIntoMix < 48) {
      // beginning of mix where we hold in the middle for a bit
      percentThroughCalc = ((beatsIntoMix  * 255) / 96);
    }
    else if (beatsIntoMix > (nextMixDuration * 4) - 48) {
      percentThroughCalc = (((beatsIntoMix - ((nextMixDuration * 4) - 48)) * 255) / 96) + 127;
    }
    else {
      percentThroughCalc = 127;
    }
  }


  if (percentThroughCalc > 255)
    percentThroughMix = 255;
  else if (percentThroughCalc < 0)
    percentThroughMix = 0;
  else
    percentThroughMix = percentThroughCalc;

  if (testMode)
    printMixDebugInfo(currentBar, nextMixStart, sixteenBeats, beatsIntoMix, nextMixDuration, percentThroughCalc, percentThroughMix);
}

void printMixDebugInfo(int currentBar, int nextMixStart, int sixteenHBeats, int beatsIntoMix, int nextMixDuration, int percentThroughCalc, int percentThroughMix) {
  Serial.print("*** currentBar:");
  Serial.print(currentBar);
  Serial.print("    mixStart:");
  Serial.print(nextMixStart);
  Serial.print("          sixteenHalfBeats:");
  Serial.println(sixteenHBeats);
  Serial.print("beatsIntoMix:");
  Serial.print(beatsIntoMix);
  Serial.print("    nextMixDuration:");
  Serial.print(nextMixDuration);
  Serial.print("          percentThroughCalc:");
  Serial.println(percentThroughCalc);
  Serial.println(percentThroughMix);
}

void startNewMix() {

  // send stuff to ableton to start the new track
  playAbletonTrack(nextGenre, nextTrack, !deckASelected);
  changeLightPattern();
  changeEyeDance();

  // tell the other arduino what you're doing
  sendSerialToMega(2, (nextGenre * 100) + nextTrack);  

  if (testMode) {
    Serial.print("JUST MIX STARTED: ");
    Serial.print(nextGenre);
    Serial.print("/");
    Serial.println(nextTrack);
  }

  updateGenreAndTrackHistory(nextGenre, nextTrack);

  // change the current track in this program
  mixCurrentBar = -1;
  currentlyMixing = true;
  sixteenBeats = 0;
  lastBeatTime = 0;
  timeyInTime = 0;
}

void doImmediateMix() {

  // send stuff to ableton to start the new track
  playAbletonTrack(nextGenre, nextTrack, !deckASelected);
  changeLightPattern();

  // tell the other arduino what you're doing
  sendSerialToMega(2, (nextGenre * 100) + nextTrack);  

  if (testMode) {
    Serial.print("JUST IMM STARTED: ");
    Serial.print(nextGenre);
    Serial.print("/");
    Serial.println(nextTrack);
  }

  updateGenreAndTrackHistory(nextGenre, nextTrack);

  // change the current track in this program
  mixCurrentBar = -1;
  sixteenBeats = 0;
  lastBeatTime = 0;
  timeyInTime = 0;
  
  endMixAndPickNewTune();
  
}

void endMixAndPickNewTune() {
  if (testMode) {
    Serial.println("EndingMixPickingNew");
  }

  // finish the mix
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

  calculateMixDurationAndStart();

  currentBar = mixCurrentBar;
  currentlyMixing = false;
}

void calculateMixDurationAndStart() {

  nextMixDuration = (currentTune.maxFadeOut > nextTune.maxFadeIn) ? nextTune.maxFadeIn : currentTune.maxFadeOut;

  if (nextMixDuration < 8) {
    nextMixStart =  currentTune.tuneLength - currentTune.maxFadeOut + currentTune.shortMixEnd - nextMixDuration;
  } else {
    nextMixStart =  currentTune.tuneLength - nextMixDuration;
  }

  if (testMode)
    printMixDurationAndStartDebug(nextMixDuration, nextMixStart, currentTune.tuneLength);
}

void printMixDurationAndStartDebug(int nextMixDuration, int nextMixStart, int tuneLength) {
  Serial.print("Picking MixDurationAndStart nextMixDuration:");
  Serial.print(nextMixDuration);
  Serial.print("  nextMixStart:");
  Serial.print(nextMixStart);
  Serial.print("  tuneLength:");
  Serial.println(tuneLength);
}

void chooseNextTrack() {
  bool nextTrackPicked = false;
  int genre, track;

  // Also pick next lights pattern here

  while (!nextTrackPicked) {

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
}


bool playedTuneHistoryContainsTrack(int genre, int track) {
  bool trackExistsInHistory = false;
  for (int x = 0; x < 19; x++) {
    if ((last20Genres[x] == genre) && (last20Tracks[x] == track)) {
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
    nextTune = tuneLibRave[track % numberOfTunesInGenre(0)];
  else if (genre == 1)
    nextTune = tuneLibDisco[track % numberOfTunesInGenre(1)];
  else if (genre == 2)
    nextTune = tuneLibReggae[track % numberOfTunesInGenre(2)];
  else if (genre == 3)
    nextTune = tuneLibRockAndPop[track % numberOfTunesInGenre(3)];
  else if (genre == 4)
    nextTune = tuneLibEasy[track % numberOfTunesInGenre(4)];
  else if (genre == 5)
    nextTune = tuneLibDance[track % numberOfTunesInGenre(5)];
  else if (genre == 6)
    nextTune = tuneLibDrumAndBass[track % numberOfTunesInGenre(6)];
  else
    nextTune = tuneLibHipHop[track % numberOfTunesInGenre(7)];
}

void setCurrentTune(int genre, int track) {
  if (genre == 0)
    currentTune = tuneLibRave[track % numberOfTunesInGenre(0)];
  else if (genre == 1)
    currentTune = tuneLibDisco[track % numberOfTunesInGenre(1)];
  else if (genre == 2)
    currentTune = tuneLibReggae[track % numberOfTunesInGenre(2)];
  else if (genre == 3)
    currentTune = tuneLibRockAndPop[track % numberOfTunesInGenre(3)];
  else if (genre == 4)
    currentTune = tuneLibEasy[track % numberOfTunesInGenre(4)];
  else if (genre == 5)
    currentTune = tuneLibDance[track % numberOfTunesInGenre(5)];
  else if (genre == 6)
    currentTune = tuneLibDrumAndBass[track % numberOfTunesInGenre(6)];
  else
    currentTune = tuneLibHipHop[track % numberOfTunesInGenre(7)];
  
}

void playNextTrack() {
  if (stayWithinGenre) {
    playRandomTune(currentGenre);
  } else {
    playRandomTune(); 
  }
}

void playPreviousTrack() {

  // shuffle the order of the history
  for (int x = 0; x < 19; x++)
    last20Genres[x] = last20Genres[x + 1];
  last20Genres[19] = currentGenre;

  for (int x = 0; x < 19; x++)
    last20Tracks[x] = last20Tracks[x + 1];
  last20Tracks[19] = currentTrack;

  // play the tune setting changeHistory to false
  playTune(last20Genres[0], last20Tracks[0], false);

  if (testMode)
    showLast20Tracks();
}

void showLast20Tracks() {
  for  (int x = 0; x < 19; x++) {
    Serial.print(x);
    Serial.print(":");
    Serial.print(last20Tracks[x]);
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


