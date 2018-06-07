void doKeypad()
{
  char key = keypad.getKey();  
  if (key != NO_KEY)
  {
    keypadPressed(key);
  }
}

void keypadPressed(char key) {
  if (key == '#')
    sendNumber();
  else if (key == '*')
    sendNumber();
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
    
  showNumber();  
}

void showNumber() {

  matrix.displaybuffer[0] = 0;
  matrix.displaybuffer[1] = 0;
  matrix.displaybuffer[3] = 0;

  if (currentSegmentNum > 99)
  {
    matrix.displaybuffer[3] = get7SegmentNumber(currentSegmentNum/100);
    matrix.displaybuffer[1] = get7SegmentNumber((currentSegmentNum%100)/10);
    matrix.displaybuffer[0] = get7SegmentNumber(currentSegmentNum%10);
  }
  else if (currentSegmentNum > 9)
  {
    matrix.displaybuffer[1] = get7SegmentNumber((currentSegmentNum%100)/10);
    matrix.displaybuffer[0] = get7SegmentNumber(currentSegmentNum%10);
  }
  else
  {
    matrix.displaybuffer[0] = get7SegmentNumber(currentSegmentNum); // currentSegmentNum == 0 ? 0 : get7SegmentNumber(currentSegmentNum);
  }

  matrix.writeDisplay();
}

int get7SegmentNumber(int actualNumber) {
  switch (actualNumber) {
     case 0: return 63;
     case 1: return 48;
     case 2: return 91;
     case 3: return 121;
     case 4: return 116;
     case 5: return 109;
     case 6: return 111;
     case 7: return 60;
     case 8: return 127;
     case 9: return 125;
     default: return 0;
  }  
}

void changeNumber(int newNumber) {
  currentSegmentNum = ((currentSegmentNum % 100) * 10) + newNumber;

  if (testMode) {
    Serial.print("currentSegmentNum:");
    Serial.println(currentSegmentNum);
    Serial.print(" %");
    Serial.println(((currentSegmentNum % 100) * 10) + newNumber);
  }
}


void resetNumber() {
  if (testMode)
    Serial.println("RESET");

  currentSegmentNum=0;
}

void sendNumber() {
  
  sendSerialToLights(4, currentSegmentNum);

  resetNumber();
}



/* use this to find new 7 segments, assign this function a key and comment showNumber call.

int sevenSegCount = 0;
void sevenSegTest() {
  matrix.displaybuffer[0] = get7SegmentNumber(sevenSegCount);

  matrix.writeDisplay();
  sevenSegCount++;
}
void sevenSegTest2(int seg) {
  matrix.displaybuffer[0] = get7SegmentNumber(seg);
  matrix.writeDisplay();
  sevenSegCount++;
}
*/



