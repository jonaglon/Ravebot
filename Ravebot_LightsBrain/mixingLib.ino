


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
  nextMixDuration = ((tunesLibrary[currentGenre][currentTrack].maxFadeOut) < (tunesLibrary[nextGenre][nextTrack].minFadeIn)) ? 
    (tunesLibrary[currentGenre][currentTrack].maxFadeOut) : (tunesLibrary[nextGenre][nextTrack].minFadeIn);
}

void pickNewGenre() {
  if (!stayWithinGenre)
    nextGenre = random(10);
  else
    nextGenre = currentGenre;
}

