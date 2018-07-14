

void doBeatDanceMove() {
  if (robotManualMode)
    return;

  doDance1();
}

void doDance1() {
  if ((currentBar % 2) == 0)
    moveServoToPos(9, servos[9].leftDancePos);
  else 
    moveServoToPos(9, servos[9].rightDancePos);
}

