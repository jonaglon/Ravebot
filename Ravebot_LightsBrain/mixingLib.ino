
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

  int beatsIntoMix = ((currentBar - nextMixStart + 1) * 8) + (sixteenHalfBeats % 8) - 7;

  if (nextMixDuration < 12) {
    // straight mix if less than 12 bars
    percentThroughCalc = (beatsIntoMix  * 255) / (nextMixDuration * 8);
  }
  else if (beatsIntoMix < 48) {
    // beginning of mix where we hold in the middle for a bit
    percentThroughCalc = ((beatsIntoMix  * 255) / 96);
  }
  else if (beatsIntoMix > (nextMixDuration * 8) - 48) {
    percentThroughCalc = (((beatsIntoMix - ((nextMixDuration * 8) - 48)) * 255) / 96) + 127;
  }
  else {
    percentThroughCalc = 127;
  }

  if (percentThroughCalc > 255)
    percentThroughMix = 255;
  else if (percentThroughCalc < 0)
    percentThroughMix = 0;
  else
    percentThroughMix = percentThroughCalc;

  if (testMode)
    printMixDebugInfo(currentBar, nextMixStart, sixteenHalfBeats, beatsIntoMix, nextMixDuration, percentThroughCalc, percentThroughMix);
}

void printMixDebugInfo(int currentBar, int nextMixStart, int sixteenHalfBeats, int beatsIntoMix, int nextMixDuration, int percentThroughCalc, int percentThroughMix) {
  Serial.print("*** currentBar:");
  Serial.print(currentBar);
  Serial.print("    mixStart:");
  Serial.print(nextMixStart);
  Serial.print("          sixteenHalfBeats:");
  Serial.println(sixteenHalfBeats);
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

  if (testMode) {
    Serial.print("JUST STARTED: ");
    Serial.print(nextGenre);
    Serial.print("/");
    Serial.println(nextTrack);
  }

  updateGenreAndTrackHistory(nextGenre, nextTrack);

  // change the current track in this program
  mixCurrentBar = -1;
  currentlyMixing = true;
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

  // tell the other arduino what you're doing
  sendSerialToMega(2, (currentGenre * 100) + currentTrack);

  currentBar = mixCurrentBar;
  currentlyMixing = false;
}

void calculateMixDurationAndStart() {

  nextMixDuration = (currentTune.maxFadeOut > nextTune.maxFadeIn) ? nextTune.maxFadeIn : currentTune.maxFadeOut;

  if (testMode) {
    Serial.print("Calculating mmix start, next duration:");
    Serial.println(nextMixDuration);
  }

  int lastPossibleMixPoint = currentTune.tuneLength - nextMixDuration;
  int idealMixPoint = (currentTune.tuneLength - currentTune.maxFadeOut) + (currentTune.tuneBestEnd - nextMixDuration);
  if (lastPossibleMixPoint < idealMixPoint)
    nextMixStart = lastPossibleMixPoint;
  else
    nextMixStart = idealMixPoint;
}

void chooseNextTrack() {
  bool nextTrackPicked = false;
  int genre, track;

  // Also pick next lights pattern here

  while (!nextTrackPicked) {

    // Pick next genre
    if (!stayWithinGenre)
      genre = random(8);
    else
      genre = currentGenre;

    // pick next track
    track = random(numberOfTunesInGenre(genre));

    // check it's not in the last 10 tunes played      JR TODO - put this back
    //if (playedTuneHistoryContainsTrack(genre, track))
    //  continue;

    setNextTune(genre, track);

    if (nextTune.maxFadeIn < currentTune.minFadeOut)
      continue;

    nextTrackPicked = true;
  }
}

bool playedTuneHistoryContainsTrack(int genre, int track) {
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
    last10Genres[x] = last10Genres[x + 1];
  last10Genres[9] = currentGenre;

  for (int x = 0; x < 9; x++)
    last10Tracks[x] = last10Tracks[x + 1];
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


