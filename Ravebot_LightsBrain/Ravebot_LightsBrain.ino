/* __                 _           _               __ _       _     _  
  /__\ __ ___   _____| |__   ___ | |_            / /(_) __ _| |__ | |_ ___
 / \/// _` \ \ / / _ \ '_ \ / _ \| __|  _____   / / | |/ _` | '_ \| __/ __|
/ _  \ (_| |\ V /  __/ |_) | (_) | |_  |_____| / /__| | (_| | | | | |_\__ \
\/ \_/\__,_| \_/ \___|_.__/ \___/ \__|         \____/_|\__, |_| |_|\__|___/
                                                       |___/                       */
#include<Arduino.h>
#include<Wire.h>
#include<FastLED.h>

const bool testMode = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ;
const bool beatTestMode = true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ;

unsigned long timey;
unsigned long fakeBeatCount = 0;
int ticky=0;

unsigned long beatTimes[10] = {0,0,0,0,0,0,0,0,0,0};
int fakeBeatLengh = 500;

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

// LED Intensity
int ledIntensity = 50;
byte wheelR;
byte wheelG;
byte wheelB;

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
  Serial1.begin(28800); // rx for receiving
  Serial2.begin(28800); // tx for sending
  // Talk to the other arduino
  // Serial3.begin(9600);

  // Make random more random
  randomSeed(analogRead(0));

  //pinMode(12, OUTPUT); // rgb LED Setup
  LEDS.addLeds<WS2811_PORTD, 5>(rgbwLeds, 488); // Hardcoded to ports:25,26,27,28,14,15
  LEDS.setBrightness(64); // 128 good max, 255 actual /max

  setMainVolume(mainVolume);

  if (testMode)
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
tuneInfo tuneLibRave[17] = {
  {149, 68, 128, 16,  0, 16, 16, true},   //1  TripToTheMoonPt2-Acen.
  {136, 80, 112, 32,  0, 16, 16, false},  //2  Bombscare-2BadMice.
  {126,  0, 114,  8,  0, 16,  8, false},  //3  LFO-LFO.
  {131,  0, 136,  8,  0, 16, 16, true},   //4  Infiltrate202-Altern8.
  {122,  0, 118,  8,  0, 16, 16, true},   //5  DirtyCash-SoldOutMix.
  {122,  0, 108,  8,  0, 16, 16, true},   //6  Break4Love-Raze.
  {124, 44, 100, 16,  0, 16, 16, true},   //7  IsThereAnybodyOutThere-Bassheads.
  {128,  0,  80,  8,  4, 16,  8, false},  //8  PacificState-808State.
  {150,  0, 163, 16,  0, 16,  8, false},  //9  OutOfSpace-Prodigy.
  {132,  0, 142, 16,  0, 16, 16, true},   //10 Breathe-Prodigy.
  {138,  0, 148, 16,  0, 16,  0, false},  //11 SmackMyBitchUp-Prodigy.
  {128,  0, 124, 16,  0, 16, 16, false},  //12 BreakOfDawn-RhythmOnTheLoose.
  {132,  0, 132, 16,  0, 16,  0, false},  //13 BlueMonday-NewOrder.
  {132, 60, 120,  8,  0, 16,  4, false},  //14 PlayingWithKnives-BizzarreInc.
  {120, 16, 129, 16,  8, 16, 16, false},  //15 KillerFeatTopCat-BoozooBajou
  {136, 60, 112,  8,  0, 16,  0, false},  //16 LivingLegends-RaggaTwins
  {135, 48, 132,  8,  0, 16,  9, false},  //17 FeelingForYou-Cassius
};

