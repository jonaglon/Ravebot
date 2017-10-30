
/* ************************************************************** *
 *                                                               
 *                            LED PATTERNS
 *  
 * ************************************************************** */

int tapePattern[224][2] = {
  {4,6}, {4,5}, {4,4}, {4,0}, {4,1}, {4,2}, {4,7}, {4,10}, {4,9}, {4,8}, 
  {4, 3}, {3,83}, {3,82}, {3,81}, {3,80}, {3,79}, {3,78}, {3,77}, {3,76}, {3,75},   
  {3,74}, {3,73}, {3,72}, {3,71}, {3,70}, {3,69}, {3,68}, {3,67}, {3,66}, {3,65},   
  {3,64}, {3,63}, {3,62}, {3,61}, {3,60}, {3,59}, {3,58}, {3,57}, {3,56}, {3,55},   
  {3,54}, {3,53}, {3,52}, {3,51}, {3,50}, {3,49}, {3,48}, {3,47}, {3,46}, {3,45},   
  {3,44}, {3,43}, {3,42}, {3,41}, {3,40}, {3,39}, {3,38}, {3,37}, {3,36}, {3,35},   
  {3,34}, {3,33}, {3,32}, {3,31}, {3,30}, {3,29}, {3,28}, {3,27}, {3,26}, {3,25},   
  {3,24}, {3,23}, {3,22}, {3,21}, {3,20}, {3,19}, {3,18}, {3,17}, {3,16}, {3,15},   
  {3,14}, {3,13}, {3,12}, {3,11}, {3,10}, {3, 9}, {3, 8}, {3, 7}, {3, 6}, {3, 5},   
  {3, 4}, {3, 3}, {3, 2}, {3, 1}, {3, 0}, {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4},   
  {5, 5}, {5, 6}, {5, 7}, {5, 8}, {5, 9}, {5,10}, {5,11}, {5,12}, {5,13}, {5,14}, 
  {5,15}, {5,16}, {5,17}, {5,18}, {5,19}, {5,20}, {5,21}, {5,22}, {5,23}, {5,24}, 
  {5,25}, {5,26}, {5,27}, {5,28}, {5,29}, {5,30}, {5,31}, {0,16}, {0,15}, {0,14}, 
  {0,13}, {0,12}, {0,11}, {0,10}, {0, 9}, {0, 8}, {0, 7}, {0, 6}, {0, 5}, {0, 4}, 
  {0, 3}, {0, 2}, {0, 1}, {0, 0}, {0,31}, {0,30}, {0,29}, {0,28}, {0,27}, {0,26}, 
  {0,25}, {0,24}, {0,23}, {0,22}, {0,21}, {0,20}, {0,19}, {0,18}, {0,17}, {0,44}, 
  {0,43}, {0,42}, {0,41}, {0,40}, {0,39}, {0,38}, {0,37}, {0,36}, {0,35}, {0,34}, 
  {0,33}, {0,32}, {0,31}, {0,55}, {0,54}, {0,53}, {0,52}, {0,51}, {0,50}, {0,49},
  {0,48}, {0,47}, {0,46}, {0,45}, {0,64}, {0,63}, {0,62}, {0,61}, {0,60}, {0,59},
  {0,58}, {0,57}, {0,56}, {0,71}, {0,70}, {0,69}, {0,68}, {0,67}, {0,66}, {0,65},
  {0,78}, {0,77}, {0,76}, {0,75}, {0,74}, {0,73}, {0,72}, {0,83}, {0,82}, {0,81},
  {0,80}, {0,79}, {0,78}, {1, 7}, {1,10}, {1, 9}, {1, 8}, {1, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 6}, {1, 5}, {1, 4} };

