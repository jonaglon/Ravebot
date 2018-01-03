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
int currentBar = 0;
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
bool stayWithinGenre = false;
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

  // TODO remove me
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
  byte tuneBestEnd; // Tune best end is where the tune should finish if it's not being mixed or the mix is shorter.
  bool playOut;
  tuneInfo(byte aBpm, byte aDrop, byte aTuneLength, byte aMaxFadeIn, byte aMinFadeOut, byte aMaxFadeOut, byte aTuneBestEnd, bool aPlayOut) : 
    bpm(aBpm), drop(aDrop), tuneLength(aTuneLength), maxFadeIn(aMaxFadeIn), minFadeOut(aMinFadeOut), maxFadeOut(aMaxFadeOut), tuneBestEnd(aTuneBestEnd), playOut(aPlayOut) { 
  }
};
 

// Genre 0, RAVE!
tuneInfo tuneLibRave[15] = {
  {149,128, 144, 16,  0, 16, 16, false},  //1  TripToTheMoonPt2-Acen
  {136, 40, 112, 16,  0, 16, 16, false},  //2  Bombscare-2BadMice
  {126,  0, 136,  8,  0, 16,  0, false},  //3  LFO-LFO  
  {132,  0, 136,  8,  0, 16, 16, false},  //4  Infiltrate202-Altern8 
  {122,  0, 118, 16,  0, 16, 16, false},  //5  DirtyCash-SoldOutMix
  {122,  0, 108,  8,  8, 16,  0, false},  //6  Break4Love-Raze
  {126,  0,  96,  8,  0, 16, 12, false},  //7  IsThereAnybodyOutThere-Bassheads
  {128,  0,  80,  8,  4,  8,  0, false},  //8  PacificState-808State
  {150,  0, 155,  0,  0, 16, 16, false},  //9  OutOfSpace-Prodigy
  {132,  0, 162, 16,  0, 16, 16, false},  //10 Breathe-Prodigy
  {138,  0, 148, 16,  0, 16,  4, false},  //11 SmackMyBitchUp-Prodigy
  {128,  0, 124,  8,  0,  8,  0, false},  //12 BreakOfDawn-RhythmOnTheLoose
  {132,  0, 116, 16,  0, 16, 16, false},  //13 BlueMonday-NewOrder
  {131, 40, 120,  8,  0, 16,  4, false},  //14 PlayingWithKnives-BizzarreInc
  {120, 16, 129, 16,  8, 16, 16, false},  //15 KillerFeatTopCat-BoozooBajou
};

// Genre 1, Disco
tuneInfo tuneLibDisco[15] = {
  {125,  0, 102,  8,  0,  8,  8, false},  //1 ILoveTheNightlife - Alecia Bridges
  {110,  0, 152,  8,  4, 16,  0, false},  //2 LastNightADjSavedMyLife-Indeep
  {134,  0, 149,  8,  0, 16,  4, false},  //3 LayAllYourLoveOnMe-Abba
  {121,  0, 152,  8,  0, 16 , 0, false},  //4 HotStuff-DonnaSummer
  {128,  0, 108,  8,  4, 12, 12, false},  //5 RingMyBell-AnitaWard
  {128,  0, 213, 16,  0, 16,  0, false},  //6 EverybodyDance-Chic
  {111,  0, 100,  8,  0,  8, 16, false},  //7 GoodTimes-Chic
  {102,  0, 112,  8,  0,  8,  4, false},  //8 ThinkingOfYou-SisSledge
  {115,  0, 104,  8,  0, 16, 16, false},  //9 SheCantLoveYou-Chemise
  {112,  0, 130,  8,  0, 16, 16, false},  //10 Automatic-PointerSisters   
  {105,  0, 120,  8,  0,  8,  8, false},  //11 StayinAlive-BeeGees  
  {114,  0, 103,  4,  0, 10,  8, false},  //12 BestOfMyLove-TheEmotions
  {125,  0,  96,  4,  0, 10, 10, false},  //13 ILoveTheNightlife-AliciaBridges
  {110,  0,  96,  8,  0, 16, 12, false},  //14 NightFever-BeeGees
  {111,  0, 102,  8,  0,  8,  4, false},  //15 GiveMeTheNight-GeorgeBenson
};

