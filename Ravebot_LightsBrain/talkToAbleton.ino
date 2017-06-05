bool newBeat=false;

void playRandomTune(int genre) {
  int newTrackNumber = 0;
  do
    newTrackNumber = random(10);
  while (newTrackNumber == currentTrack);  
  
  playTune(genre, newTrackNumber);
}

void playTune(int genre, int track) {
  
  // send stuff to ableton to start the new track  
  stopAllAbletonTracks(); 
  start16BeatAbletonTrack(); // start the midi track in ableton which sends midi time codes back here
  setAbletonTempo(tunesLibrary[genre][track].bpm);
  playAbletonTrack(genre, track, true);

  // change the current track in this program
  currentBar = 0;
  currentGenre = genre;
  currentTrack = track;
  currentBpm=tunesLibrary[genre][track].bpm;
  inTheMix=false;

  // tell the other arduino what you're doing
  sendSerialToMega(2,(genre*100)+track);

  // choose the track to mix in to
  chooseNextTrack();
}

void playAbletonTrack(int channel, int trackNumber, bool playSideA)
{
  int abletonChannel = channel*2;
  if (playSideA) {
    deckASelected = true;
  } else {
    abletonChannel++;
    deckASelected = false;
  }

  if (abletonChannel < 17) {
    sendMidi(abletonChannel+176, trackNumber, 127);
    return;
  }
  
  int abletonTrack = (trackNumber%24)+97;
  int offset=1;
  if (trackNumber > 72)
    offset=4;
  else if (trackNumber > 48)
    offset=3;
  else if (trackNumber > 24)
    offset=2;
  
  switch (abletonChannel) {
    case 17:
      sendMidi(offset+176, abletonTrack, 127);
      break;
    case 18:
      sendMidi(offset+4+176, abletonTrack, 127);
      break;
    case 19:
      sendMidi(offset+8+176, abletonTrack, 127);
      break;
    case 20:
      sendMidi(offset+12+176, abletonTrack, 127);
      break;
  }
}

void stopAbletonChannel(int channel, bool stopSideA) {
  int abletonChannel = channel*2;
  if (stopSideA)
    abletonChannel++;

  switch (abletonChannel) {
    case 17:
      sendMidi(1+176, 121, 127);
      break;
    case 18:
      sendMidi(5+176, 121, 127);
      break; 
    case 19:
      sendMidi(9+176, 121, 127);
      break; 
    case 20:
      sendMidi(13+176, 121, 127);
      break;
    default:
      sendMidi(abletonChannel+176, 0, 127);
      break;
  }
}    

void stopAllAbletonTracks() {
  sendMidi(176, 125, 127);
}

void start16BeatAbletonTrack() {
  sendMidi(176, 126, 127);
}

void setMainVolume(int volume) { // 0 - 127
  if (volume > 127)
    volume = 127;
  sendMidi(176, 127, volume);
}

void setAbletonTempo(int tempo) { // 80 - 207 bpm only
    sendMidi(177, 125, tempo-80);
}

void setRobotVolume(int volume)  // 0 - 127
{
  sendMidi(177, 126, volume);
}

void setCrossfader(int value) { // 0 - 127
  sendMidi(177, 127, value);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
// 176 is channel=1, 190 channel=15
void sendMidi(int channel, int trackNumber, int velocity) {
  if ((channel < 176) || (channel > 192))
    return;
  if ((trackNumber < 1) || (trackNumber > 127))
    return;
  if ((velocity < 1) || (velocity > 127))
    return;
  
  Serial.write(channel);
  Serial.write(trackNumber);
  Serial.write(velocity);
}

void sendMidiTest(int channel, int trackNumber, int velocity) {
  Serial.print("channel:");
  //Serial.write(channel);
  Serial.print(channel);
  Serial.println(" ");
  Serial.print("track:");
  //Serial.write(trackNumber);
  Serial.print(trackNumber);
  Serial.println(" ");
  Serial.print("velocity:");
  //Serial.write(velocity);
  Serial.print(velocity);
  Serial.println(" ");
}