int sweepPatterns[270][5] = {
{  0, 27,  2,  8,  6}, {  1, 30,  2, 10,  3}, {  2, 33,  3, 13,  2}, {  3, 36,  4, 17,  1}, {  4, 38,  6, 21,  1}, {  5, 39,  8, 24,  1}, {  6, 40, 10, 28,  2}, {  7, 41, 12, 31,  3},{  8, 41, 15, 34,  6},{  9, 41, 18, 36,  9},
{ 10, 40, 20, 38, 12}, { 11, 39, 22, 39, 15}, { 12, 38, 24, 39, 19}, { 13, 36, 27, 39, 23}, { 14, 33, 28, 38, 27}, { 15, 30, 29, 36, 30}, { 16, 27, 29, 34, 32}, { 17, 25, 29, 31, 35},{ 18, 23, 28, 28, 37},{ 19, 21, 27, 24, 38},
{ 20, 19, 24, 21, 38}, { 21, 17, 22, 17, 38}, { 22, 16, 20, 13, 37}, { 23, 15, 18, 10, 35}, { 24, 15, 15,  8, 32}, { 25, 15, 12,  5, 30}, { 26, 16, 10,  3, 27}, { 27, 17,  8,  2, 23},{ 28, 19,  6,  2, 19},{ 29, 21,  4,  2, 15},
{ 30, 23,  3,  3, 12}, { 31, 25,  2,  5,  9}, { 32, 27,  5, 10,  8}, { 33, 30,  5, 13, 00}, { 34, 33,  6, 17,  5}, { 35, 36,  8, 21,  5}, { 36, 37, 10, 24,  5}, { 37, 38, 12, 28, 00},{ 38, 38, 15, 31,  8},{ 39, 38, 18, 34, 11},
{ 40, 37, 20, 35, 15}, { 41, 36, 23, 35, 19}, { 42, 33, 24, 35, 23}, { 43, 30, 26, 34, 27}, { 44, 27, 26, 31, 30}, { 45, 25, 26, 28, 32}, { 46, 23, 24, 24, 34}, { 47, 21, 23, 21, 34},{ 48, 19, 20, 17, 34},{ 49, 18, 18, 13, 32},
{ 50, 18, 15, 10, 30}, { 51, 18, 12,  8, 27}, { 52, 19, 10,  6, 23}, { 53, 21,  8,  6, 19}, { 54, 23, 06,  6, 15}, { 55, 25,  5,  8, 11}, { 56, 27,  7, 13, 11}, { 57, 30,  8, 16,  8},{ 58, 33,  9, 21,  8},{ 59, 36, 12, 25,  8},
{ 60, 36, 15, 28, 11}, { 61, 36, 18, 31, 15}, { 62, 33, 21, 32, 19}, { 63, 30, 23, 31, 24}, { 64, 27, 23, 28, 28}, { 65, 25, 23, 25, 30}, { 66, 22, 21, 21, 30}, { 67, 21, 18, 16, 30},{ 68, 20, 15, 13, 28},{ 69, 21, 12, 10, 24},
{ 70, 22,  9,  9, 19}, { 71, 25,  8, 10, 15}, { 72, 27,  9, 15, 14}, { 73, 30, 10, 19, 11}, { 74, 33, 12, 23, 11}, { 75, 33, 15, 26, 14}, { 76, 33, 18, 28, 17}, { 77, 30, 20, 28, 22},{ 78, 27, 21, 26, 25},{ 79, 25, 20, 23, 27},
{ 80, 23, 18, 19, 27}, { 81, 22, 15, 15, 25}, { 82, 23, 12, 13, 22}, { 83, 25, 10, 13, 17}, { 84, 25, 13, 17, 19}, { 85, 25, 15, 19, 22}, { 86, 25, 17, 21, 23}, { 87, 27, 11, 17, 15},{ 88, 27, 13, 19, 17},{ 89, 27, 15, 21, 19},
{ 90, 27, 17, 23, 22}, { 91, 27, 19, 25, 23}, { 92, 30, 13, 21, 15}, { 93, 30, 15, 23, 17}, { 94, 30, 17, 25, 19}, { 95,  0, 64, 81, 52}, { 96,  0, 62, 80, 51}, { 97,  0, 60, 78, 49},{ 98,  0, 58, 76, 47},{ 99,  0, 57, 74, 45},
{100,  0, 55, 72, 43}, {101,  0, 53, 71, 42}, {102,  0, 51, 69, 40}, {103,  0, 50, 67, 38}, {104,  0, 48, 63, 36}, {105,  0, 46, 64, 34}, {106,  0, 44, 62, 33}, {107,  0, 43, 60, 31},{108,  0, 41, 58, 29},{109,  0, 39, 57, 28},
{110,  0, 38, 55, 27}, {111,  0, 36, 53, 25}, {112,  0, 34, 52, 23}, {113, 27, 71, 73, 72}, {114, 30, 71, 75, 69}, {115, 33, 72, 78, 68}, {116, 36, 73, 82, 67}, {117, 38, 75, 86, 67},{118, 39, 77, 89, 67},{119, 40, 79, 93, 68},
{120, 41, 81, 96, 69}, {121, 41, 84, 99, 72}, {122, 41, 87,101, 75}, {123, 40, 89,103, 78}, {124, 39, 91,104, 81}, {125, 38, 93,104, 85}, {126, 36, 96,104, 89}, {127, 33, 97,103, 93},{128, 30, 98,101, 96},{129, 27, 98, 99, 98},
{130, 25, 98, 96,101}, {131, 23, 97, 93,103}, {132, 21, 96, 89,104}, {133, 19, 93, 86,104}, {134, 17, 91, 82,104}, {135, 16, 89, 78,103}, {136, 15, 87, 75,101}, {137, 15, 84, 73, 98},{138, 15, 81, 70, 96},{139, 16, 79, 68, 93},
{140, 17, 77, 67, 89}, {141, 19, 75, 67, 85}, {142, 21, 73, 67, 81}, {143, 23, 72, 68, 78}, {144, 25, 71, 70, 75}, {145, 27, 74, 75, 74}, {146, 30, 74, 78, 72}, {147, 33, 75, 82, 71},{148, 36, 77, 86, 71},{149, 37, 79, 89, 71},
{150, 38, 81, 93, 72}, {151, 38, 84, 96, 74}, {152, 38, 87, 99, 77}, {153, 37, 89,100, 81}, {154, 36, 92,100, 85}, {155, 33, 93,100, 89}, {156, 30, 95, 99, 93}, {157, 27, 95, 96, 96},{158, 25, 95, 93, 98},{159, 23, 93, 89,100},
{160, 21, 92, 86,100}, {161, 19, 89, 82,100}, {162, 18, 87, 78, 98}, {163, 18, 84, 75, 96}, {164, 18, 81, 73, 93}, {165, 19, 79, 71, 89}, {166, 21, 77, 71, 85}, {167, 23, 75, 71, 81},{168, 25, 74, 73, 77},{169, 27, 76, 78, 77},
{170, 30, 77, 81, 74}, {171, 33, 78, 86, 74}, {172, 36, 81, 90, 74}, {173, 36, 84, 93, 77}, {174, 36, 87, 96, 81}, {175, 33, 90, 97, 85}, {176, 30, 92, 96, 90}, {177, 27, 92, 93, 94},{178, 25, 92, 90, 96},{179, 23, 90, 86, 96},
{180, 21, 87, 81, 96}, {181, 20, 84, 78, 94}, {182, 21, 81, 75, 90}, {183, 23, 78, 74, 85}, {184, 25, 77, 75, 81}, {185, 27, 78, 80, 80}, {186, 30, 79, 84, 77}, {187, 33, 81, 88, 77},{188, 33, 84, 91, 80},{189, 33, 87, 93, 83},
{190, 30, 89, 93, 88}, {191, 27, 90, 91, 91}, {192, 25, 89, 88, 93}, {193, 23, 87, 84, 93}, {194, 23, 84, 80, 91}, {195, 23, 81, 78, 88}, {196, 25, 79, 78, 83}, {197, 25, 82, 82, 85},{198, 25, 84, 84, 88},{199, 25, 86, 86, 89},
{200, 27, 80, 82, 81}, {201, 27, 82, 84, 83}, {202, 27, 84, 86, 85}, {203, 27, 86, 88, 88}, {204, 27, 88, 90, 89}, {205, 30, 82, 86, 81}, {206, 30, 84, 88, 83}, {207, 30, 86, 90, 85},{208, 29, 00, 70, 64},{209, 27, 00, 68, 66},
{210, 26, 00, 66, 67}, {211, 24, 00, 65, 69}, {212, 22, 00, 63, 71}, {213, 20, 00, 61, 73}, {214, 18, 00, 59, 75}, {215, 17, 00, 57, 77}, {216, 15, 00, 56, 79}, {217,  0, 62, 54, 79},{218,  0, 60, 53, 77},{219,  0, 59, 51, 75},
{220,  0, 57, 49, 74}, {221,  0, 55, 47, 72}, {222,  0, 53, 46, 70}, {223,  0, 52, 44, 68}, {224,  0, 50, 42, 67}, {225,  0, 48, 41, 65}, {226,  0, 46, 39, 63}, {227,  0, 45, 37, 61},{228,  0, 43, 35, 60},{229,  0, 41, 34, 58},
{230,  0, 40, 32, 56}, {231,  0, 38, 30, 54}, {232, 13, 36, 29, 53}, {233, 15, 00, 29, 51}, {234, 17, 00, 30, 50}, {235, 18, 00, 32, 48}, {236, 20, 00, 34, 46}, {237, 22, 00, 36, 44},{238, 24, 00, 37, 43},{239, 26, 00, 39, 41},
{240, 27, 00, 41, 39}, {241, 29, 00, 43, 00}, {242,  0, 74, 53,105}, {243,  0, 76, 55,107}, {244,  0, 78, 57,109}, {245,  0, 80, 59,111}, {246,  0, 26,  1, 55}, {247,  0, 27,  3, 56},{248,  0, 29,  5, 58},{249,  0, 31,  7, 60},
{250,  0, 32,  8, 61}, {251,  0, 34, 10, 63}, {252,  0, 36, 12, 65}, {253,  0, 37, 13, 67}, {254,  0, 39, 15, 68}, {255,  0, 41, 17, 70}, {256,  0, 43, 19, 75}, {257,  0, 44, 20, 74},{258,  0, 46, 22, 75},{259,  0, 48, 24, 77},
{260,  0, 49, 25, 79}, {261,  0, 51, 27, 80}, {262,  0, 53, 29, 82}, {263,  0, 55, 30, 84}, {264,  0, 57, 32, 86}, {265,  0, 58, 34, 88}, {266,  0, 60, 35, 90}, {267,  0, 62, 37, 91},{268,  0, 64, 39, 93},{269,  0, 65, 40, 95}};
 