// Genre 1, Disco
tuneInfo tuneLibDisco[15] = {
  {125,  0, 102,  8,  0,  8,  8, true},   // 1 ILoveTheNightlife - Alecia Bridges
  {110,  0, 128,  8,  4, 16, 16, true},   // 2 LastNightADjSavedMyLife-Indeep
  {134,  0, 149,  8,  0, 16, 16, true},   // 3 LayAllYourLoveOnMe-Abba
  {121,  0, 156,  8,  0, 16, 14, false},  // 4 HotStuff-DonnaSummer
  {128,  0, 110,  8,  4,  8, 14, true},   // 5 RingMyBell-AnitaWard
  {130,  0, 209, 16,  0, 16, 16, true},   // 6 EverybodyDance-Chic
  {111,  0, 100,  8,  0, 16, 16, true},   // 7 GoodTimes-Chic
  {102,  0, 108,  8,  0, 10,  8, false},  // 8 ThinkingOfYou-SisSledge
  {117,  0, 104,  8,  0,  8 , 8, true},   // 9 SheCantLoveYou-Chemise
  {112,  0, 130,  8,  0, 16, 16, true},   // 10 Automatic-PointerSisters   
  {105,  0, 120,  8,  0,  8,  8, true},   // 11 StayinAlive-BeeGees  
  {114,  0, 100,  4,  0,  8,  8, false},  // 12 BestOfMyLove-TheEmotions
  {125,  0,  96,  4,  0, 16, 16, true},   // 13 ILoveTheNightlife-AliciaBridges
  {110,  0,  96,  8,  0, 16, 16, true},   // 14 NightFever-BeeGees
  {111,  0, 102,  8,  0, 16,  4, true},   // 15 GiveMeTheNight-GeorgeBenson
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
  {179,  0, 255,  0,  0,  0,  0, false},  //13 Blade Runner Flip Side    -- TODO this tune was shortened!
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

// 

int eyeCoords[93][2] = {
  { 55,107}, { 64,106}, { 75,104}, { 84, 98}, { 92, 93}, { 98, 85}, {103, 76}, {107, 66}, {108, 56}, {107, 45},
  {103, 35}, { 98, 27}, { 92, 18}, { 84, 12}, { 75,  7}, { 64,  3}, { 55,  2}, { 45,  3}, { 35,  7}, { 26, 12},
  { 18, 18}, { 12, 27}, {  7, 35}, {  4, 45}, {  3, 56}, {  4, 66}, {  7, 76}, { 12, 85}, { 18, 93}, { 26, 98},
  { 35,104}, { 45,106}, { 55, 98}, { 66, 97}, { 76, 92}, { 84, 85}, { 91, 77}, { 96, 66}, { 97, 55}, { 96, 44},
  { 91, 35}, { 84, 26}, { 76, 18}, { 66, 14}, { 55, 13}, { 45, 14}, { 34, 18}, { 26, 26}, { 18, 35}, { 14, 44},
  { 12, 55}, { 14, 66}, { 18, 77}, { 25, 85}, { 34, 92}, { 44, 97}, { 55, 88}, { 67, 86}, { 77, 78}, { 85, 68},
  { 87, 55}, { 85, 43}, { 77, 33}, { 67, 25}, { 55, 23}, { 43, 25}, { 32, 33}, { 25, 43}, { 23, 55}, { 25, 68},
  { 32, 78}, { 43, 86}, { 55, 78}, { 66, 75}, { 74, 67}, { 77, 55}, { 75, 44}, { 67, 36}, { 55, 33}, { 44, 36},
  { 36, 44}, { 33, 55}, { 35, 67}, { 43, 75}, { 55, 68}, { 64, 64}, { 67, 55}, { 64, 47}, { 55, 43}, { 46, 47},
  { 43, 55}, { 46, 64}, { 55, 55} };
int armCoords[24][2] = {
  { 0,  6}, { 0, 13}, { 0, 19}, { 0, 25}, { 0, 31}, { 0, 38}, { 0, 44}, { 0, 50}, { 0, 57}, { 0, 62}, 
  { 0, 69}, { 0, 75}, { 0, 82}, { 0, 88}, { 0, 94}, { 0,100}, { 0,106}, { 0,113}, { 0,119}, { 0,125}, 
  { 0,131}, { 0,138}, { 0,144}, { 0,150} };
int horizCoords[26][2] = {
  {  7, 0}, { 13, 0}, { 20, 0}, { 27, 0}, { 33, 0}, { 40, 0}, { 47, 0}, { 53, 0}, { 60, 0}, { 67, 0}, 
  { 73, 0}, { 80, 0}, { 87, 0}, { 93, 0}, {100, 0}, {107, 0}, {113, 0}, {120, 0}, {127, 0}, {133, 0}, 
  {140, 0}, {147, 0}, {153, 0}, {160, 0}, {167, 0}, {173, 0} };
int tapeCoords[34][2] = {
  { 00,  7}, { 00, 13}, { 00, 20}, { 00, 27}, { 00, 33}, { 00, 40}, { 00, 47}, { 00, 53}, { 00, 60}, {  4, 60}, 
  { 10, 60}, { 17, 60}, { 24, 60}, { 30, 60}, { 36, 60}, { 44, 60}, { 50, 60}, { 57, 60}, { 64, 60}, { 70, 60}, 
  { 77, 60}, { 84, 60}, { 90, 60}, { 97, 60}, {104, 60}, {104, 60}, {104, 53}, {104, 47}, {104, 40}, {104, 33}, 
  {104, 27}, {104, 20}, {104, 13}, {104,  7} };
int tubeCoords[90][2] = {
  {100,197}, {108,197}, {113,196}, {122,194}, {129,191}, {137,188}, {143,186}, {150,181}, {157,178}, {162,172}, 
  {167,168}, {172,163}, {177,158}, {183,152}, {187,145}, {190,138}, {193,131}, {195,124}, {197,118}, {198,111}, 
  {198,105}, {198, 98}, {197, 92}, {196, 84}, {195, 78}, {194, 72}, {193, 65}, {190, 59}, {188, 52}, {183, 46}, 
  {179, 40}, {175, 34}, {170, 29}, {166, 26}, {161, 22}, {156, 18}, {149, 16}, {143, 11}, {138,  8}, {134,  5}, 
  {128,  4}, {122,  3}, {116,  2}, {112,  2}, {105,  1}, {100,  0}, { 93,  1}, { 87,  2}, { 79,  4}, { 71,  8}, 
  { 63, 10}, { 58, 12}, { 50, 16}, { 44, 20}, { 38, 23}, { 33, 28}, { 29, 32}, { 24, 36}, { 20, 42}, { 16, 48}, 
  { 12, 74}, {  8, 59}, {  5, 67}, {  3, 74}, {  2, 82}, {  2, 88}, {  1, 94}, {  0,100}, {  1,108}, {  2,114}, 
  {  3,119}, {  5,127}, {  6,134}, {  8,140}, { 12,146}, { 15,154}, { 19,158}, { 23,162}, { 27,166}, { 30,170}, 
  { 37,175}, { 42,179}, { 48,182}, { 55,185}, { 62,189}, { 69,193}, { 77,194}, { 83,196}, { 88,197}, { 95,198} };
int binCoords[203][2] = {  // 3               // 5                             // 8                  // 0
  {230,460}, {238,459}, {245,459}, {251,458}, {258,458}, {266,458}, {272,457}, {277,455}, {285,453}, {292,450}, 
  {299,447}, {305,444}, {324,439}, {329,436}, {335,432}, {340,430}, {347,425}, {352,421}, {357,416}, {360,410}, // 20
  {365,406}, {370,402}, {375,400}, {380,394}, {385,386}, {390,382}, {394,378}, {398,373}, {402,396}, {406,363}, 
  {410,359}, {414,352}, {418,348}, {421,342}, {424,336}, {425,331}, {429,322}, {433,317}, {435,311}, {438,305}, // 40
  {440,296}, {442,288}, {443,283}, {444,277}, {445,269}, {446,261}, {448,253}, {448,248}, {449,239}, {449,230}, 
  {450,225}, {449,219}, {448,212}, {447,205}, {446,198}, {446,191}, {445,188}, {443,178}, {440,170}, {438,166}, // 60
  {436,161}, {434,155}, {432,147}, {429,140}, {426,135}, {424,130}, {420,122}, {416,114}, {413,108}, {409,103}, 
  {405,100}, {402, 94}, {398, 87}, {394, 82}, {390, 77}, {385, 73}, {380, 69}, {375, 63}, {368, 56}, {364, 51}, // 80
  {357, 48}, {352, 45}, {346, 42}, {341, 39}, {335, 34}, {331, 31}, {325, 28}, {319, 25}, {313, 22}, {306, 20}, 
  {300, 18}, {294, 16}, {285, 14}, {279, 13}, {273, 12}, {266, 10}, {259,  9}, {251,  7}, {245,  5}, {238,  5}, // 100
  {232,  5}, {225,  6}, {221,  7}, {214,  8}, {208,  9}, {200, 10}, {192, 12}, {184, 13}, {174, 13}, {168, 14}, 
  {162, 16}, {154, 18}, {148, 22}, {141, 25}, {137, 27}, {132, 29}, {125, 32}, {118, 36}, {112, 39}, {106, 42}, // 120
  {101, 46}, { 97, 48}, { 91, 53}, { 85, 59}, { 80, 65}, { 75, 70}, { 71, 75}, { 65, 78}, { 60, 85}, { 56, 92}, 
  { 52, 98}, { 48,101}, { 45,107}, { 40,112}, { 36,119}, { 32,127}, { 28,134}, { 26,138}, { 24,144}, { 21,152}, // 140
  { 18,158}, { 17,164}, { 15,171}, { 14,178}, { 13,186}, { 12,192}, { 11,198}, { 10,206}, {  9,214}, {  9,221}, 
  {  8,228}, {  9,235}, {  9,244}, {  9,249}, { 10,254}, { 11,260}, { 12,268}, { 13,275}, { 15,282}, { 16,288}, // 160
  { 17,292}, { 18,302}, { 21,308}, { 22,312}, { 25,318}, { 28,322}, { 31,330}, { 34,336}, { 36,342}, { 39,346}, 
  { 43,352}, { 45,360}, { 49,366}, { 53,370}, { 60,376}, { 65,379}, { 68,386}, { 71,392}, { 78,399}, { 82,402}, // 180
  { 88,405}, { 93,408}, { 98,412}, {103,418}, {108,423}, {112,427}, {119,430}, {125,433}, {132,436}, {137,439}, 
  {144,440}, {151,442}, {156,445}, {162,447}, {168,450}, {175,452}, {182,454}, {188,456}, {195,457}, {204,458}, // 200
  {212,459}, {217,460}, {222,460} };
int bigHeartCoords[175][2] = {      // 3        // 4                             // 7                  // 9
  { 48,267}, { 45,273}, { 42,280}, { 37,287}, { 33,295}, { 28,303}, { 26,309}, { 23,317}, { 20,325}, { 17,333}, 
  { 15,338}, { 14,344}, { 12,352}, { 10,359}, {  9,365}, {  8,372}, {  7,378}, {  6,385}, {  8,392}, {  9,401}, 
  { 10,409}, { 12,416}, { 15,423}, { 18,430}, { 21,438}, { 23,443}, { 27,451}, { 30,456}, { 34,463}, { 40,469}, 
  { 35,473}, { 52,478}, { 57,482}, { 63,484}, { 68,487}, { 74,489}, { 80,493}, { 86,495}, { 94,497}, {100,498}, 
  {107,499}, {115,499}, {120,500}, {125,500}, {132,500}, {138,499}, {144,499}, {153,499}, {158,498}, {165,497}, // 49
  {172,497}, {178,496}, {185,495}, {192,493}, {200,491}, {206,489}, {212,487}, {218,485}, {225,482}, {232,479}, 
  {238,475}, {244,472}, {252,470}, {258,468}, {265,466}, {270,463}, {276,459}, {282,456}, {287,454}, {292,450}, // 69
  {298,455}, {303,458}, {309,462}, {315,466}, {322,470}, {328,473}, {334,476}, {340,479}, {348,481}, {354,484},
  {361,485}, {367,488}, {373,490}, {379,491}, {386,493}, {393,494}, {401,496}, {408,497}, {414,498}, {421,499}, // 89
  {428,499}, {434,497}, {441,495}, {448,492}, {454,490}, {462,488}, {468,487}, {475,484}, {482,481}, {488,478},
  {494,472}, {500,469}, {506,467}, {512,466}, {518,463}, {522,460}, {529,456}, {535,452}, {540,448}, {547,442}, // 109
  {550,438}, {555,432}, {560,428}, {563,420}, {566,412}, {568,406}, {570,401}, {572,395}, {573,388}, {574,380},
  {574,376}, {573,369}, {572,363}, {572,358}, {571,352}, {569,345}, {566,338}, {564,328}, {562,322}, {559,315}, // 129
  {556,308}, {553,300}, {551,292}, {549,287}, {546,278}, {545,273}, {542,268}, {539,261}, {536,254}, {533,248},
  {531,243}, {528,238}, {526,231}, {523,225}, {521,220}, {490,230}, {490,230}, {385, 63}, {380, 58}, {375, 52}, // 149
  {370, 44}, {364, 43}, {358, 39}, {352, 33}, {346, 30}, {341, 25}, {334, 21}, {329, 17}, {323, 12}, {318,  9},
  {309,  6}, {300,  8}, {294, 12}, {289, 14}, {283, 18}, {278, 22}, {272, 26}, {268, 30}, {263, 35}, {258, 40}, // 169
  {251, 45}, {246, 49}, {239, 54}, {232, 60}, {228, 65} };
int smHeartCoords[85][2] = {        // 3        // 4                             // 7                  // 9
  { 00, 00}, { 00, 00}, { 00, 00}, { 24,  6}, { 22, 12}, { 19, 18}, { 17, 26}, { 14, 32}, { 11, 38}, {  9, 44}, 
  {  8, 49}, {  7, 56}, {  4, 62}, {  3, 68}, {  3, 76}, {  4, 85}, {  5, 92}, {  5, 98}, {  6,104}, {  9,112}, 
  { 12,120}, { 14,125}, { 18,128}, { 20,134}, { 24,139}, { 29,144}, { 36,148}, { 40,153}, { 48,158}, { 57,162}, 
  { 61,163}, { 67,164}, { 73,165}, { 80,165}, { 87,164}, { 95,163}, {102,162}, {109,159}, {115,155}, {119,152}, 
  {125,150}, {132,147}, {139,143}, {145,140}, {150,138}, {145,140}, {164,144}, {170,148}, {176,152}, {182,158}, 
  {188,160}, {194,163}, {203,165}, {209,168}, {217,169}, {224,169}, {232,168}, {238,167}, {246,164}, {252,162}, 
  {258,160}, {265,153}, {270,148}, {275,145}, {282,140}, {287,133}, {290,126}, {292,118}, {294,112}, {296,106}, 
  {297, 98}, {298, 92}, {298, 85}, {295, 78}, {294, 70}, {294, 65}, {293, 60}, {292, 54}, {290, 48}, {288, 42}, 
  {286, 37}, {282, 28}, {278, 21}, {273, 15}, {269,  9} };
int portRCoords[19][2] = {          // 3        // 4                             // 7                  // 9
  { 12, 80}, { 22, 90}, { 38, 96}, { 54, 96}, { 70, 95}, { 82, 87}, { 92, 75}, { 98, 62}, { 98, 48}, { 95, 32}, 
  { 88, 20}, { 75, 10}, { 60,  3}, { 40,  3}, { 26,  8}, { 12, 18}, {  5, 32}, {  2, 50}, {  5, 65} };
int portLCoords[19][2] = {          // 3        // 4                             // 7                  // 9
  { 82, 87}, { 70, 95}, { 54, 96}, { 38, 96}, { 22, 90}, { 12, 80}, {  5, 65}, {  2, 50}, {  5, 32}, { 12, 18}, 
  { 26,  8}, { 40,  3}, { 60,  3}, { 75, 10}, { 88, 20}, { 95, 32}, { 98, 48}, { 98, 62}, { 92, 75} };

  
int ledSections[20] = {
  0,     // 0  bottom ring *
  203,   // 1  big heart
  378,   // 2  small heart
  463,   // 3 underarm left
  482,   // 4 overarm left
  506,   // 5  eye left 
  599,   // 6  eye right
  692,   // 7  mouth
  710,   // 8  tape
  744,   // 9  tuner *
  770,   // 10 indiciator *
  774,   // 11 underarm right
  797,   // 12 overarm right
  821,   // 13 tube bottomright *
  911,   // 14 tube bottomleft *
  1001,  // 15 tube topleft *
  1090,  // 16 tube topright * starred sections are shifted and / or reversed
  1179,  // 17 port left
  1302,  // 18 port right
  1441};

int ledPosOffset[19][2] = {
  {  70, 90},    // 00 bottomRing
  {  0, 945},    // 01 bigHeart
  {  150, 1224},    // 02 smallHeart
  {  612, 1400},    // 03 underarm left
  {  612, 1090},    // 04 overarm left
  {  384, 1550},    // 05 eyeLeft 
  {  110, 1550},    // 06 rightEye
  {  246, 1536},    // 07 mouth
  {  250, 1600},    // 08 tape
  {  239, 1710},    // 09 tuner 
  {  180, 1714},    // 10 indicator
  {  1, 1400},    // 11 underArm right
  {  1, 1090},    // 12 overArm right
  {  315, 800},    // 13 tubeBottomright
  {  80, 800},    // 14 tubeBottomleft
  {  80, 1020},    // 15 tubeTopleft
  {  315, 1020},    // 16 tubeTopright
  {  50, 555},    // 17 port left
  {  490, 555},    // 18 port right
};


  
