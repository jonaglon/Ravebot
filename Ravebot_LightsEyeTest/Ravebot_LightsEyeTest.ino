/* __                 _           _               __ _       _     _  
  /__\ __ ___   _____| |__   ___ | |_            / /(_) __ _| |__ | |_ ___
 / \/// _` \ \ / / _ \ '_ \ / _ \| __|  _____   / / | |/ _` | '_ \| __/ __|
/ _  \ (_| |\ V /  __/ |_) | (_) | |_  |_____| / /__| | (_| | | | | |_\__ \
\/ \_/\__,_| \_/ \___|_.__/ \___/ \__|         \____/_|\__, |_| |_|\__|___/
                                                       |___/                       */
#include<Arduino.h>
#include<Wire.h>
#include<FastLED.h>

bool testMode = true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ;

unsigned long timey;
unsigned long fakeBeatCount = 0;
int ticky=0;

unsigned long beatTimes[10] = {0,0,0,0,0,0,0,0,0,0};
int fakeBeatLengh = 240;

// Set by midi in to be 1-16 with beat.
short sixteenBeats = 0;
 
int mainVolume = 100; // 127 actual max but we won't exceed 100.
int currentBar = 0;
int mixCurrentBar = 0; // This counts from the start of a mix
int currentGenre = 0;
int currentTrack = 0;
int dropCountdown = 0;

int eyeCoords[93][2] = {
  {43,22}, {43,18}, {41,14}, {39,10}, {37, 7}, {34, 4}, {30, 3}, {26, 1}, {22, 1}, {18, 1},
  {14, 3}, {10, 4}, { 7, 7}, { 5,10}, { 3,14}, { 1,18}, { 1,22}, { 1,26}, { 3,30}, { 5,34},
  { 7,37}, {11,40}, {14,42}, {18,43}, {22,43}, {27,43}, {30,42}, {34,40}, {37,37}, {40,34},
  {41,30}, {43,26}, {39,22}, {39,18}, {37,13}, {34,10}, {30, 7}, {26, 5}, {22, 5}, {18, 5},
  {14, 7}, {10,10}, { 7,13}, { 6,18}, { 5,22}, { 6,27}, { 7,30}, {10,34}, {14,37}, {18,38},
  {22,39}, {27,38}, {31,37}, {34,34}, {37,30}, {39,27}, {35,22}, {34,17}, {31,13}, {27,10},
  {22, 9}, {17,10}, {13,13}, {10,17}, { 9,22}, {10,27}, {13,31}, {17,34}, {22,35}, {27,34},
  {31,32}, {34,27}, {31,22}, {30,17}, {26,14}, {22,13}, {17,14}, {14,17}, {13,22}, {14,26},
  {17,30}, {22,31}, {27,30}, {30,26}, {27,22}, {26,19}, {22,17}, {18,19}, {17,22}, {18,25},
  {22,27}, {26,25}, {22,22} };

bool robotTalking = false;
unsigned long robotTalkingOnTime;

const int numLeds = 93;
CRGB rgbwLeds[2440]; // 488 * 5

// MIXING VARS
int nextTrack = 0;
int nextGenre = 0;
int nextMixDuration = 0;
int abletonBpm = 0;
bool stayWithinGenre = false;
bool currentlyMixing=false;
bool deckASelected = true;
int currentMixerPosition = 0;

bool abletonPaused = false;
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
  LEDS.setBrightness(4); // 255 max

  setMainVolume(mainVolume);
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
  byte dropOffset; // The drop offset is where the tune should finish with respect to the max fade out.
  tuneInfo(byte aBpm, byte aDrop, byte aTuneLength, byte aMaxFadeIn, byte aMinFadeOut, byte aMaxFadeOut, byte aDropOffset) : 
           bpm(aBpm), drop(aDrop), tuneLength(aTuneLength), maxFadeIn(aMaxFadeIn), minFadeOut(aMinFadeOut), maxFadeOut(aMaxFadeOut), dropOffset(aDropOffset) { 
  }
};
 
tuneInfo tuneLibRave[1] = { {120, 16, 129, 16,  8, 16, 16} };
tuneInfo tuneLibDisco[1] = { {120, 16, 129, 16,  8, 16, 16} };
tuneInfo tuneLibReggae[1] = { {120, 16, 129, 16,  8, 16, 16} };
tuneInfo tuneLibRockAndPop[1] = { {120, 16, 129, 16,  8, 16, 16} };
tuneInfo tuneLibEasy[1] = { {120, 16, 129, 16,  8, 16, 16} };
tuneInfo tuneLibDance[1] = { {120, 16, 129, 16,  8, 16, 16} };
tuneInfo tuneLibDrumAndBass[1] = { {120, 16, 129, 16,  8, 16, 16} };
tuneInfo tuneLibHipHop[1] = { {120, 16, 129, 16,  8, 16, 16} };

tuneInfo currentTune = tuneLibRave[1];
tuneInfo nextTune = tuneLibRave[2];




  
