/*  
2 - L claw
3 - l wrist ud
4 - R elbow
5 - R wrist lr
6 - R claw increase to grab
7 - r wrist ud
8 - l elbow
9 - l wrist lr

10 - l new nod
11 - l new tilt
12 - l new shake  */

int numDances = 2;
int currentDance = 1;

// The plan. Put this on lappy.
// comment everything but actual arms

/* Dance Move Functions - these are Called Every Cycle */

void doDancing() {
  if (currentDance == 1)
    dance1Movements();
   else if (currentDance == 2)
    dance2Movements();

  if (timey > servos[10].servoMoveTime) {
    nodHead(false);
  }
    
}

void changeDance() {
  int newDanceNumber;
  
  while (newDanceNumber != currentDance)
    newDanceNumber = random(1, numDances);
    
  currentDance = newDanceNumber;
  sendDanceNumberToLights(currentDance);
}

/* ******************************************* Dance Move Functions *************************** */

void moveLeftWristLR (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(9, doLeftMove, delayo);
}

void moveRightWristLR (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(5, doLeftMove, delayo);
}

void moveLeftWristUD (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(3, doLeftMove, delayo);
}

void moveRightWristUD (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(7, doLeftMove, delayo);
}

void moveLeftClaw (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(2, doLeftMove, delayo);
}

void moveRightClaw (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(6, doLeftMove, delayo);
}

void shakeHead (bool shakeLeft, int delayo) {
  int doLeftMove = shakeLeft ? -1 : 1;
  moveServoSoft(12, doLeftMove, delayo);
}

void tiltHead (bool tiltLeft, int delayo) {
  int doLeftMove = tiltLeft ? -1 : 1;
  moveServoSoft(11, doLeftMove, delayo);
  
}

/* ******************************************* Dance 1 Moves *********************************/
void dance1Movements() {
  if ((currentBar % 32) < 8) {
    dance1Moves1();
  } else if ((currentBar % 32) < 16) {
    dance1Moves2();
  } else if ((currentBar % 32) < 24) {
    dance1Moves1();
  } else {
    dance1Moves2();
  }
}

void dance1Moves1() {
  if ((currentBar % 4) == 0) {
    moveLeftWristLR(true, 32);
  } else if ((currentBar % 4) == 1) {
    moveLeftWristLR(false, 32);
  } else if ((currentBar % 4) == 2) {
    moveRightWristLR(true, 32);
  } else {
    moveRightWristLR(false, 32);
  }
}

void dance1Moves2() {
  if ((currentBar % 4) == 0) {
    shakeHead(true, 32);
  } else if ((currentBar % 4) == 1) {
    shakeHead(false, 32);
  } else if ((currentBar % 4) == 2) {
    shakeHead(true, 32);
  } else {
    shakeHead(false, 32);
  }
}
/* ******************************************* Dance 2 Moves *********************************/
void dance2Movements() {
  if ((currentBar % 32) < 8) {
    dance2Moves1();
  } else if ((currentBar % 32) < 16) {
    dance2Moves2();
  } else if ((currentBar % 32) < 24) {
    dance2Moves1();
  } else {
    dance2Moves2();
  }
}

void dance2Moves1() {
  if ((currentBar % 4) == 0) {
    moveLeftWristUD(true, 32);
  } else if ((currentBar % 4) == 1) {
    moveLeftWristUD(false, 32);
  } else if ((currentBar % 4) == 2) {
    moveRightWristUD(true, 32);
  } else {
    moveRightWristUD(false, 32);
  }
}
void dance2Moves2() {
  if ((currentBar % 4) == 0) {
    moveLeftClaw(true, 32);
  } else if ((currentBar % 4) == 1) {
    moveLeftClaw(false, 32);
  } else if ((currentBar % 4) == 2) {
    moveLeftClaw(true, 32);
  } else {
    moveLeftClaw(false, 32);
  }
}

/* ************* Dance BEAT moves called on the beat signal passed by the Due *************** */

void doBeatDanceMove() {
  if (robotManualMode || !robotSwitchedOn)
    return;

  if (currentDance == 1)
    doDance1BeatMoves();
  else if (currentDance == 2)
    doDance2BeatMoves();

  nodHead(true);
  servos[10].servoMoveTime = timey + 100;
}

/************************** Dance beat move functions **************************/

void leftWristLR (bool moveLeft) {
  if (moveLeft)
    moveServoToPos(9, servos[9].leftDancePos);
  else
    moveServoToPos(9, servos[9].rightDancePos);
}

void rightWristLR (bool moveLeft) {
  if (moveLeft)
    moveServoToPos(5, servos[5].leftDancePos);
  else
    moveServoToPos(5, servos[5].rightDancePos);
}

void leftWristUD (bool moveLeft) {
  if (moveLeft)
    moveServoToPos(3, servos[3].leftDancePos);
  else
    moveServoToPos(3, servos[3].rightDancePos);
}

void rightWristUD (bool moveLeft) {
  if (moveLeft)
    moveServoToPos(7, servos[7].leftDancePos);
  else
    moveServoToPos(7, servos[7].rightDancePos);
}

void leftClaw (bool moveLeft, int delayo) {
  if (moveLeft)
    moveServoToPos(2, servos[2].leftDancePos);
  else
    moveServoToPos(2, servos[2].rightDancePos);
}