boolean rightEyeQuartAnim [4][95] = {
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
  0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 
  0, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 
  0, 0, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
  1, 1, 0, 1, 1 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 
  1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 
  1, 1, 0, 0, 0 }
};

int numLedsSet[9] = {84, 11, 18, 84, 11, 34, 4, 24, 120};

void OLDOLDOLDOLD_doRgbwLights()
{


  //allOn();
  //rgbwRainbow(20);

  //lightsInTime();

  //beatLights();

  //doTalkingLights();


  //rgbwRainbow(1);

  //rgbwSnake();
  //bassBinRainbow(20);
  
  //rgbwSnake();

  //rgbwRainbow(10);

  //solidHeadColors();

  //rgbwRainbow(40);

  //doTapePattern(80);  

  //rgbwRainbow(20);

  /* drawMovingStripe(60, 300, 1, 10, 0, 100, 0, 0,  0);
  drawMovingStripe(30, 350, 2, 50, 0, 0, 100,  0, 0);
  drawMovingStripe(23, 500, 3, 10, 12, 0, 0,120,  0);
  drawMovingStripe(12, 400, 2, 15, 12, 0, 80,30,  0);
  drawMovingStripe(22, 200, 4, 20, 24, 20, 30,  80,0);
  drawMovingStripe(40, 250, 3, 5, 24,  30, 80,  0,  0);

  //drawMovingStripe(6, 12, 4, 5, 0, 255, 0, 0, 0);
  //drawMovingStripe(32, 166, 3, 20, 0, 255, 0, 0, 0);
  //drawMovingStripe(60, 199, 2, 25, 12, 130, 130, 0, 0);
  //drawMovingStripe(25, 990, 1, 12, 12, 0, 130, 130, 0);
  //drawMovingStripe(12, 220, 4, 4, 24, 0, 0, 0, 255);
  //drawMovingStripe(12, 220, 3, 20, 24, 0, 0, 0, 255); */

   //quarterLights(500);

  //doTalkingLights();

  //tubeTest();

}


