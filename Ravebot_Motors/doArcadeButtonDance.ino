int thisArcadeBtnDance = 0;
int numArcardButtonDances = 6;

void doArcadeButtonDance(int beatNumber) {

  // TODO - TEST CODE!!!!!!"!
  thisArcadeBtnDance = 6;
  
  for (int btnNum = 0; btnNum < 14; btnNum++) {
    switch (thisArcadeBtnDance) {
       case 0: setArcadeButton(btnNum, arcadeButtonDance0[beatNumber][btnNum]); break;
       case 1: setArcadeButton(btnNum, arcadeButtonDance1[beatNumber][btnNum]); break;
       case 2: setArcadeButton(btnNum, arcadeButtonDance2[beatNumber][btnNum]); break;
       case 3: setArcadeButton(btnNum, arcadeButtonDance3[beatNumber][btnNum]); break;
       case 4: setArcadeButton(btnNum, arcadeButtonDance4[beatNumber][btnNum]); break;
       case 5: setArcadeButton(btnNum, arcadeButtonDance5[beatNumber][btnNum]); break;
       case 6: setArcadeButton(btnNum, arcadeButtonDance6[beatNumber][btnNum]); break;
       case 7: setArcadeButton(btnNum, arcadeButtonDance7[beatNumber][btnNum]); break;
    }
  }
}

void changeArcadeButtonDance() {
  thisArcadeBtnDance = random(numArcardButtonDances);
}

void setArcadeButton(int buttonToSet, int intensity) {
  int finalIntensity = intensity*16;
  if (finalIntensity > 4095)
    finalIntensity = 4095;

  switch (buttonToSet) {
     case 0:
       ledPwm.setPWM(7, 0, finalIntensity);
       return;
     case 1:
       ledPwm.setPWM(6, 0, finalIntensity);
       return;
     case 2:
       ledPwm.setPWM(5, 0, finalIntensity);
       return;
     case 3:
       ledPwm.setPWM(4, 0, finalIntensity);
       return;
     case 4:
       ledPwm.setPWM(3, 0, finalIntensity);
       return;
     case 5:
       ledPwm.setPWM(2, 0, finalIntensity);
       return;
     case 6:
       ledPwm.setPWM(1, 0, finalIntensity);
       return;
     case 7:
       ledPwm.setPWM(0, 0, finalIntensity);
       return;
     case 8:
       ledPwm.setPWM(12, 0, finalIntensity);
       return;
     case 9:
       ledPwm.setPWM(13, 0, finalIntensity);
       return;
     case 10:
       ledPwm.setPWM(11, 0, finalIntensity);
       return;
     case 11:
       ledPwm.setPWM(10, 0, finalIntensity);
       return;
     case 12:
       ledPwm.setPWM(8, 0, finalIntensity);
       return;
     case 13:
       ledPwm.setPWM(9, 0, finalIntensity);
       return;
     default: return;
  }
}
