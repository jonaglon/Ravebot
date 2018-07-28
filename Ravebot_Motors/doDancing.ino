/* to do a dance:
 *  Go to dance start position - arms up / down. All dancing servos to init.
 */
int currentDance = 1;

// Called from the beat event passed by the Due
void doBeatDanceMove() {
  if (robotManualMode || !robotSwitchedOn)
    return;

  if (currentDance == 1)
    dance1BeatMove();
    
}

void doDancing() {
  if (currentDance == 1)
    dance1LoopMoves();
  // else if (currentDance == 2)
  //   dance2LoopMoves();
}

void dance1BeatMove() {
  if ((currentBeat % 8) == 0) {
    moveServoToPos(9, servos[9].leftDancePos);
    moveServoToPos(5, servos[5].rightDancePos);
  } else if ((currentBeat % 8) == 4) {
    moveServoToPos(9, servos[9].rightDancePos);
    moveServoToPos(5, servos[5].leftDancePos);
  }
  /* if ((currentBeat % 8) == 2) {
    moveServoToPos(3, servos[3].leftDancePos);
    //moveServoToPos(5, servos[5].rightDancePos);
  } else if ((currentBeat % 8) == 6) {
    moveServoToPos(3, servos[3].rightDancePos);
    //moveServoToPos(5, servos[5].leftDancePos);
  } */

}

void dance1LoopMoves() {
  if ((currentBar % 2) == 0) {
    moveServo(9, 1);
    moveServo(5, -1);
  } else { 
    moveServo(9, -1);
    moveServo(5, 1);
  }
}

