/* _____                 _           _              __  __       _
  |  __ \               | |         | |            |  \/  |     | |
  | |__) |__ ___   _____| |__   ___ | |_   ______  | \  / | ___ | |_ ___  _ __ ___
  |  _  // _` \ \ / / _ \ '_ \ / _ \| __| |______| | |\/| |/ _ \| __/ _ \| '__/ __|
  | | \ \ (_| |\ V /  __/ |_) | (_) | |_           | |  | | (_) | || (_) | |  \__ \
  |_|  \_\__,_| \_/ \___|_.__/ \___/ \__|          |_|  |_|\___/ \__\___/|_|  |___/            */

#include<Arduino.h>
#include<Keypad.h>
#include<Wire.h>
#include<Adafruit_LEDBackpack.h>
#include<Adafruit_PWMServoDriver.h>
#include<SoftwareSerial.h>
#include<SabertoothSimplified.h>
#include<Cytron_PS2Shield.h>
#include<avr/wdt.h>

/*
 * Arduino Mega to do listy
 * 
 * Hmmmm.
 * implement modes, have manual, automatic and off.
 * Learn to dance!
 * 
 */

const bool testMode = false;

bool robotSwitchedOn = false;
bool robotManualMode = true;

unsigned long timey;
unsigned long nextAnalogRead;

int currentBeat;
int currentBar;

int ledIntensity = 10;
int currentSegmentNum;

// switches in arcade buttons
int switchPins[14] = { 27, 29, 31, 33, 35, 37, 39, 41, 45, 43, 53, 51, 49, 47 };

// Big main motor driver
SoftwareSerial SabretoothSerial(NOT_A_PIN, 9); // RX on no pin (unused), TX on pin 9 (to S1).
SoftwareSerial SabretoothSerial2(NOT_A_PIN, A9); // RX on no pin (unused), TX on pin 9 (to S1).
// NOTE TO JR - you just wired the other sabertooth to pin 52
SabertoothSimplified ST1(SabretoothSerial); // Use SoftwareSerial as the serial port.
SabertoothSimplified ST2(SabretoothSerial2); // Use SoftwareSerial as the serial port.

Cytron_PS2Shield ps2(10, 11);

// 7 segmehnt led setup
Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();

// PCA9685 Led driver for arcade buttons
Adafruit_PWMServoDriver ledPwm = Adafruit_PWMServoDriver(0x40);

// PCA9685 Servo driver for arms, you can't do much if you got no arms.
Adafruit_PWMServoDriver servoPwm = Adafruit_PWMServoDriver(0x41);

