/* KEYPAD SET UP  */

#include<Arduino.h>
#include<Keypad.h>
#include<Wire.h>
#include<FastLED.h>

// Keypad setup
char keys[4][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
byte rowPins[4] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[3] = {2, 3, 4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 3);

unsigned long timey;
int ticky=0;

unsigned long beatTimes[10] = {0,0,0,0,0,0,0,0,0,0};
int fakeBeatLengh = 240;

// Set by midi in to be 1-16 with beat.
short sixteenth = 0;

int mainVolume = 80; // 127 actual max but we won't exceed 100.
int currentBar = 0;
int currentGenre = 0;
int currentTrack = 0;
int dropCountdown = 0;

bool robotTalking = false;
unsigned long robotTalkingOnTime;

const int numLeds = 671;
const int numLedsAdj = (numLeds * 4) / 3;
CRGB rgbwLeds[numLedsAdj];

// NEW MIXING VARS
int nextTrack = 0;
int nextGenre = 0;
int nextMixDuration16 = 0;
int currentBpm = 0;
bool stayWithinGenre = false;
bool inTheMix = false;
bool deckASelected = true;
int currentMixerPosition = 0;

void setup() {
  delay(500);

  // Talk to Ableton via midi over USB, or debug.
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

void loop()
{
  timey = millis();

  doKeypad();

  //listenToAbleton();

  //receiveFromMega();

}

void doKeypad()
{
  char key = keypad.getKey();  
  if (key != NO_KEY)
  {
    keypadPressed(key);
  }
}


int uptopos = 0;
int currChannel = 0;
int currTrackNum = 0;
int currValue = 0;

void resetNumber() {
  int uptopos = 0;
  int currChannel = 0;
  int currValue = 0;
  int currTrackNum = 0;
}

// TODO - make it so the * button just adds one to the track and sends that stragit away x Nice x

void keypadPressed(char key) {
  if (key == '#')
    resetNumber();
  else if (key == '*')
    sendNextNumber();
  else if (key == '1')
    changeNumber(1);
  else if (key == '2')
    changeNumber(2);
  else if (key == '3')
    changeNumber(3);
  else if (key == '4')
    changeNumber(4);
  else if (key == '5')
    changeNumber(5);
  else if (key == '6')
    changeNumber(6);
  else if (key == '7')
    changeNumber(7);
  else if (key == '8')
    changeNumber(8);
  else if (key == '9')
    changeNumber(9);
  else if (key == '0')
    changeNumber(0);    
}

void sendNextNumber() {
  currTrackNum = currTrackNum+1;
  playAbletonTrack(currChannel, currTrackNum);
  uptopos=0;
}

void changeNumber(int inNum) {
  Serial.print("nu8mber!");
  Serial.println(inNum);
  if (uptopos == 0) {
    currChannel = (10 * inNum);
    uptopos=1;
  } else if (uptopos == 1) {
    currChannel = currChannel + inNum;
    uptopos=2;
  } else if (uptopos == 2) {
    currTrackNum =  (100 * inNum);
    uptopos=3;
  } else if (uptopos == 3) {
    currTrackNum = currTrackNum + (10 * inNum);
    uptopos=4;
  } else if (uptopos == 4) {
    currTrackNum = currTrackNum+ inNum;
    playAbletonTrack(currChannel, currTrackNum);
    uptopos=0;
  }
}

void changeNumberFull(int inNum) {
  if (uptopos == 0) {
    currChannel = (100 * inNum);
    uptopos=1;
  } else if (uptopos == 1) {
    currChannel = currChannel + (10 * inNum);
    uptopos=2;
  } else if (uptopos == 2) {
    currChannel =  currChannel + inNum;
    uptopos=3;
  } else if (uptopos == 3) {
    currTrackNum = 100 * inNum;
    uptopos=4;
  } else if (uptopos == 4) {
    currTrackNum = currTrackNum + (10 * inNum);
    uptopos=5;
  } else if (uptopos == 5) {
    currTrackNum = currTrackNum + inNum;
    uptopos=6;
  } else if (uptopos == 6) {
    currValue = 100 * inNum;
    uptopos=7;
  } else if (uptopos == 7) {
    currValue = currValue + (10 * inNum);
    uptopos=8;
  } else if (uptopos == 8) {
    currValue = currValue + inNum;
    sendMidi(currChannel, currTrackNum, currValue);
    uptopos=0;
  }
}

