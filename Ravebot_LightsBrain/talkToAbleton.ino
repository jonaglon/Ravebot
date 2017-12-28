bool newBeat=false;

void playRandomTune() {
 currentGenre = random(8);
 
 playRandomTune(currentGenre);
}

void playRandomTune(int genre) {
  int track = 0;

  do {
    // pick next track
    track = random(numberOfTunesInGenre(genre));
  } while (playedTuneHistoryContainsTrack(genre, track));
  
  playTune(genre, track, true);
}

void playTune(int genre, int track, bool alterHistory) {
  sendFullStop();
  stopAllAbletonClips(); 

  if (alterHistory)
    updateGenreAndTrackHistory(genre, track);
  currentGenre = genre % 8;
  track = (track % numberOfTunesInGenre(genre));  
  setCurrentTune(genre, track);
  deckASelected = true;

  // change the current track in this program
  sixteenBeats = 0;
  currentBar = 0;
  fakeBeatCount = 0;

  if (testMode) {
     Serial.print("NOW PLAYING: ");
     Serial.print(genre);
     Serial.print("/");
     Serial.println(track);
  }      
  currentlyMixing=false;

  // Send new bpm and 
  setAbletonTempo(currentTune.bpm);
  setCrossfader(0);

  // tell the other arduino what you're doing
  sendSerialToMega(2,(genre*100)+track);

  // send stuff to ableton to start the new track  
  delay(200);
  playAbletonTrack(genre, track, true);
  start16BeatAbletonTrack(); // start the midi track in ableton which sends midi time codes back here
 
  chooseNextTrack();
  calculateMixDurationAndStart();

  if (testMode)
    showLast10Tracks();

}

void updateGenreAndTrackHistory(int genre, int track) {

  for (int x = 9; x > 0; x--)
    last10Genres[x] = last10Genres[x-1];  
  last10Genres[0] = genre;

  for (int x = 9; x > 0; x--)
    last10Tracks[x] = last10Tracks[x-1];    
  last10Tracks[0] = track;
}

void playAbletonTrack(int channel, int trackNumber, bool playSideA) {
  int abletonChannel = channel*2;
  if (!playSideA)
    abletonChannel++;

  sendMidi(abletonChannel+176, trackNumber+1, 127);
}

void stopAbletonChannel(int channel, bool stopSideA) {
  int abletonChannel = channel*2;
  if (stopSideA)
    abletonChannel++;

  sendMidi(abletonChannel+176, 0, 127);
}


void sendFullStop() {
  sendMidi(176, 120, 127);
}

void sendQuantisationOn() { // Uses Bomes to send ctrl-9
  // sendMidi(176, 121, 127);
}

void stopAllAbletonClips() {
  sendMidi(176, 125, 127);
}

void start16BeatAbletonTrack() {
  sendMidi(176, 126, 127); // channel 1, track 126, value 127.
}

void setMainVolume(int newVolume) {

  if (newVolume < 0)
    newVolume = 0;
  
  if (newVolume > 110)
    newVolume = 110;

  mainVolume = newVolume;
  
  sendMidi(176, 127, mainVolume);
}

void setAbletonTempo(int tempo) { // 80 - 207 bpm only
  if (abletonBpm == tempo)
    return;
  
  sendMidi(177, 125, tempo-80);
  abletonBpm = tempo;
}

void setRobotVolume(int volume) { // 0 - 127
  sendMidi(177, 126, volume);
}

void setCrossfader(int value) { // 0 - 127     176
  sendMidi(177, 127, value);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
// 176 is channel=1, 190 channel=15
void sendMidi(int channel, int trackNumber, int velocity) {
  if (testMode) {
    sendMidiTest(channel, trackNumber, velocity);
    return;
  }
  
  if ((channel < 176) || (channel > 192))
    return;
  if ((trackNumber < 0) || (trackNumber > 127))
    return;
  if ((velocity < 0) || (velocity > 127))
    return;
  
  Serial.write(channel);
  Serial.write(trackNumber);
  Serial.write(velocity);
}

void sendMidiTest(int channel, int trackNumber, int velocity) {
  // (176, 126, 127); // channel 1, track 126, value 127.
  
  Serial.print("Channel:");
  Serial.print(channel - 175);

  Serial.print(" Note:");
  Serial.print(trackNumber);

  Serial.print(" Value:");
  Serial.println(velocity);
}