// Keypad setup
char keys[4][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
byte rowPins[4] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[3] = {2, 3, 4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 3);

void setup() {
  delay(500);
  wdt_enable(WDTO_2S);

  if (testMode)
    Serial.begin(9600);

  // Talk to the other arduino
  Serial1.begin(28800);  // tx for sending tx2 port 16
  Serial3.begin(28800);  // rx for receiving rx1 - port 19

  // make random more random?!
  randomSeed(analogRead(0));

  ps2.begin(57600);

  // The relays which control the arms - todo - there are no relays controlling the arms any more
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  digitalWrite(22, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(28, HIGH);

  SabretoothSerial.begin(9600); // Set the same as the baud pins on the sabretooth.
  SabretoothSerial2.begin(9600); // Set the same as the baud pins on the sabretooth.

  // The jukebox 7segment
  matrix.begin(0x71);  // pass in the address
  matrix.setBrightness(255);

  // servo
  servoPwm.begin();
  servoPwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  initServos();

  ledPwm.begin();
  ledPwm.setPWMFreq(1600);  // This is the maximum PWM frequency

  // Arm cutoff
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  // led intensity
  pinMode(A8, INPUT_PULLUP);  //todo - change this

  // Arcade switch
  pinMode(switchPins[0], INPUT_PULLUP);
  pinMode(switchPins[1], INPUT_PULLUP);
  pinMode(switchPins[2], INPUT_PULLUP);
  pinMode(switchPins[3], INPUT_PULLUP);
  pinMode(switchPins[4], INPUT_PULLUP);
  pinMode(switchPins[5], INPUT_PULLUP);
  pinMode(switchPins[6], INPUT_PULLUP);
  pinMode(switchPins[7], INPUT_PULLUP);
  pinMode(switchPins[8], INPUT_PULLUP);
  pinMode(switchPins[9], INPUT_PULLUP);
  pinMode(switchPins[10], INPUT_PULLUP);
  pinMode(switchPins[11], INPUT_PULLUP);
  pinMode(switchPins[12], INPUT_PULLUP);
  pinMode(switchPins[13], INPUT_PULLUP);

  timey = millis();

  currentSegmentNum=0;

  nextAnalogRead = timey+500;
}

void loop()
{
  wdt_reset(); // this checks if the board crashed and resets
  
  timey = millis();

  checkForOnOffChange();
  checkForManualAutoChange();
  talkToLights();

  if (robotSwitchedOn) {
    if (robotManualMode) {
      doServos();
      doMyArms();
    } else {
      if (currentBar != 0)
        doDancing();
    }
    doKeypad();
    doArcadeBtn();
  }
  doMyWheels();  
}

bool startButtonPressed = false;
void checkForOnOffChange() {
  if (!startButtonPressed && (ps2.readButton(PS2_START) == 0)) {
    startButtonPressed = true;
    robotSwitchedOn = !robotSwitchedOn;
    int numToSend = 9 + (robotSwitchedOn ? 0 : 1);
    sendSerialToLights(1, numToSend);
    if (!robotSwitchedOn) {
      switchOffArcadeButtons();
      switchOffDisplay();
    } else {
      showNumber();
    }
  } else if (ps2.readButton(PS2_START) == 1) {
    startButtonPressed = false;
  }
}

bool selectButtonPressed = false;
void checkForManualAutoChange() {
  if (!selectButtonPressed && (ps2.readButton(PS2_SELECT) == 0)) {
    selectButtonPressed = true;
    robotManualMode = !robotManualMode;
    int numToSend = 11 + (robotManualMode ? 0 : 1);
    sendSerialToLights(1, numToSend);
  } else if (ps2.readButton(PS2_SELECT) == 1) {
    selectButtonPressed = false;
  }
}



struct servoInfo {
  int minPosition;
  int maxPosition;
  int servoSpeed;
  int servoCenter;
  int servoPos;
  int leftDancePos;
  int rightDancePos;
  unsigned long servoMoveTime;
  servoInfo(int aMinPosition, int aMaxPosition, int aServoSpeed, int aServoCenter, int aServoPos, int aLeftDancePos, int aRightDancePos, unsigned long aServoMoveTime) :
    minPosition(aMinPosition), maxPosition(aMaxPosition), servoSpeed(aServoSpeed), servoCenter(aServoCenter), servoPos(aServoPos), leftDancePos(aLeftDancePos), rightDancePos(aRightDancePos), servoMoveTime(aServoMoveTime) {
  }
};

servoInfo servos[13] = {
  // 20 kg red servos - 150-500 / 325 mid
  { 130, 530, 3, 330, 330, 0, 0, 0 }, // 0 - Head - shake
  { 360, 485, 2, 450, 450, 0, 0, 0 }, // 1 - Head - Nod
  { 180, 330, 5, 240, 240, 0, 0, 0 }, // 2 - L claw
  { 140, 560, 3, 350, 350, 0, 0, 0 }, // 3 - l wrist ud
  { 140, 560, 4, 350, 350, 0, 0, 0 }, // 4 - R elbow
  { 140, 560, 3, 350, 350, 300, 400, 0 }, // 5 - R wrist lr
  { 290, 445, 5, 350, 350, 0, 0, 0 }, // 6 - R claw increase to grab
  { 140, 560, 3, 350, 350, 0, 0, 0 }, // 7 - r wrist ud
  { 140, 560, 4, 350, 350, 0, 0, 0 }, // 8 - l elbow
  { 140, 560, 3, 350, 350, 300, 400, 0 }, // 9 - l wrist lr
  { 202, 330, 2, 330, 330, 0, 0, 0 }, // 10 - l new nod
  { 375, 455, 1, 400, 400, 0, 0, 0 }, // 11 - l new tilt
  { 200, 500, 3, 350, 350, 0, 0, 0 }  // 12 - l new shake
  
};

