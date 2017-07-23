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
int currentBar;
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

bool abletonPaused = false;

void setup() {
  currentBar=0;
  
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

// this needs bools for fadeInBusy, fadeOutBusy and isInSync  - also needs mixing, meaning requires the crossfader or if it can just join.
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
  {149,  0, 210, 4, 4, 4, 4, 0},  // TripToTheMoonPt2-Acen
  {126,  0, 74,  4, 4, 4, 4, 0},  // MrKirsNightmare-4Hero
  {136,  0, 112, 4, 4, 4, 4, 0},  // Bombscare-2BadMice
  {126,  0, 165, 4, 4, 4, 4, 0},  // LFO-LFO
  {132,  0, 179, 4, 4, 4, 4, 0},  // Infiltrate202-Altern8 
  {122,  0, 118, 4, 4, 4, 4, 0},  // DirtyCash-SoldOutMix
  {122,  0, 132, 4, 4, 4, 4, 0},  // Break4Love-Raze
  {126,  0,  95, 4, 4, 4, 4, 0},  // IsThereAnybodyOutThere-Bassheads
  {128,  0,  85, 4, 4, 4, 4, 0},  // PacificState-808State
  {150,  0, 182, 4, 4, 4, 4, 0},  // OutOfSpace-Prodigy
  {124,  0, 183, 4, 4, 4, 4, 0}   // WhatCanYouDoForMe-UtahSaints
};

// Genre 1, Disco
tuneInfo tuneLibDisco[10] = {
  {125,  0, 102, 4, 4, 4, 4, 0},  // ILoveTheNightlife - Alecia Bridges
  {110,  0, 150, 4, 4, 4, 4, 0},  // LastNightADjSavedMyLife-Indeep
  {134,  0, 148, 4, 4, 4, 4, 0},  // LayAllYourLoveOnMe-Abba
  {121,  0, 158, 4, 4, 4, 4, 0},  // HotStuff-DonnaSummer
  {128,  0, 110, 4, 4, 4, 4, 0},  // RingMyBell-AnitaWard
  {128,  0, 212, 4, 4, 4, 4, 0},  // EverybodyDance-Chic
  {111,  0, 100, 4, 4, 4, 4, 0},  // GoodTimes-Chic
  {101,  0, 112, 4, 4, 4, 4, 0},  // ThinkingOfYou-SisSledge
  {115,  0, 104, 4, 4, 4, 4, 0},  // SheCantLoveYou-Chemise
  {112,  0, 130, 4, 4, 4, 4, 0}   // Automatic-PointerSisters   
};

// Genre 2, Reggae
tuneInfo tuneLibReggae[11] = {
  {170,  0, 134, 4, 4, 4, 4, 0},  // RingTheAlarm-TenorSaw
  {102,  0, 118, 4, 4, 4, 4, 0},  // FunkyKingston-Toots
  {164,  0, 164, 4, 4, 4, 4, 0},  // UnderMeSlengTeng-WayneSmith
  {162,  0, 163, 4, 4, 4, 4, 0},  // BamBam-SisNancy
  {162,  0, 152, 4, 4, 4, 4, 0},  // StrictlyRoots-Althea&Donna 
  {154,  0, 102, 4, 4, 4, 4, 0},  // WelcomeToJamrock-DamianMarley
  {148,  0, 146, 4, 4, 4, 4, 0},  // ItsAPity-TanyaStevens
  {177,  0, 142, 4, 4, 4, 4, 0},  // FeelLikeJumping-MarciaG 
  {164,  0, 164, 4, 4, 4, 4, 0},  // CantStopNow-MajorLazer
  {148,  0, 105, 4, 4, 4, 4, 0},  // PressureDrop-Toots
  {104,  0, 100, 4, 4, 4, 4, 0}   // CouldYouBeLoved-BobMarley
};

// Genre 3, Rock&Pop
tuneInfo tuneLibRockAndPop[11] = {
  {160,  0, 112, 4, 4, 4, 4, 0},  // KidsInAmerica-KimWilde
  {126,  0,  80, 4, 4, 4, 4, 0},  // CantGetYouOut-Kylie
  {112,  0, 100, 4, 4, 4, 4, 0},  // ICantGoForThat-Hall&Oates
  { 97,  0,  63, 4, 4, 4, 4, 0},  // Faith-GeorgeMichael
  {122, 49, 106, 4, 4, 4, 4, 0},  // GrooveIsInTheHeart-DeeLite
  {126,  0, 108, 4, 4, 4, 4, 0},  // SweetDreams-Euritmics
  {122, 39, 106, 4, 4, 4, 4, 0},  // StuckInTheMiddle-SteelersWheel
  {164,  9, 136, 4, 4, 4, 4, 0},  // Martha&Muffins Echo Beach
  {199,  0, 111, 4, 4, 4, 4, 0},  // DreamingOfYou-TheCoral
  { 99,  0,  58, 4, 4, 4, 4, 0},  // BlisterInTheSun-VoilentFemmes
  {114,  0,  96, 4, 4, 4, 4, 0}   // ALittleRespect-Erasure  
};