void tubeTest() {
  //for (int pixNum = 0; pixNum < 20; pixNum++) {
  //  setLedDirect(270, 255, 0, 0, 0);
  //}
  setLedDirect(271, 0, 0 , 0, 255);
  setLedDirect(274, 0, 0, 0, 255);
}

void drawMovingStripe(int speedFactor, int animationSteps, int stripeDirection, int stripeLength, int offset, int r, int g, int b, int w) {

  int thisFrame = ((timey / speedFactor) % animationSteps) + offset;

  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    if (sweepPatterns[pixNum][stripeDirection] > 0)
      if (thisFrame > sweepPatterns[pixNum][stripeDirection] && thisFrame < (sweepPatterns[pixNum][stripeDirection]+stripeLength))
        setLedDirect(pixNum, r, g, b, w);
  }
}

void drawMovingStripeRev(int speedFactor, int animationSteps, int stripeDirection, int stripeLength, int offset, int r, int g, int b, int w) {

  int thisFrame = ((timey / speedFactor) % animationSteps) + offset;

  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    if (sweepPatterns[pixNum][stripeDirection] > 0)
      if ((animationSteps-thisFrame) > sweepPatterns[pixNum][stripeDirection] && ((animationSteps-thisFrame) < sweepPatterns[pixNum][stripeDirection] + stripeLength))
        setLedDirect(pixNum, r, g, b, w);
  }
}


