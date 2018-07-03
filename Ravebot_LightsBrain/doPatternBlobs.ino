
// 0-x, 1-y, 2-radius, 3-r, 4-g, 5-b, 6-w, 7-fadeSpeed
int colorBlobs[16][8] = {
   {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0},
   {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0},
   {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0},
   {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0}, {300,800,150,255,0,0,0,0} };

int currentBeat = 0;
void doPatternBlobs() {

  if (sixteenBeats != currentBeat) {
    currentBeat = sixteenBeats;
    setNewBlob(currentBeat);
  }

  for(int j = 0; j < 16; j++) { 

    for(int k = 0; k < 4; k++) { 
      if (colorBlobs[j][3+k] > 0) {
        colorBlobs[j][3+k] = colorBlobs[j][3+k]-colorBlobs[j][7];
      }
    }    
    drawSquare(colorBlobs[j][0], colorBlobs[j][1], colorBlobs[j][2], colorBlobs[j][3], colorBlobs[j][4], colorBlobs[j][5], colorBlobs[j][6]);
  }

}


void drawSquare(int xCoord, int  yCoord, int radius, int r, int g, int b, int w) {
  for(int j = 0; j < numLeds; j++) { 
    if (getCoord(j,0) < (xCoord+radius) && getCoord(j,1) < (yCoord+radius)) {
      if (getCoord(j,0) > (xCoord-radius) && getCoord(j,1) > (yCoord-radius)) {
        setLedDirect(j, r, g, b, w, false);
      }
    }
  }
}

void setNewBlob(int blobNumber) {

  // todo - make this! - setGoodBlobCoords

  setGoodRandomColorVars();

  colorBlobs[blobNumber][0] = random(700);  // x
  colorBlobs[blobNumber][1] = random(2000); // y
  colorBlobs[blobNumber][2] = random(20,250);  // radius
  colorBlobs[blobNumber][3] = goodColR;  // r
  colorBlobs[blobNumber][4] = goodColG;  // g
  colorBlobs[blobNumber][5] = goodColB;  // b
  colorBlobs[blobNumber][6] = goodColW;  // w
  colorBlobs[blobNumber][7] = random(0,6);   // blob Started Time
}