// Genre 2, Reggae 
tuneInfo tuneLibReggae[15] = {
  {170,  0, 132,  8,  0, 16, 16, false},  //1 RingTheAlarm-TenorSaw
  {102,  0, 118,  8,  0,  8,  8, false},  //2 FunkyKingston-Toots
  {164,  0, 164,  8,  0, 16, 16, false},  //3 UnderMeSlengTeng-WayneSmith
  {162,  0, 128, 16,  0, 16, 12, false},  //4 BamBam-SisNancy
  {162,  0, 152,  8,  0, 16, 12, false},  //5 StrictlyRoots-Althea&Donna 
  {154,  0, 102,  0,  0, 16, 16, false},  //6 WelcomeToJamrock-DamianMarley
  {146,  0, 146,  0,  0, 16, 16, false},  //7 ItsAPity-TanyaStevens
  {177,  0, 142,  8,  0, 16, 16, false},  //8 FeelLikeJumping-MarciaG 
  {164,  0, 160,  8,  0, 16, 16, false},  //9 CantStopNow-MajorLazer
  {148,  0, 106,  8,  0, 16, 14, false},  //10 PressureDrop-Toots
  {104,  0, 100,  4,  0, 16, 14, false},  //11 CouldYouBeLoved-BobMarley
  { 90,  0, 101,  8,  0, 16, 16, false},  //12 DidYouReallyKnow-MungoHiFi
  {131,  0, 129,  0,  0,  8,  8, false},  //13 ThingsInLife-BarryBrown 
  { 90,  0,  89,  8 , 0,  4,  4, false},  //14 StandUp-MrBenn
  { 93,  0, 121,  8,  0, 16, 16, false},  //15 LongTime-MrBenn  
};

// Genre 3, Rock&Pop
tuneInfo tuneLibRockAndPop[15] = {
  {160,  0, 117,  0,  0, 16, 16, false},  //1 KidsInAmerica-KimWilde
  {126,  0, 120,  8,  0, 16, 12, false},  //2 CantGetYouOut-Kylie
  {112,  0, 102,  8,  0,  8,  6, false},  //3 ICantGoForThat-Hall&Oates
  { 97,  0,  63,  0,  0,  0,  0, false},  //4 Faith-GeorgeMichael
  {122, 48,  98,  0,  0,  8,  8, false},  //5 GrooveIsInTheHeart-DeeLite
  {126,  0, 108,  4,  0,  8, 12, false},  //6 SweetDreams-Euritmics
  {122, 38, 100,  4,  0,  8,  8, false},  //7 StuckInTheMiddle-SteelersWheel
  {164,  0, 135,  8,  0,  8,  6, false},  //8 Martha&Muffins Echo Beach
  {199,  0, 111,  0,  0,  0,  0, false},  //9 DreamingOfYou-TheCoral
  { 99,  0,  58,  0,  4,  4,  0, false},  //10 BlisterInTheSun-VoilentFemmes
  {114,  0,  96,  0,  4,  4,  0, false},  //11 ALittleRespect-Erasure  
  { 99,  0,  99,  8,  0, 10,  8, false},  //12 Superstition-StevieWonder
  {112,  0, 101,  0,  0,  8,  8, false},  //13 Kiss-Prince
  {112, 26, 106, 16,  0,  8,  8, false},  //14 WatchOutForThis-MajorLazer 
  {134,  0, 138,  8,  0, 10,  8, false},  //15 YouCantTouchThis-MCHammer
};