void rightClaw (bool moveLeft, int delayo) {
  if (moveLeft)
    moveServoToPos(6, servos[6].leftDancePos);
  else
    moveServoToPos(6, servos[6].rightDancePos);
}

void beatShake (bool moveLeft, int delayo) {
  if (moveLeft)
    moveServoToPos(12, servos[12].leftDancePos);
  else
    moveServoToPos(12, servos[12].rightDancePos);
}


void nodHead(bool headUp) {
  if (headUp) {
    moveServoToPos(10, servos[10].rightDancePos);
  } else {
    moveServoToPos(10, servos[10].leftDancePos);
  }
}

void rightArmUpRightElbowUp() {
  moveServoToPos(4, rightArmUpRightElbowUpPos);
}
void rightArmUpRightElbowDown() {
  moveServoToPos(4, rightArmUpRightElbowDownPos);
}

void leftArmUpLeftElbowUp() {
  moveServoToPos(8, leftArmUpLeftElbowUpPos);
}
void leftArmUpLeftElbowDown() {
  moveServoToPos(8, leftArmUpLeftElbowDownPos);
}

void rightArmDownRightElbowUp() {
  moveServoToPos(4, rightArmDownRightElbowUpPos);
}
void rightArmDownRightElbowDown() {
  moveServoToPos(4, rightArmDownRightElbowDownPos);
}

void leftArmDownLeftElbowUp() {
  moveServoToPos(8, leftArmDownLeftElbowUpPos);
}
void leftArmDownLeftElbowDown() {
  moveServoToPos(8, leftArmDownLeftElbowDownPos);
}


/* ***************************** Dance 1 *********************************** */
void doDance1BeatMoves() {
  if ((currentBar % 32) < 8) {
    if (currentBar == 0 && currentBeat == 0) {
      // go to move 1 initial positions0
      moveLArm(10);
      moveRArm(10);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
    }
    dance1BeatMoves1();
  } else if ((currentBar % 32) < 16) {
    if ((currentBar % 32) == 8 && currentBeat == 0) {
      // go to move 2 initial positions
      moveLArm(-20);
      moveRArm(-20);
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
    }
    dance1BeatMoves2();
  } else if ((currentBar % 32) < 24) {
    if ((currentBar % 32) == 16 && currentBeat == 0) {
      // go to move 3 initial positions
      moveLArm(20);
      moveRArm(20);
      rightArmUpRightElbowDown();
      leftArmUpLeftElbowDown();
    }
    dance1BeatMoves1();
  } else {
    if ((currentBar % 32) == 24 && currentBeat == 0) {
      // go to move 4 initial positions
      moveLArm(-10);
      moveRArm(-10);
      rightArmDownRightElbowDown();
      leftArmDownLeftElbowDown();
    }
    dance1BeatMoves2();
  }
}

void dance1BeatMoves1() {
  if ((currentBeat % 8) == 0) {
    leftWristLR (true);
    rightWristLR (true);
  } else if ((currentBeat % 8) == 2) {
    leftWristUD (false);
    rightWristUD (false);
  } else if ((currentBeat % 8) == 4) {
    leftWristLR (true);
    rightWristLR (true);
  } else if ((currentBeat % 8) == 6) {
    leftWristUD(false);
    leftWristUD(false);
  }
}

void dance1BeatMoves2() {
  if ((currentBeat % 4) == 0) {
    leftClaw (false, 32);
    rightClaw (false, 32);
  } else if ((currentBeat % 4) == 2) {
    leftClaw (true, 32);
    rightClaw (true, 32);
  }
}

/* ***************************** Dance 2 *********************************** */
void doDance2BeatMoves() {
  if ((currentBar % 32) < 8) {
    if (currentBar == 0 && currentBeat == 0) {
      // go to move 1 initial positions0
      moveLArm(100);
      moveRArm(100);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
    }
    dance2BeatMoves1();
  } else if ((currentBar % 32) < 16) {
    if ((currentBar % 32) == 8 && currentBeat == 0) {
      // go to move 2 initial positions
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
    }
    dance2BeatMoves2();
  } else if ((currentBar % 32) < 24) {
    if ((currentBar % 32) == 16 && currentBeat == 0) {
      // go to move 3 initial positions
      rightArmUpRightElbowDown();
      leftArmUpLeftElbowDown();
    }
    dance2BeatMoves1();
  } else {
    if ((currentBar % 32) == 24 && currentBeat == 0) {
      // go to move 4 initial positions
      rightArmUpRightElbowDown();
      leftArmUpLeftElbowDown();
    }
    dance2BeatMoves2();
  }
}

void dance2BeatMoves1() {
  if ((currentBeat % 8) == 0) {
    leftWristLR (true);
    rightWristLR (false);
  } else if ((currentBeat % 8) == 2) {
    leftWristLR (false);
    rightWristLR (true);
  } else if ((currentBeat % 8) == 4) {
    leftWristLR (true);
    rightWristLR (false);
  } else if ((currentBeat % 8) == 6) {
    leftWristLR(false);
    rightWristLR(true);
  }
}

void dance2BeatMoves2() {
  if ((currentBeat % 4) == 0) {
    leftClaw (false, 32);
    rightClaw (false, 32);
  } else if ((currentBeat % 4) == 2) {
    leftClaw (true, 32);
    rightClaw (true, 32);
  }
}


