int animation_1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
int animation_2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
int animation_3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
int animation_4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
int emptyline[] = {0,0,0,0,0,0,0,0};




#define NUM_LEDS 8 // amount of leds available
int pins[] = {2, 0, 4, 16, 17, 5, 18, 23}; // led pins
int animLines = 5; // amount of lines per animation


//----------------- Get Delay Time -----------------//

// Number of "lines" in one lap
int linesPerLap = 20;

// Compensate the latency of the code execution
int latency = 0;

// Used to calculate the delay time between each line
long boardTime = 1;
long boardTime_memo = 1;

// Time between each lap
long period = 1;

// Time to wait before to print one line of leds
int delayTime = 100000;

/* micros() : Returns the number of microseconds since the Arduino board
began running the current program. Data type: unsigned long. */
void getDelayTime() {
  boardTime = micros(); // (microseconds)
  period = (boardTime - boardTime_memo); // period of one lap (us)
  boardTime_memo = boardTime; // stock data
  delayTime = round((period/linesPerLap) - latency); // time to wait before to print one line of leds (us)
  if(delayTime > 1000000) { // if the result is too big to be correct (> 1 second)
        delayTime = 1;
  }
  if(delayTime < 1) { // if the result is too small to be correct (< 1 microsecond)
        delayTime = 1;
  }
}
//--------------------------------------------------//


//------------------- Print Line -------------------//
void printLine(int line[]) {
  for (int i=0; i<NUM_LEDS; i++) {
    digitalWrite(pins[i], line[i]);
  }
  delayMicroseconds(delayTime);
}
//--------------------------------------------------//


//------------- Turn all the leds off --------------//
void turnLightsOff() {
  printLine(emptyline);
}
//--------------------------------------------------//


//----------------- Print Animation -------------------//
/* Convert the animArray into lines and print each line */
void printAnim(int animArray[]) {
  int line[NUM_LEDS] = {}; // declare an empty list
  for (int lineFirstLed=0; lineFirstLed<(animLines*NUM_LEDS); lineFirstLed+=NUM_LEDS) { // for each line of the animArray
    for(int led=0; led<NUM_LEDS; led++) { // for each led of the line
      line[led] = animArray[lineFirstLed+led]; // write the led state into a "line" list
    }
    printLine(line); // print the line
    printLine(emptyline); // print an empty line
  }
}
//--------------------------------------------------//


//----------------- Set Animation -------------------//
void setAnimation(int animationNb) {
  if (animationNb == 1)
  {
          printAnim(animation_1);
          //Serial.println("animation 1");
  }
  if (animationNb == 2)
  {
          printAnim(animation_2);
          //Serial.println("animation 2");
  }
  if (animationNb == 3)
  {
          printAnim(animation_3);
          //Serial.println("animation 3");
  }
}
