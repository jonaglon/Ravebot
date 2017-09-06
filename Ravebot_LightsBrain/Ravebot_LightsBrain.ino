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
tuneInfo tuneLibRave[15] = {
  /*{149,128, 16,  4,  0, 4, 4},  // TripToTheMoonPt2-Acen
  {136, 40, 16,  4,  0, 4, 4},  // Bombscare-2BadMice
  {126,  0, 16,  4,  0, 4, 4},  // LFO-LFO  
  {132,  0, 16,  4,  0, 4, 4},  // Infiltrate202-Altern8 
  {122,  0, 16, 4,  0, 4, 4},  // DirtyCash-SoldOutMix
  {122,  0, 16, 4,  0, 4, 4},  // Break4Love-Raze
  {126,  0, 16, 4,  0, 4, 4},  // IsThereAnybodyOutThere-Bassheads
  {128,  0, 16, 4,  0, 4, 4},  // PacificState-808State
  {150,  0, 16, 4,  0, 4, 4},  // OutOfSpace-Prodigy
  {132,  0, 16, 4,  0, 4, 4},  // Breathe-Prodigy
  {138,  0, 16, 4,  0, 4,  4},  // SmackMyBitchUp-Prodigy
  {128,  0, 16, 4,  0, 4,  4},  // BreakOfDawn-RhythmOnTheLoose
  {132,  0, 16, 4,  0, 4, 4},  // BlueMonday-NewOrder  */
  
  {149,128, 144, 16,  0, 16, 16},  //1  TripToTheMoonPt2-Acen
  {136, 40, 112, 16,  0, 16, 16},  //2  Bombscare-2BadMice
  {126,  0, 136,  8,  0, 16,  0},  //3  LFO-LFO  
  {132,  0, 136,  8,  0, 16, 16},  //4  Infiltrate202-Altern8 
  {122,  0, 118, 16,  0, 16, 16},  //5  DirtyCash-SoldOutMix
  {122,  0, 108,  8,  8, 16,  0},  //6  Break4Love-Raze
  {126,  0,  96,  8,  0, 16, 12},  //7  IsThereAnybodyOutThere-Bassheads
  {128,  0,  80,  8,  4,  8,  0},  //8  PacificState-808State
  {150,  0, 155,  0,  0, 16, 16},  //9  OutOfSpace-Prodigy
  {132,  0, 162, 16,  0, 16, 16},  //10 Breathe-Prodigy
  {138,  0, 148, 16,  0, 16,  4},  //11 SmackMyBitchUp-Prodigy
  {128,  0, 124,  8,  0,  8,  0},  //12 BreakOfDawn-RhythmOnTheLoose
  {132,  0, 116, 16,  0, 16, 16},  //13 BlueMonday-NewOrder
  {131, 40, 120,  8,  0, 16,  4},  //14 PlayingWithKnives-BizzarreInc
  {120, 16, 129, 16,  8, 16, 16},  //15 KillerFeatTopCat-BoozooBajou
};
// Genre 1, Disco
tuneInfo tuneLibDisco[15] = {
  {125,  0, 102,  8,  0,  8,  8},  //1 ILoveTheNightlife - Alecia Bridges
  {110,  0, 152,  8,  4, 16,  0},  //2 LastNightADjSavedMyLife-Indeep
  {134,  0, 149,  8,  0, 16,  4},  //3 LayAllYourLoveOnMe-Abba
  {121,  0, 152,  8,  0, 16 , 0},  //4 HotStuff-DonnaSummer
  {128,  0, 108,  8,  4, 12, 12},  //5 RingMyBell-AnitaWard
  {128,  0, 213, 16,  0, 16,  0},  //6 EverybodyDance-Chic
  {111,  0, 100,  8,  0,  8, 16},  //7 GoodTimes-Chic
  {102,  0, 112,  8,  0,  8,  4},  //8 ThinkingOfYou-SisSledge
  {115,  0, 104,  8,  0, 16, 16},  //9 SheCantLoveYou-Chemise
  {112,  0, 130,  8,  0, 16, 16},  //10 Automatic-PointerSisters   
  {105,  0, 120,  8,  0,  8,  8},  //11 StayinAlive-BeeGees
  {114,  0, 103,  4,  0, 10,  8},  //12 BestOfMyLove-TheEmotions
  {125,  0,  96,  4,  0, 10, 10},  //13 ILoveTheNightlife-AliciaBridges
  {110,  0,  96,  8,  0, 16, 12},  //14 NightFever-BeeGees
  {111,  0, 102,  8,  0,  8,  4},  //15 GiveMeTheNight-GeorgeBenson
};

// Genre 2, Reggae 
tuneInfo tuneLibReggae[15] = {
  {170,  0, 132,  8,  0, 16, 16},  //1 RingTheAlarm-TenorSaw
  {102,  0, 118,  8,  0,  8,  8},  //2 FunkyKingston-Toots
  {164,  0, 164,  8,  0, 16, 16},  //3 UnderMeSlengTeng-WayneSmith
  {162,  0, 128, 16,  0, 16, 12},  //4 BamBam-SisNancy
  {162,  0, 152,  8,  0, 16, 12},  //5 StrictlyRoots-Althea&Donna 
  {154,  0, 102,  0,  0, 16, 16},  //6 WelcomeToJamrock-DamianMarley
  {146,  0, 146,  0,  0, 16, 16},  //7 ItsAPity-TanyaStevens
  {177,  0, 142,  8,  0, 16, 16},  //8 FeelLikeJumping-MarciaG 
  {164,  0, 160,  8,  0, 16, 16},  //9 CantStopNow-MajorLazer
  {148,  0, 106,  8,  0, 16, 14},  //10 PressureDrop-Toots
  {104,  0, 100,  4,  0, 16, 14},  //11 CouldYouBeLoved-BobMarley
  { 90,  0, 101,  8,  0, 16, 16},  //12 DidYouReallyKnow-MungoHiFi
  {131,  0, 129,  0,  0,  8,  8},  //13 ThingsInLife-BarryBrown 
  { 90,  0,  89,  8 , 0,  4,  4},  //14 StandUp-MrBenn
  { 93,  0, 121,  8,  0, 16, 16},  //15 LongTime-MrBenn  
};