// Genre 4, Easy
tuneInfo tuneLibEasy[15] = {
  {122,  0, 142,  0,  4,  4,  0, false},  //1 BackToMyRoots - RichieHavens
  {104,  0,  59,  0,  4,  4,  0, false},  //2 Think - Aretha
  {100,  0, 181,  0,  4,  4,  0, false},  //3 As - Wonder
  {174,  0, 150,  4,  4,  4,  0, false},  //4 Roady - FatFreddyNextmen
  {132,  0,  88,  0,  4,  4,  0, false},  //5 Beggin - FrankieValli
  { 98,  0,  72,  0,  4,  4,  0, false},  //6 IGotAWoman - RayCharles 
  {156,  0, 140,  4,  4,  4,  0, false},  //7 MilkAndHoney-PrinceFatty
  {126,  0, 123,  0,  4,  4,  0, false},  //8 BackToBlack - Amy 
  {132,  0, 166,  0,  4,  4,  0, false},  //9 MasterBlaster-StevieWonder
  {109,  0, 113,  0,  4,  4,  0, false},  //10 AllNightLong - LionelRichie
  { 96,  0,  96,  0,  4,  4,  0, false},  //11 INeedADollar-AloeBlacc     
  {122,  0, 120,  4,  4,  4,  0, false},  //12 GotToGiveItUp-MarvinGaye
  {139, 37, 124,  4,  0,  0, 0, false},  //13 TheHumansAreDead-FOTC
  {175,  0, 176,  8,  0,  8, 0, false},  //14 AgainAndAgain-RootsManuva
  {116, 24, 142,  4,  0,  6, 6, false},  //15 JamacianBoy-LoneRanger  
};

// Genre 5, Dance
tuneInfo tuneLibDance[15] = {
  {134, 29, 119,  0,  4,  4,  0, false},  //1 A rinky dinky
  {110, 58,  91,  0,  4,  4,  0, false},  //2 Kelis - Trick Me
  {150, 25, 130,  4,  4,  4,  0, false},  //3 Dubbleedge - Lips to the floor
  {134,105, 169,  0,  4,  4,  0, false},  //4 Zero Emit Collect
  {125, 70, 102,  0,  4,  4,  0, false},  //5 Dizee Bonkers
  {115, 56,  88,  0,  4,  4,  0, false},  //6 RizzleKicks - DownWithTheTrumpets
  {168, 92, 181,  0,  4,  4,  0, false},  //7 OneTime
  {130,  0, 162,  0,  4,  4,  0, false},  //8 WileOut - DJ Zinc
  {145,  0, 170,  0,  4,  4,  0, false},  //9 Aphex - Polynomial C
  {124,  0, 189,  0,  4,  4,  0, false},  //10 Aphex WindowLicker
  {121,  0, 170,  8,  0, 16,  0, false},  //11 OverAndOver-HotChip
  {140,  0, 120,  0,  0,  0,  0, false},  //12 Omen - Prodigy
  {128,  0, 110,  0,  0,  0,  0, false},  //13 DibbyDibbySound-MajorLazer
  {132,  0, 120,  0,  0,  0,  0, false},  //14 ClintEastwood-EdCaseGorillaz
  {134,  0, 105,  0,  0,  0,  0, false},  //15 AllAboutThatBass-MeganTrainor
};

/*
  {000,  0, 000,  0,  4,  4,  0, false},  //16 SomeSong-Someone
  {000,  0, 000,  0,  4,  4,  0, false},  //17 SomeSong-Someone
  {000,  0, 000,  0,  4,  4,  0, false},  //18 SomeSong-Someone
  {000,  0, 000,  0,  4,  4,  0, false},  //19 SomeSong-Someone
  {000,  0, 000,  0,  4,  4,  0, false},  //20 SomeSong-Someone  
//  bpm drop tuneLength maxFadeIn minFadeOut maxFadeOut dropOffset  */

