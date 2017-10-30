int lastPosL = 0;
int lastPosR = 0;

void doArmRelays() {

  if (ps2.readButton(PS2_RIGHT_1)==0) {
    if (lastPosL==2) {
      digitalWrite(28,HIGH);
      digitalWrite(26,HIGH);
      delay(20);
    }
    digitalWrite(28,LOW);
    lastPosL=1;
  } else if (ps2.readButton(PS2_RIGHT_2)==0) {
    if (lastPosL==1) {
      digitalWrite(28,HIGH);
      digitalWrite(26,HIGH);
      delay(20);
    }
    digitalWrite(26,LOW);
    lastPosL=2;
  } else {
    digitalWrite(28,HIGH);
    digitalWrite(26,HIGH);
    lastPosL=3;
  }

  if (ps2.readButton(PS2_LEFT_1)==0) {
    if (lastPosR==2) {
      digitalWrite(24,HIGH);
      digitalWrite(22,HIGH);
      delay(20);
    }
    digitalWrite(24,LOW);
    lastPosR=1;
  } else if (ps2.readButton(PS2_LEFT_2)==0) {
    if (lastPosR==1) {
      digitalWrite(24,HIGH);
      digitalWrite(22,HIGH);
      delay(20);
    }
    digitalWrite(22,LOW);
    lastPosR=2;
  } else {
    digitalWrite(24,HIGH);
    digitalWrite(22,HIGH);
    lastPosR=3;
  }
}