void sweepTestThree(int speedFactor) {
  int j, pixNum;

  int thisFrame = (timey / speedFactor) % 122;

  // forward
  for (pixNum = 0; pixNum < 270; pixNum++) {
    if (thisFrame > sweepPatterns[pixNum][4] && thisFrame < sweepPatterns[pixNum][4]+20)
      setLedDirect(pixNum, 0, 0, 255, 0);
  }

}

void sweepTestRainbow(int speedFactor) {
  int j, pixNum;

  int thisFrame = (timey / speedFactor) % 130;

  int rainbowFactor = (timey / 5) % 255;

  // forward
  for (pixNum = 0; pixNum < 270; pixNum++) {
    if (thisFrame > sweepPatterns[pixNum][4] && thisFrame < sweepPatterns[pixNum][4]+20)
      SetRgbwWheel(pixNum, rainbowFactor, 20);
  }
}

/*
void doTapePattern(int speedFactor) {
  int animSteps = 224;

  int ticky = (timey / speedFactor) % animSteps;

  for (int i = 0; i < 122; i++)
  {
    //setLedBySet(tapePattern[(ticky+i)%animSteps][0], tapePattern[(ticky+i)%animSteps][1], 255, 0, 0, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i)%animSteps][0], tapePattern[(ticky+i)%animSteps][1], i, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i+56)%animSteps][0], tapePattern[(ticky+i+56)%animSteps][1], (i+80) % animSteps, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i+112)%animSteps][0], tapePattern[(ticky+i+112)%animSteps][1], (i+160) % animSteps, 0);
    SetRgbwWheelSet(tapePattern[(ticky+i+168)%animSteps][0], tapePattern[(ticky+i+168)%animSteps][1], (i+240) % animSteps, 0);
  } 
}  */