// Genre 4, Easy
tuneInfo tuneLibEasy[12] = {
  {122,  0, 142, 4, 4, 4, 4, 0}, // BackToMyRoots - RichieHavens
  {104,  0,  59, 4, 4, 4, 4, 0}, // Think - Aretha
  {100,  0, 181, 4, 4, 4, 4, 0}, // As - Wonder
  {174,  0, 154, 4, 4, 4, 4, 0}, // Roady - FatFreddyNextmen
  {132,  0,  88, 4, 4, 4, 4, 0}, // Beggin - FrankieValli
  { 98,  0,  72, 4, 4, 4, 4, 0}, // IGotAWoman - RayCharles 
  {156,  0, 144, 4, 4, 4, 4, 0}, // MilkAndHoney-PrinceFatty
  {126,  0, 123, 4, 4, 4, 4, 0}, // BackToBlack - Amy 
  {132,  0, 166, 4, 4, 4, 4, 0}, // MasterBlaster-StevieWonder
  {109,  0, 113, 4, 4, 4, 4, 0}, // AllNightLong - LionelRichie
  { 96,  0,  96, 4, 4, 4, 4, 0}, // INeedADollar-AloeBlacc     
  {122,  0, 124, 4, 4, 4, 4, 0}  // GotToGiveItUp-MarvinGaye
};

// Genre 5, Dance
tuneInfo tuneLibDance[10] = {
  {134,  29, 119, 4, 4, 4, 4, 0},  // A rinky dinky
  {110,  58,  91, 4, 4, 4, 4, 0},  // Kelis - Trick Me
  {150,  25, 134, 4, 4, 4, 4, 0},  // Dubbleedge - Lips to the floor
  {134, 105, 169, 4, 4, 4, 4, 0},  // Zero Emit Collect
  {125,  70, 102, 4, 4, 4, 4, 0},  // Dizee Bonkers
  {115,  56,  88, 4, 4, 4, 4, 0},  // RizzleKicks - DownWithTheTrumpets
  {168,  92, 181, 4, 4, 4, 4, 0},  // OneTime
  {130,   0, 162, 4, 4, 4, 4, 0},  // WileOut - DJ Zinc
  {145,   0, 170, 4, 4, 4, 4, 0},  // Aphex - Polynomial C
  {124,   0, 189, 4, 4, 4, 4, 0}   // Aphex WindowLicker
};

// Genre 6, Drum&Bass
tuneInfo tuneLibDrumAndBass[10] = {
  {176,  0, 220, 4, 4, 4, 4, 0},  // Girls-DJHypeAndPotential
  {176,  0, 190, 4, 4, 4, 4, 0},  // DuppyMan-ChaseAndStatusCapleton
  {176,  0, 252, 4, 4, 4, 4, 0},  // TheNine-BadCompany
  {176,  0, 200, 4, 4, 4, 4, 0},  // GoldDigger-HighContrast
  {176,  0, 248, 4, 4, 4, 4, 0},  // ShakeUrBody-ShyFX
  {176,  0, 132, 4, 4, 4, 4, 0},  // KingOfTheBeats2016-Aphrodite
  {176,  0, 181, 4, 4, 4, 4, 0},  // LastNight-BennyPage
  {176,  0, 212, 4, 4, 4, 4, 0},  // TurnDownTheLights-BennyPage
  {176,  0, 157, 4, 4, 4, 4, 0},  // PassTheKutchie-BennyPage
  {176,  0, 169, 4, 4, 4, 4, 0},  // PassMeTheRizla-Deekline
};

// Genre 7, HipHop
tuneInfo tuneLibHipHop[10] = {
  {101, 25,  81, 4, 4, 4, 4, 0},  // Lets get ill
  { 90,  0, 109, 4, 4, 4, 4, 0},  // No Diggidy
  { 97, 49,  66, 4, 4, 4, 4, 0},  // ShimmyHimmyYa-ODB
  {103, 69, 122, 4, 4, 4, 4, 0},  // Moma said knock you out    
  {154, 65, 144, 4, 4, 4, 4, 0},  // Bigger than hip hop
  { 93, 61, 108, 4, 4, 4, 4, 0},  // DropItLikeItsCloseToMe-Snoop
  { 98,  0, 101, 4, 4, 4, 4, 0},  // OPP-NaughtyByNature
  {100,  0, 105, 4, 4, 4, 4, 0},  // HipHopHooray
  {106,  0,  95, 4, 4, 4, 4, 0},  // JumpAround-HouseOfPain
  {106,  0,  88, 4, 4, 4, 4, 0},  // InsazlleInTheBazzle-CyprusHazzle
};

tuneInfo currentTune = tuneLibRave[1];
tuneInfo nextTune = tuneLibRave[2];




  
