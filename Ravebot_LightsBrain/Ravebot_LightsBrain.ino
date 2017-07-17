  /* __                 _           _               __ _       _     _  
  /__\ __ ___   _____| |__   ___ | |_            / /(_) __ _| |__ | |_ ___
 / \/// _` \ \ / / _ \ '_ \ / _ \| __|  _____   / / | |/ _` | '_ \| __/ __|
/ _  \ (_| |\ V /  __/ |_) | (_) | |_  |_____| / /__| | (_| | | | | |_\__ \
\/ \_/\__,_| \_/ \___|_.__/ \___/ \__|         \____/_|\__, |_| |_|\__|___/
                                                       |___/                       */
#include<Arduino.h>
#include<Wire.h>
#include<FastLED.h>

bool testMode = false;

unsigned long timey;
unsigned long fakeBeatCount = 0; 
int ticky=0;

unsigned long beatTimes[10] = {0,0,0,0,0,0,0,0,0,0};
int fakeBeatLengh = 240;

// Set by midi in to be 1-16 with beat.
short sixteenBeats = 0;

int mainVolume = 100; // 127 actual max but we won't exceed 100.
int currentBar = 0;
int newCurrentBar = 0; // This counts from the start of a mix
int currentGenre = 0;
int currentTrack = 0;
int dropCountdown = 0;

bool robotTalking = false;
unsigned long robotTalkingOnTime;

const int numLeds = 671;
const int numLedsAdj = (numLeds * 4) / 3;
CRGB rgbwLeds[numLedsAdj];

// MIXING VARS
int nextTrack = 0;
int nextGenre = 0;
int nextMixDuration = 0;
int abletonBpm = 0;
bool stayWithinGenre = false;
bool currentlyMixing=false;
bool deckASelected = true;
int currentMixerPosition = 0;

void setup() {
  delay(500);

  // Talk to Ableton using midi over USB, or debug.
  Serial.begin(9600);

  // Listen to the other arduino
  Serial2.begin(57600);
  // Talk to the other arduino
  Serial3.begin(9600);

  // Make random more random?!
  randomSeed(analogRead(0));

  pinMode(12, OUTPUT); // rgb LED Setup
  LEDS.addLeds<WS2812B, 12>(rgbwLeds, numLedsAdj);
  LEDS.setBrightness(255); // 255 max

  setMainVolume(mainVolume);
}

void loop() {
  timey = millis();

  listenToAbleton();

  receiveFromMega();

  doLights();

}

// this needs bools for fadeInBusy, fadeOutBusy and isInSync  
struct tuneInfo {   
  byte bpm;
  byte drop;
  byte tuneLength;
  byte minFadeIn;
  byte maxFadeIn;
  byte minFadeOut; 
  byte maxFadeOut;
  byte dropOffset; // The drop offset is where the tune should finish with respect to the max fade out.
  tuneInfo(byte aBpm, byte aDrop, byte aTuneLength, byte aMinFadeIn, byte aMaxFadeIn, byte aMinFadeOut, byte aMaxFadeOut, byte aDropOffset) : 
           bpm(aBpm), drop(aDrop), tuneLength(aTuneLength), minFadeIn(aMinFadeIn), maxFadeIn(aMaxFadeIn), minFadeOut(aMinFadeOut), maxFadeOut(aMaxFadeOut), dropOffset(aDropOffset) { 
  }
};
 
// Genre 0, RAVE!
tuneInfo tuneLibRave[11] = {
  {124,  0, 124, 4, 4, 4, 4, 0},  // WhatCanYouDoForMe-UtahSaints
  {149,  0, 177, 4, 4, 4, 4, 0},  // TripToTheMoonPt2-Acen
  {119,  0, 110, 4, 4, 4, 4, 0},  // YouGotTheLove-TheSourceFtCandiStanton
  {126,  0, 75,  4, 4, 4, 4, 0},   // MrKirsNightmare-4Hero
  {137,  0, 113, 4, 4, 4, 4, 0},  // Bombscare-2BadMice
  {126,  0, 138, 4, 4, 4, 4, 0},  // LFO-LFO
  {132,  0, 135, 4, 4, 4, 4, 0},  // Infiltrate202-Altern8 
  {122,  0, 119, 4, 4, 4, 4, 0},  // DirtyCash-SoldOutMix
  {122,  0, 133, 4, 4, 4, 4, 0},  // Break4Love-Raze
  {126,  0,  93, 4, 4, 4, 4, 0},  // IsThereAnybodyOutThere-Bassheads
  {126,  0,  86, 4, 4, 4, 4, 0}   //PacificState-808State
};