void rgbwRainbow(int speedFactor) {

  int ticky = (timey / speedFactor);

  // forward
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    SetRgbwWheel(pixNum, (pixNum + ticky) % 255, 0);
  }
}

void SetRgbwWheel(int pixNum, byte WheelPos, short whiteVal) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    setLedDirect(pixNum, 255 - WheelPos * 3, 0, WheelPos * 3, whiteVal);
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    setLedDirect(pixNum, 0, WheelPos * 3, 255 - WheelPos * 3, whiteVal);
    return;
  }
  WheelPos -= 170;
  setLedDirect(pixNum, WheelPos * 3, 255 - WheelPos * 3, 0, whiteVal);
  return;
}

/*
void SetRgbwWheelSet(int ledSet, int pixNum, byte WheelPos, short whiteVal) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    setLedBySet(ledSet, pixNum, 255 - WheelPos * 3, 0, WheelPos * 3, whiteVal);
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    setLedBySet(ledSet, pixNum, 0, WheelPos * 3, 255 - WheelPos * 3, whiteVal);
    return;
  }
  WheelPos -= 170;
  setLedBySet(ledSet, pixNum, WheelPos * 3, 255 - WheelPos * 3, 0, whiteVal);
  return;
}  */

int test=0;
void rgbwSnake() {
  setLedDirect((test % numLeds) + 4, 40, 10, 10, 5);
  setLedDirect((test % numLeds) + 3, 80, 10, 0, 50);
  setLedDirect((test % numLeds) + 2, 80, 10, 0, 60);
  setLedDirect((test % numLeds) + 1, 120, 10, 0, 50);
  setLedDirect((test % numLeds) + 0, 0, 0, 0, 0);
  test++;
}



void bassBinRainbow(int speedFactor) {
  unsigned long thisFrame = (timey / speedFactor);
  
  for (int pixNum = 0; pixNum < numLeds; pixNum++) {
    SetRgbwWheel(pixNum, (thisFrame + (pixNum / 8)) % 255, 0);
  }

}




void lightsInTime() {

  //int thisFrame = sixteenth % 4;

  /*for (int pixNum = 0; pixNum < 95; pixNum++) {
    if (rightEyeQuartAnim[thisFrame][pixNum]) {
      if (currentBar % 4 == 0) {
        setLedDirect(pixNum, 255, 255, 255, 255);
      } else if (currentBar % 4 == 1) {
        setLedDirect(pixNum, 255, 0, 0, 0);
      } else if (currentBar % 4 == 2) {
        setLedDirect(pixNum, 0, 255, 0, 0);
      } else if (currentBar % 4 == 3) { 
        setLedDirect(pixNum, 0, 0, 255, 0);
      };
    }
  }*/
  
  /*if (dropCountdown == 0)
    LEDS.setBrightness(64);
  else 
    LEDS.setBrightness(dropCountdown*4);*/
}

void beatLights() {

  if (timey - beatTimes[0] < 255) {
    int ledValue = (beatTimes[0] + 255)-timey;
    setLedDirect(dropCountdown+114, 0, ledValue, 0, 0);
  }
  
}




void doTalkingLights() {

  if (robotTalking) {
    setLedBySet(2, 8, 255, 60, 60, 100);
    setLedBySet(2, 9, 255, 60, 60, 100);
    
    if (timey > (robotTalkingOnTime + 40)) {
      setLedBySet(2, 7, 255, 60, 60, 100);
      setLedBySet(2, 10, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 80)) {
      setLedBySet(2, 6, 255, 60, 60, 100);
      setLedBySet(2, 11, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 110)) {
      setLedBySet(2, 5, 255, 60, 60, 100);
      setLedBySet(2, 12, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 135)) {
      setLedBySet(2, 4, 255, 60, 60, 100);
      setLedBySet(2, 13, 255, 60, 60, 100);
    }
    
    if (timey > (robotTalkingOnTime + 150)) {
      setLedBySet(2, 3, 255, 60, 60, 100);
      setLedBySet(2, 14, 255, 60, 60, 100);
    }
    
  }
}