// Genre 3, Rock&Pop
tuneInfo tuneLibRockAndPop[15] = {
  {160,  0, 117,  0,  0, 16, 16},  //1 KidsInAmerica-KimWilde
  {126,  0, 120,  8,  0, 16, 12},  //2 CantGetYouOut-Kylie
  {112,  0, 102,  8,  0,  8,  6},  //3 ICantGoForThat-Hall&Oates
  { 97,  0,  63,  0,  0,  0,  0},  //4 Faith-GeorgeMichael
  {122, 48,  98,  0,  0,  8,  8},  //5 GrooveIsInTheHeart-DeeLite
  {126,  0, 108,  4,  0,  8, 12},  //6 SweetDreams-Euritmics
  {122, 38, 100,  4,  0,  8,  8},  //7 StuckInTheMiddle-SteelersWheel
  {164,  0, 135,  8,  0,  8,  6},  //8 Martha&Muffins Echo Beach
  {199,  0, 111,  0,  0,  0,  0},  //9 DreamingOfYou-TheCoral
  { 99,  0,  58,  0,  4,  4,  0},  //10 BlisterInTheSun-VoilentFemmes
  {114,  0,  96,  0,  4,  4,  0},  //11 ALittleRespect-Erasure  
  { 99,  0,  99,  8,  0, 10,  8},  //12 Superstition-StevieWonder
  {112,  0, 101,  0,  0,  8,  8},  //13 Kiss-Prince
  {112, 26, 106, 16,  0,  8,  8},  //14 WatchOutForThis-MajorLazer 
  {134,  0, 138,  8,  0, 10,  8},  //15 YouCantTouchThis-MCHammer
};

// Genre 4, Easy
tuneInfo tuneLibEasy[15] = {
  {122,  0, 142,  0,  4,  4,  0},  //1 BackToMyRoots - RichieHavens
  {104,  0,  59,  0,  4,  4,  0},  //2 Think - Aretha
  {100,  0, 181,  0,  4,  4,  0},  //3 As - Wonder
  {174,  0, 150,  4,  4,  4,  0},  //4 Roady - FatFreddyNextmen
  {132,  0,  88,  0,  4,  4,  0},  //5 Beggin - FrankieValli
  { 98,  0,  72,  0,  4,  4,  0},  //6 IGotAWoman - RayCharles 
  {156,  0, 140,  4,  4,  4,  0},  //7 MilkAndHoney-PrinceFatty
  {126,  0, 123,  0,  4,  4,  0},  //8 BackToBlack - Amy 
  {132,  0, 166,  0,  4,  4,  0},  //9 MasterBlaster-StevieWonder
  {109,  0, 113,  0,  4,  4,  0},  //10 AllNightLong - LionelRichie
  { 96,  0,  96,  0,  4,  4,  0},  //11 INeedADollar-AloeBlacc     
  {122,  0, 120,  4,  4,  4,  0},  //12 GotToGiveItUp-MarvinGaye
  {139, 37, 124,  4,  0,  0, 0},  //13 TheHumansAreDead-FOTC
  {175,  0, 176,  8,  0,  8, 0},  //14 AgainAndAgain-RootsManuva
  {116, 24, 142,  4,  0,  6, 6},  //15 JamacianBoy-LoneRanger  
};

// Genre 5, Dance
tuneInfo tuneLibDance[15] = {
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
  {121,   0, 170,  8,  0, 16,  0},  //11 OverAndOver-HotChip
  {140,  0, 120, 0, 0, 0, 0},  //12 Omen - Prodigy
  {128,  0, 110, 0, 0, 0, 0},  //13 DibbyDibbySound-MajorLazer
  {132,  0, 120, 0, 0, 0, 0},  //14 ClintEastwood-EdCaseGorillaz
  {134,  0, 105, 0, 0, 0, 0},  //15 AllAboutThatBass-MeganTrainor
};

//  {000,  0, 000, 0, 0, 0, 0},  // SomeSong-Someone
//  bpm drop tuneLength maxFadeIn minFadeOut maxFadeOut dropOffset

// Genre 6, Drum&Bass
tuneInfo tuneLibDrumAndBass[15] = {
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
  {000,  0, 000, 0, 0, 0, 0},  //11 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //12 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //13 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //14 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //15 SomeSong-Someone  
};

// Genre 7, HipHop
tuneInfo tuneLibHipHop[15] = {
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
  {000,  0, 000, 0, 0, 0, 0},  //11 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //12 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //13 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //14 SomeSong-Someone
  {000,  0, 000, 0, 0, 0, 0},  //15 SomeSong-Someone  
};

tuneInfo currentTune = tuneLibRave[1];
tuneInfo nextTune = tuneLibRave[2];




  
