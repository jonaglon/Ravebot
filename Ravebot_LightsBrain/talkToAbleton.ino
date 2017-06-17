bool newBeat=false;

void playRandomTune(int genre) {
  int newTrackNumber = 0;
  do
    newTrackNumber = random(numTunesByGenre[genre]);
  while (newTrackNumber == currentTrack);  
  
  playTune(genre, newTrackNumber);
}

void playTune(int genre, int track) {
  
  // send stuff to ableton to start the new track  
  stopAllAbletonTracks(); 
  start16BeatAbletonTrack(); // start the midi track in ableton which sends midi time codes back here
  setAbletonTempo(tunesLibrary[genre][track].bpm);
  setCrossfader(0);
  playAbletonTrack(genre, track, true);

  // change the current track in this program
  sixteenBeats = 0;
  currentBar = -1;
  fakeBeatCount = 0;
  currentGenre = genre;
  currentTrack = track;
  if (testMode) {
     Serial.print("NOW PLAYING: ");
     Serial.print(genre);
     Serial.print("/");
     Serial.println(track);
  }      
  currentlyMixing=false;

  // tell the other arduino what you're doing
  sendSerialToMega(2,(genre*100)+track);
 
  // choose the track to mix in to
  chooseNextTrack();
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

void stopAllAbletonTracks() {
  sendMidi(176, 125, 127);
}

void start16BeatAbletonTrack() {
  sendMidi(176, 126, 127); // channel 1, track 126, value 127.
}

void setMainVolume(int volume) { // 0 - 127
  if (volume > 127)
    volume = 127;
  sendMidi(176, 127, volume);
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