void solidHeadColors() {

  for(int j = 0; j < numLedsSet[0]; j++) {
    setLedBySet(0, j, 255, 0, 255, 0);
  }

  for(int j = 0; j < numLedsSet[1]; j++) {
    setLedBySet(1, j, 0, 255, 0, 0);
  }

  for(int j = 0; j < numLedsSet[2]; j++) {
    setLedBySet(2, j, 150, 30, 0, 0);
  }

  for(int j = 0; j < numLedsSet[3]; j++) {
    setLedBySet(3, j, 0, 0, 100, 0);
  }

  for(int j = 0; j < numLedsSet[4]; j++) {
    setLedBySet(4, j, 2, 0, 0, 255);
  }

  for(int j = 0; j < numLedsSet[5]; j++) {
    setLedBySet(5, j, 255, 0, 0, 0);
  }

  for(int j = 0; j < numLedsSet[6]; j++) {
    setLedBySet(6, j, 0, 80, 0, 0);
  }

  for(int j = 0; j < numLedsSet[7]; j++) {
    setLedBySet(7, j, 0, 0, 255, 0);
  }

  for(int j = 0; j < numLedsSet[8]; j++) {
    setLedBySet(8, j, 0, 0, 0, 255);
  }
  for(int j = 0; j < numLedsSet[8]; j++) {
    setLedBySet(8, j, 255, 0, 0, 0);
  }  
}   

/* 0  - RGB   Left Eye Outer  84
 * 1  - RGBW  Left Eye Inner  11
 * 2  - RGBW  Mouth           18
 * 3  - RGB   Right Eye Outer 84
 * 4  - RGBW  Right Eye Inner 11
 * 5  - RGBW  Casette         34
 * 6  - RGBW  4                4
 * 7  - RGBW  Dial            24       */
void setLedBySet(int ledSet, int ledNum, int rVal, int gVal, int bVal, int wVal) {
  if (ledNum < 0)
    return;

  if (ledSet == 0 && ledNum < numLedsSet[0])
    setLedDirect(ledNum, rVal, gVal, bVal, wVal);
  else if (ledSet == 1 && ledNum < numLedsSet[1])
    setLedDirect(ledNum + 84, rVal, gVal, bVal, 0);
  else if (ledSet == 2 && ledNum < numLedsSet[2])
    setLedDirect(ledNum + 95, rVal, gVal, bVal, wVal);
  else if (ledSet == 3 && ledNum < numLedsSet[3])
    setLedDirect(ledNum + 113, rVal, gVal, bVal, 0);
  else if (ledSet == 4 && ledNum < numLedsSet[4])
    setLedDirect(ledNum + 197, rVal, gVal, bVal, wVal);
  else if (ledSet == 5 && ledNum < numLedsSet[5])
    setLedDirect(ledNum + 208, rVal, gVal, bVal, wVal);
  else if (ledSet == 6 && ledNum < numLedsSet[6])
    setLedDirect(ledNum + 242, rVal, gVal, bVal, wVal);
  else if (ledSet == 7 && ledNum < numLedsSet[7])
    setLedDirect(ledNum + 246, rVal, gVal, bVal, wVal);
  else if (ledSet == 8 && ledNum < numLedsSet[8])
    setLedDirect(ledNum + 270, rVal, gVal, bVal, wVal);
}


void setLed(int ledNum, int rVal, int gVal, int bVal, int wVal) {
  setLedDirect(ledNum, rVal, gVal, bVal, wVal);
}


void allOn() {
  for(int j = 0; j < numLeds; j++) {
    setLedDirect(j, 255, 255, 255, 255);
  }
}

void allOff() {
  for(int j = 0; j < numLeds; j++) {
    setLedDirect(j, 0, 0, 0, 0);
  }
}




