  
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
int fakeBeatLengh = 240;

// Set by midi in to be 1-16 with beat.
short sixteenBeats = 0;

int mainVolume = 100; // 127 actual max but we won't exceed 100.
int currentBar = 0;
int mixCurrentBar = 0; // This counts from the start of a mix
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
int last10Genres[10] = {0,0,0,0,0,0,0,0,0,0};
int last10Tracks[10] = {0,0,0,0,0,0,0,0,0,0};

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
  LEDS.setBrightness(50); // 255 max

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
 
// Genre 0, RAVE!
tuneInfo tuneLibRave[14] = {
  {149,128, 144, 16,  0, 16, 16},  // TripToTheMoonPt2-Acen
  {136, 40, 112, 16,  0, 16, 16},  // Bombscare-2BadMice
  {126,  0, 136,  8,  0, 16,  0},  // LFO-LFO  
  {132,  0, 136, 16,  0, 16, 16},  // Infiltrate202-Altern8 
  {122,  0, 118, 16,  0, 16, 16},  // DirtyCash-SoldOutMix
  {122,  0, 108,  8,  8, 16,  0},  // Break4Love-Raze
  {126,  0,  96,  8,  0, 16, 12},  // IsThereAnybodyOutThere-Bassheads
  {128,  0,  80,  8,  4,  8,  0},  // PacificState-808State
  {150,  0, 155,  0,  0, 16, 16},  // OutOfSpace-Prodigy
  {124,  0, 168, 16,  0, 16,  0},  // WhatCanYouDoForMe-UtahSaints
  {132,  0, 162, 16,  0, 16, 16},  // Breathe-Prodigy
  {138,  0, 165, 16,  0, 16,  4},  // SmackMyBitchUp-Prodigy
  {128,  0, 124,  8,  0,  8,  0},  // BreakOfDawn-RhythmOnTheLoose
  {132,  0, 116, 16,  0, 16, 16},  // BlueMonday-NewOrder
};

// Genre 1, Disco
    tuneInfo tuneLibDisco[14] = {
  {125,  0, 102,  8,  0,  8,  8},  // ILoveTheNightlife - Alecia Bridges
  {110,  0, 152,  8,  4, 16,  0},  // LastNightADjSavedMyLife-Indeep
  {134,  0, 149,  8,  0, 16,  4},  // LayAllYourLoveOnMe-Abba
  {121,  0, 152,  8,  0, 16 , 0},  // HotStuff-DonnaSummer
  {128,  0, 108,  8,  4, 12, 12},  // RingMyBell-AnitaWard
  {128,  0, 213, 16,  0, 16,  0},  // EverybodyDance-Chic
  {111,  0, 100,  8,  0, 16, 16},  // GoodTimes-Chic
  {102,  0, 112,  8,  0,  8,  4},  // ThinkingOfYou-SisSledge
  {115,  0, 104,  8,  0, 16, 16},  // SheCantLoveYou-Chemise
  {112,  0, 130,  8,  0, 16, 16},  // Automatic-PointerSisters   
  {105,  0, 120,  8,  0,  8,  8},  // StayinAlive-BeeGees
  {114,  0, 103,  4,  0, 10,  8},  // BestOfMyLove-TheEmotions
  {125,  0,  96,  4,  0, 10, 10},  // ILoveTheNightlife-AliciaBridges
  {110,  0,  96,  8,  0, 16, 12},  // NightFever-BeeGees
};

// Genre 2, Reggae 
tuneInfo tuneLibReggae[14] = {
  {170,  0, 132,  8,  0, 16, 16},  // RingTheAlarm-TenorSaw
  {102,  0, 118,  8,  0,  8,  8},  // FunkyKingston-Toots
  {164,  0, 164,  8,  0, 16, 16},  // UnderMeSlengTeng-WayneSmith
  {162,  0, 128, 16,  0, 16, 12},  // BamBam-SisNancy
  {162,  0, 152,  8,  0, 16, 12},  // StrictlyRoots-Althea&Donna 
  {154,  0, 102,  0,  0, 16, 16},  // WelcomeToJamrock-DamianMarley
  {146,  0, 146,  0,  0, 16, 16},  // ItsAPity-TanyaStevens
  {177,  0, 142,  8,  0, 16, 16},  // FeelLikeJumping-MarciaG 
  {164,  0, 160,  8,  0, 16, 16},  // CantStopNow-MajorLazer
  {148,  0, 106,  8,  0, 16, 14},  // PressureDrop-Toots
  {104,  0, 100,  4,  0, 16, 14},  // CouldYouBeLoved-BobMarley
  { 90,  0, 101,  8,  0, 16, 16},  // DidYouReallyKnow-MungoHiFi
  {131,  0, 129,  0,  0,  8,  8},  // ThingsInLife-BarryBrown
  { 90,  0,  89,  8 , 0,  4,  4},  // StandUp-MrBenn
};