// Genre 1, Disco
tuneInfo tuneLibDisco[11] = {
  {124,  0,  71, 4, 4, 4, 4, 0},  // ILoveTheNightlife - Alecia Bridges
  {115,  0, 105, 4, 4, 4, 4, 0},  // LoveHangover - DianaRoss
  {110,  0, 151, 4, 4, 4, 4, 0},  // LastNightADjSavedMyLife-Indeep
  {134,  0, 148, 4, 4, 4, 4, 0},  // LayAllYourLoveOnMe-Abba
  {121,  0, 182, 4, 4, 4, 4, 0},  // HotStuff-DonnaSummer
  {128,  0, 109, 4, 4, 4, 4, 0},  // RingMyBell-AnitaWard
  {128,  0, 129, 4, 4, 4, 4, 0},  // EverybodyDance-Chic
  {111,  0,  97, 4, 4, 4, 4, 0},  // GoodTimes-Chic
  {101,  0, 110, 4, 4, 4, 4, 0},  // ThinkingOfYou-SisSledge
  {115,  0, 105, 4, 4, 4, 4, 0},  // SheCantLoveYou-Chemise
  {112,  0, 131, 4, 4, 4, 4, 0}   // Automatic-PointerSisters   
};

// Genre 2, Reggae
tuneInfo tuneLibReggae[11] = {
  { 86,  9,  51, 4, 4, 4, 4, 0},  // Tenor Saw Ring the Alarm
  {102, 49, 119, 4, 4, 4, 4, 0},  // Toots Funky Kingston
  { 80,  0,  79, 4, 4, 4, 4, 0},  // WayneSmith - UnderMeSleng Teng
  { 86,  0,  67, 4, 4, 4, 4, 0},  // Sis Nancy Bam Bam
  { 83,  0,  77, 4, 4, 4, 4, 0},  // Althea&Donna Strictly Roots
  { 77, 27,  52, 4, 4, 4, 4, 0},  // Damian Marley Welcome To Jamrock
  {147, 59, 147, 4, 4, 4, 4, 0},  // Tanya S - It's a pity
  { 88,  0,  72, 4, 4, 4, 4, 0},  // Marcia G - Feel like jumping
  { 82,  0,  72, 4, 4, 4, 4, 0},  // Cant stop now, MajorLazer
  {148,  0, 106, 4, 4, 4, 4, 0},  // Toots - pressure drop
  {104,  0,  99, 4, 4, 4, 4, 0}   // Bob - Could you be loved
};

// Genre 3, Rock&Pop
tuneInfo tuneLibRockAndPop[11] = {
  {160,  0, 113, 4, 4, 4, 4, 0},  // Kim Wilde - Kids in America
  {126,  0,  81, 4, 4, 4, 4, 0},  //Kylie - cant get you out
  {112,  0, 101, 4, 4, 4, 4, 0},  //Hall&Oates - I can't go for that
  { 97,  0,  63, 4, 4, 4, 4, 0},  //George Michael - Faith
  {122, 49, 107, 4, 4, 4, 4, 0},  //DeeLite - Groove is in the heart
  {126,  0, 103, 4, 4, 4, 4, 0},  //Euritmics - sweet dreams
  {126, 39,  97, 4, 4, 4, 4, 0},  //PaulSimon&Dylan Stuck in the middle
  {164,  9, 136, 4, 4, 4, 4, 0},  //Martha&Muffins Echo Beach
  {199,  0, 111, 4, 4, 4, 4, 0},  //TheCoral - DreamingOfYou
  { 99,  0,  58, 4, 4, 4, 4, 0},  // Blister in the sun - Voilent femmes
  {114,  0,  96, 4, 4, 4, 4, 0}   // Erasure a little respect  
};

