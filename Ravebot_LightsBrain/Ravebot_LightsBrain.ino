/* __                 _           _               __ _       _     _  
  /__\ __ ___   _____| |__   ___ | |_            / /(_) __ _| |__ | |_ ___
 / \/// _` \ \ / / _ \ '_ \ / _ \| __|  _____   / / | |/ _` | '_ \| __/ __|
/ _  \ (_| |\ V /  __/ |_) | (_) | |_  |_____| / /__| | (_| | | | | |_\__ \
\/ \_/\__,_| \_/ \___|_.__/ \___/ \__|         \____/_|\__, |_| |_|\__|___/
                                                       |___/                       */
#include<Arduino.h>
#include<Wire.h>
#include<FastLED.h>

bool testMode = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ;

unsigned long timey;
unsigned long fakeBeatCount = 0;
int ticky=0;

unsigned long beatTimes[10] = {0,0,0,0,0,0,0,0,0,0};
int fakeBeatLengh = 120;

// Set by midi in to be 1-16 with beat.
short sixteenHalfBeats = 0;
 
int mainVolume = 100; // 127 actual max but we won't exceed 100.
int currentBar = 1;
int mixCurrentBar = 0; // This counts from the start of a mix
int currentGenre = 0;
int currentTrack = 0;
int dropCountdown = 0; 

bool robotTalking = false;
unsigned long robotTalkingOnTime;

const int numLeds = 1443;
CRGB rgbwLeds[2440]; // 488 * 5

// MIXING VARS
int nextTrack = 0;
int nextGenre = 0;
int nextMixDuration = 0;
int nextMixStart = 0;
int abletonBpm = 0;
bool stayWithinGenre = true;
bool currentlyMixing=false;
bool deckASelected = true;
int currentMixerPosition = 0;
int percentThroughMix = 0;  // not really % through, it's 0-256
int last10Genres[10] = {0,0,0,0,0,0,0,0,0,0};
int last10Tracks[10] = {0,0,0,0,0,0,0,0,0,0};

void setup() {

  delay(500);

  // Talk to Ableton using midi over USB, or debug.
  Serial.begin(9600);

  // Communicate with the Mega
  Serial2.begin(57600);
  // Talk to the other arduino
  //Serial3.begin(9600);

  // Make random more random
  randomSeed(analogRead(0));

  //pinMode(12, OUTPUT); // rgb LED Setup
  LEDS.addLeds<WS2811_PORTD, 5>(rgbwLeds, 488); // Hardcoded to ports:25,26,27,28,14,15
  LEDS.setBrightness(10); // 255 max

  setMainVolume(mainVolume);

  // TODO 
  playTune(7, 0, true);
}

void loop() {
  timey = millis();

  listenToAbleton();

  receiveFromMega();

  doLights();
}

struct tuneInfo {   
  byte bpm;
  byte drop;
  byte tuneLength;
  byte maxFadeIn;
  byte minFadeOut; 
  byte maxFadeOut;
  byte dropOffset; // The drop offset is where the tune should finish if it's not being mixed or the mix is shorter.
  bool playOut;
  tuneInfo(byte aBpm, byte aDrop, byte aTuneLength, byte aMaxFadeIn, byte aMinFadeOut, byte aMaxFadeOut, byte aDropOffset, bool aPlayOut) : 
    bpm(aBpm), drop(aDrop), tuneLength(aTuneLength), maxFadeIn(aMaxFadeIn), minFadeOut(aMinFadeOut), maxFadeOut(aMaxFadeOut), dropOffset(aDropOffset), playOut(aPlayOut) { 
  }
};
 
tuneInfo tuneLibRave[1] = { {120, 16, 129, 16,  8, 16, 16, false} };
tuneInfo tuneLibDisco[1] = { {120, 16, 129, 16,  8, 16, 16, false} };
tuneInfo tuneLibReggae[1] = { {120, 16, 129, 16,  8, 16, 16, false} };
tuneInfo tuneLibRockAndPop[1] = { {120, 16, 129, 16,  8, 16, 16, false} };
tuneInfo tuneLibEasy[1] = { {120, 16, 129, 16,  8, 16, 16, false} };
tuneInfo tuneLibDance[1] = { {120, 16, 129, 16,  8, 16, 16, false} };
tuneInfo tuneLibDrumAndBass[1] = { {120, 16, 129, 16,  8, 16, 16, false} };
// bpm, drop, tuneLength, maxFadeIn, minFadeOut, maxFadeOut, dropOffset, playOut
tuneInfo tuneLibHipHop[4] = { 
  { 89,  0,  16, 4,  4,  4,  4, false},  // shimmyshimmy
  { 89,  0,  16, 4,  4,  4,  4, false}, // NoDiggidy
  {111,  0,  16, 4,  4,  4,  4, true}, // Automatic
  {120,  0,  16, 4,  4,  4,  4, true},  // Like a g6
};

tuneInfo currentTune = tuneLibHipHop[0];
tuneInfo nextTune = tuneLibHipHop[1];




  