// Genre 3, Rock&Pop
tuneInfo tuneLibRockAndPop[11] = {
  {160,  0, 117,  0,  0, 16, 16},  // KidsInAmerica-KimWilde
  {126,  0, 120,  8,  0, 16, 12},  // CantGetYouOut-Kylie
  {112,  0, 102,  8,  0,  8,  6},  // ICantGoForThat-Hall&Oates
  { 97,  0,  63,  0,  0,  0,  0},  // Faith-GeorgeMichael
  {122, 48, 106,  0,  0,  8,  8},  // GrooveIsInTheHeart-DeeLite
  {126,  0, 108,  4,  0, 16, 12},  // SweetDreams-Euritmics
  {122, 38, 100,  4,  0,  8,  8},  // StuckInTheMiddle-SteelersWheel
  {164,  0, 135,  8,  0,  8,  6},  // Martha&Muffins Echo Beach
  {199,  0, 111,  0,  0,  0,  0},  // DreamingOfYou-TheCoral

  
  { 99,  0,  58,  0,  4,  4,  0},  // BlisterInTheSun-VoilentFemmes
  {114,  0,  96,  0,  4,  4,  0},  // ALittleRespect-Erasure  
};

//  {199,  0, 199, 16, 0, 16, 16},  // SomeSong-Someone

// Genre 4, Easy
tuneInfo tuneLibEasy[12] = {
  {122,  0, 142,  0,  4,  4,  0}, // BackToMyRoots - RichieHavens
  {104,  0,  59,  0,  4,  4,  0}, // Think - Aretha
  {100,  0, 181,  0,  4,  4,  0}, // As - Wonder
  {174,  0, 150,  4,  4,  4,  0}, // Roady - FatFreddyNextmen
  {132,  0,  88,  0,  4,  4,  0}, // Beggin - FrankieValli
  { 98,  0,  72,  0,  4,  4,  0}, // IGotAWoman - RayCharles 
  {156,  0, 140,  4,  4,  4,  0}, // MilkAndHoney-PrinceFatty
  {126,  0, 123,  0,  4,  4,  0}, // BackToBlack - Amy 
  {132,  0, 166,  0,  4,  4,  0}, // MasterBlaster-StevieWonder
  {109,  0, 113,  0,  4,  4,  0}, // AllNightLong - LionelRichie
  { 96,  0,  96,  0,  4,  4,  0}, // INeedADollar-AloeBlacc     
  {122,  0, 120,  4,  4,  4,  0}, // GotToGiveItUp-MarvinGaye
};

// Genre 5, Dance
tuneInfo tuneLibDance[10] = {
  {134,  29, 119,  0,  4,  4,  0},  // A rinky dinky
  {110,  58,  91,  0,  4,  4,  0},  // Kelis - Trick Me
  {150,  25, 130,  4,  4,  4,  0},  // Dubbleedge - Lips to the floor
  {134, 105, 169,  0,  4,  4,  0},  // Zero Emit Collect
  {125,  70, 102,  0,  4,  4,  0},  // Dizee Bonkers
  {115,  56,  88,  0,  4,  4,  0},  // RizzleKicks - DownWithTheTrumpets
  {168,  92, 181,  0,  4,  4,  0},  // OneTime
  {130,   0, 162,  0,  4,  4,  0},  // WileOut - DJ Zinc
  {145,   0, 170,  0,  4,  4,  0},  // Aphex - Polynomial C
  {124,   0, 189,  0,  4,  4,  0},   // Aphex WindowLicker
};

// Genre 6, Drum&Bass
tuneInfo tuneLibDrumAndBass[10] = {
  {176,  0, 220,  0,  4,  4,  0},  // Girls-DJHypeAndPotential
  {176,  0, 190,  0,  4,  4,  0},  // DuppyMan-ChaseAndStatusCapleton
  {176,  0, 252,  0,  4,  4,  0},  // TheNine-BadCompany
  {176,  0, 200,  0,  4,  4,  0},  // GoldDigger-HighContrast
  {176,  0, 248,  0,  4,  4,  0},  // ShakeUrBody-ShyFX
  {176,  0, 132,  0,  4,  4,  0},  // KingOfTheBeats2016-Aphrodite
  {176,  0, 181,  0,  4,  4,  0},  // LastNight-BennyPage
  {176,  0, 212,  0,  4,  4,  0},  // TurnDownTheLights-BennyPage
  {176,  0, 157,  0,  4,  4,  0},  // PassTheKutchie-BennyPage
  {176,  0, 169,  0,  4,  4,  0},  // PassMeTheRizla-Deekline
};

// Genre 7, HipHop
tuneInfo tuneLibHipHop[10] = {
  {101, 25,  81,  0,  4,  4,  0},  // Lets get ill
  { 90,  0, 109,  0,  4,  4,  0},  // No Diggidy
  { 97, 49,  66,  0,  4,  4,  0},  // ShimmyHimmyYa-ODB
  {103, 69, 122,  0,  4,  4,  0},  // Moma said knock you out    
  {154, 65, 140,  4,  4,  4,  0},  // Bigger than hip hop
  { 93, 61, 108,  0,  4,  4,  0},  // DropItLikeItsCloseToMe-Snoop
  { 98,  0, 101,  0,  4,  4,  0},  // OPP-NaughtyByNature
  {100,  0, 105,  0,  4,  4,  0},  // HipHopHooray
  {106,  0,  95,  0,  4,  4,  0},  // JumpAround-HouseOfPain
  {106,  0,  88,  0,  4,  4,  0},  // InsazlleInTheBazzle-CyprusHazzle
};

tuneInfo currentTune = tuneLibRave[1];
tuneInfo nextTune = tuneLibRave[2];




  