// Genre 6, Drum&Bass
tuneInfo tuneLibDrumAndBass[20] = {
  {176,  0, 182, 16,  0, 16,  0, false},  //1 Girls-DJHypeAndPotential
  {176,  0, 185, 16,  8, 16, 16, false},  //2 DuppyMan-ChaseAndStatusCapleton
  {176,  0, 252,  0,  4,  4,  0, false},  //3 TheNine-BadCompany
  {176,  0, 200, 16,  4,  4,  0, false},  //4 GoldDigger-HighContrast
  {176,  0, 248,  0,  4,  4,  0, false},  //5 ShakeUrBody-ShyFX
  {176,  0, 132,  0,  4,  4,  0, false},  //6 KingOfTheBeats2016-Aphrodite
  {176,  0, 181,  0,  4,  4,  0, false},  //7 LastNight-BennyPage
  {176,  0, 212,  0,  4,  4,  0, false},  //8 TurnDownTheLights-BennyPage
  {176,  0, 157,  0,  4,  4,  0, false},  //9 PassTheKutchie-BennyPage
  {176,  0, 169,  0,  4,  4,  0, false},  //10 PassMeTheRizla-Deekline
  {176,  0, 232,  0,  0,  0,  0, false},  //11 CryingOut-BennyPageSerialKillazMix
  {179,  0, 108,  0,  0,  0,  0, false},  //12 LivingInJungles-BedouinSoundclash
  {179,  0, 274,  0,  0,  0,  0, false},  //13 Blade Runner Flip Side
  {176,  0, 224,  0,  0,  0,  0, false},  //14 BamBam-SerialKillaz
  {176,  0, 224,  0,  0,  0,  0, false},  //15 NoNoNo-SerialKillaz  
  {100,  0, 100,  0,  4,  4,  0, false},  //16 SomeSong-Someone
  {100,  0, 100,  0,  4,  4,  0, false},  //17 SomeSong-Someone
  {100,  0, 100,  0,  4,  4,  0, false},  //18 SomeSong-Someone
  {100,  0, 100,  0,  4,  4,  0, false},  //19 SomeSong-Someone
  {100,  0, 100,  0,  4,  4,  0, false},  //20 SomeSong-Someone  
};

// Genre 7, HipHop
tuneInfo tuneLibHipHop[20] = {
  {101, 25,  81,  4,  0,  8,  8, false},  //1 Lets get ill
  { 90,  0, 108,  4,  0, 16,  0, false},  //2 No Diggidy
  { 97, 49,  66,  4,  0, 16,  0, false},  //3 ShimmyShimmyYa-ODB
  {103, 69, 122,  4,  0,  8,  8, false},  //4 Moma said knock you out    
  {154, 65, 140,  4,  0,  8,  0, false},  //5 Bigger than hip hop
  { 93, 61, 108,  8,  0,  8,  8, false},  //6 DropItLikeItsCloseToMe-Snoop
  { 98,  0, 101,  4,  0,  8,  8, false},  //7 OPP-NaughtyByNature
  {100,  0, 105,  0,  4,  4,  0, false},  //8 HipHopHooray
  {106,  0,  91,  0,  0,  8,  0, false},  //9 JumpAround-HouseOfPain
  {106,  0,  88,  2,  0, 16,  0, false},  //10 InsazlleInTheBazzle-CyprusHazzle
  {108,  0, 101,  0,  2,  8,  6, false},  //11 KingKunta-KendrickLamar
  { 95,  0,  82,  8,  0,  8,  8, false},  //12 GinAndJuice-Snoop
  {108,  0,  97,  8,  0,  8,  8, false},  //13 HotInHere-Nelly
  { 92,  0, 133,  4,  4,  8,  0, false},  //14 CaliforniaLove-DreAnd2Pac
  { 97,  0,  80,  8,  0,  8,  0, false},  //15 TheOnlyOne-DangermouseJemini  
  { 93,  0, 102,  8,  4,  4,  0, false},  //16 FamilyAffair-MaryJBlige
  { 93,  0,  60,  8,  0,  8,  8, false},  //17 HitsFromTheBong-CypressHill
  { 96,  0,  98,  8,  0,  8,  8, false},  //18 Regulate-WarrenG
  { 90,  0,  77,  8,  0,  8,  8, false},  //19 GetUrFreakOn-MissyElliot
  { 96,  0,  80,  4,  0,  8,  8, false},  //20 GoldDigger-Kanye
};


tuneInfo currentTune = tuneLibHipHop[0];
tuneInfo nextTune = tuneLibHipHop[0];




  
