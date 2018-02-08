int currentNum = 0;

void doJukebox()
{
  char key = keypad.getKey();  
  if (key != NO_KEY)
  {
    keypadPressed(key);
  }
}

void keypadPressed(char key) {
  if (key == '#')
    changeNumber(0); // resetNumber();
  else if (key == '*')
    changeNumber(0); // sendNumber();
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
} */

void showNumber() {
  /* 
  //matrix.displaybuffer[0] = 0;
  //matrix.displaybuffer[1] = 0;
  //matrix.displaybuffer[3] = 0;
  
  // int finalNumber = getFinalNumber();

  if (finalNumber > 99)
  {
    matrix.displaybuffer[3] = get7SegmentNumber(num0);
    matrix.displaybuffer[1] = get7SegmentNumber(num1);
    matrix.displaybuffer[0] = get7SegmentNumber(num2);
  }
  else if (finalNumber > 9)
  {
    matrix.displaybuffer[1] = get7SegmentNumber(num1);
    matrix.displaybuffer[0] = get7SegmentNumber(num2);
  }
  else
  {
    matrix.displaybuffer[0] = get7SegmentNumber(num2); //num2 == 0 ? 0 : get7SegmentNumber(num2);
  }  */
  
  matrix.displaybuffer[3] = get7SegmentNumber(currentNum/100);
  //matrix.displaybuffer[1] = get7SegmentNumber((currentNum%100)/10);
  //matrix.displaybuffer[0] = get7SegmentNumber(currentNum%110);
  
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
  if (currentNum > 100)
    currentNum = ((currentNum % 100) * 10) + newNumber;
  else if (currentNum > 10)
    currentNum = (currentNum % 10) + newNumber;
  else 
    currentNum = newNumber;
}


/*
 * 

short getFinalNumber() {
  return num0 + (10 * num1) + (100 * num2);
}

void resetNumber() {
  num0 = 0;
  num1 = 0;
  num2 = 0;
}

void sendNumber() {
  short finalNumber = getFinalNumber();

  sendSerialToLights(4, finalNumber);

  resetNumber();
}

void setDisplay(int number) {
  char buf [3];
  sprintf (buf, "%03i", number);
  num0 = buf [0] - '0';
  num1 = buf [1] - '0';
  num2 = buf [2] - '0';

  showNumber(); 
}

 todo obv */