// Genre 4, Easy
tuneInfo tuneLibEasy[12] = {
  {120,  0, 143, 4, 4, 4, 4, 0}, // BackToMyRoots - RichieHavens
  {104,  0, 116, 4, 4, 4, 4, 0}, // Think - Aretha
  {100,  0, 182, 4, 4, 4, 4, 0}, // As - Wonder
  {174,  0, 155, 4, 4, 4, 4, 0}, // Roady - FatFreddyNextmen
  {130,  0,  89, 4, 4, 4, 4, 0}, // Beggin - FrankieValli *******
  { 98,  0,  70, 4, 4, 4, 4, 0}, // IGotAWoman - RayCharles
  {156,  0, 143, 4, 4, 4, 4, 0}, // MilkAndHoney-PrinceFatty
  {124,  0, 123, 4, 4, 4, 4, 0}, // BackToBlack - Amy 
  {132,  0, 166, 4, 4, 4, 4, 0}, // MasterBlaster-StevieWonder
  {109,  0, 113, 4, 4, 4, 4, 0}, // AllNightLong - LionelRichie
  { 96,  0,  97, 4, 4, 4, 4, 0}, // INeedADollar-AloeBlacc     
  {122,  0, 124, 4, 4, 4, 4, 0}  // GotToGiveItUp-MarvinGaye
};

// Genre 5, Dance
tuneInfo tuneLibDance[11] = {
  {133,  29, 120, 4, 4, 4, 4, 0},  // A rinky dinky
  {136,  45,  93, 4, 4, 4, 4, 0},  // Israelites mix
  {108,  57,  83, 4, 4, 4, 4, 0},  // Kelis - Trick Me
  {150,  25, 125, 4, 4, 4, 4, 0},  // Dubbleedge - Lips to the floor
  {134, 105, 121, 4, 4, 4, 4, 0},  // Zero Emit Collect
  {125,  71, 103, 4, 4, 4, 4, 0},  // Dizee Bonkers
  {115,  57,  84, 4, 4, 4, 4, 0},  // RizzleKicks - DownWithTheTrumpets
  {168,  93, 173, 4, 4, 4, 4, 0},  // OneTime
  {130,   0, 161, 4, 4, 4, 4, 0},  // WileOut - DJ Zinc
  {145,   0, 171, 4, 4, 4, 4, 0},  // Aphex - Polynomial C
  {123,   0, 187, 4, 4, 4, 4, 0}   // Aphex WindowLicker
};

// Genre 6, Drum&Bass
tuneInfo tuneLibDrumAndBass[7] = {
  {140,  0, 148, 4, 4, 4, 4, 0},  // NextHype-TempaT
  {175,  0, 191, 4, 4, 4, 4, 0},  // DuppyMan-ChaseAndStatusCapleton
  {174,  0, 264, 4, 4, 4, 4, 0},  // TheNine-BadCompany
  {174,  0, 166, 4, 4, 4, 4, 0},  // GoldDigger-HighContrast
  {175,  0, 189, 4, 4, 4, 4, 0},  // ShakeUrBody-ShyFX
  {180,  0, 185, 4, 4, 4, 4, 0},  // LastNight-BennyPage
  {175,  0, 170, 4, 4, 4, 4, 0},  // PassMeTheRizla-Deekline
};

// Genre 7, HipHop
tuneInfo tuneLibHipHop[11] = {
  {101, 25,  12, 4, 4, 4, 4, 0},  // Lets get ill
  { 93, 49,  12, 4, 4, 4, 4, 0},  // No Diggidy
  {103, 69,  12, 4, 4, 4, 4, 0},  // Moma said knock you out     
  {100, 25,  12, 4, 4, 4, 4, 0},  // Like it raw
  { 92, 49,  12, 4, 4, 4, 4, 0},  // Dre&2Pac California
  {162, 65, 143, 4, 4, 4, 4, 0},  // Bigger than hip hop
  { 93, 61,  73, 4, 4, 4, 4, 0},  // Close to me snoop
  {160, 77, 159, 4, 4, 4, 4, 0},  // Coolio Gansters paradise
  {100, 47,  89, 4, 4, 4, 4, 0},  // HipHopHooray
  {108, 34,  96, 4, 4, 4, 4, 0},  // Jump Around 
  {103,  0,  81, 4, 4, 4, 4, 0},  // Insazlle in the bazzle - Cyprus Hazzle
};

tuneInfo currentTune = tuneLibRave[1];
tuneInfo nextTune = tuneLibRave[2];
int currentGenre = 0;



  
