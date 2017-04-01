#define NodServoMin 3700
#define NodServoMax 4780
int nodServoPos = 3800;

#define NeckServoMin 3200
#define NeckServoMax 4400
int neckServoPos = 3800;


// called from init
void initServos() {

  delay(100);
  servoPwm.setPWM(0, 0, (nodServoPos/10)); 
  servoPwm.setPWM(1, 0, (neckServoPos/10)); 

}

void doServos() {
  
  // Nod
  if(ps2.readButton(PS2_UP)==0)
    doNodding(3);
  else if(ps2.readButton(PS2_DOWN)==0)
    doNodding(-3);

  // Neck
  if(ps2.readButton(PS2_LEFT)==0 && neckServoPos < NeckServoMax)
  {
    neckServoPos=neckServoPos+6;
    servoPwm.setPWM(1, 0, (neckServoPos/10));
  }
  if(ps2.readButton(PS2_RIGHT)==0 && neckServoPos > NeckServoMin)
  {
    neckServoPos=neckServoPos-6;
    servoPwm.setPWM(1, 0, (neckServoPos/10));
  }

}


void doNodding(int velocity) {
  if (velocity > 0 && nodServoPos < NodServoMax)
  {
    nodServoPos=nodServoPos+velocity;
    servoPwm.setPWM(0, 0, (nodServoPos/10));
  } 
  else if (velocity < 0 && nodServoPos > NodServoMin)
  {
    nodServoPos=nodServoPos+velocity;
    servoPwm.setPWM(0, 0, (nodServoPos/10));
  }
}


