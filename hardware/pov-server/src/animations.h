int animation_1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
int animation_2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
int animation_3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
int animation_4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
int emptyline[] = {0,0,0,0,0,0,0,0};


int pins[] = {2, 0, 4, 16, 17, 5, 18, 23};

#define NUM_LEDS 8


//----------------- Get Delay Time -----------------//

// Number of "lines" in one lap
int numLines = 20;

// Compensate the latency of the code execution
int latency = 0;

// Used to calculate the delay time between each line
long boardTime = 1;
long boardTime_memo = 1;

// Time between each lap
long period = 1;

// Time to wait before to print one line of leds
int delayTime = 1;

/* micros() : Returns the number of microseconds since the Arduino board
began running the current program. Data type: unsigned long. */
void getDelayTime() {
  boardTime = micros(); // (microseconds)
  period = (boardTime - boardTime_memo); // period of one lap (us)
  boardTime_memo = boardTime; // stock data
  delayTime = round((period/numLines) - latency); // time to wait before to print one line of leds (us)
  //Serial.println(delayTime);
  if(delayTime > 1000000) {
        delayTime = 1;
  }
  if(delayTime < 1) {
        delayTime = 1;
  }
}
//--------------------------------------------------//


//----------------- Print Radius -------------------//
void printLine(int line[]) {
  for (int i=0; i<NUM_LEDS; i++) {
    digitalWrite(pins[i], line[i]);
  }
  delayMicroseconds(delayTime);
}
//--------------------------------------------------//


//----------------- Print Animation -------------------//
void printAnim(int chunk[]) {
  int line[NUM_LEDS] = {};
  for (int numline=0; numline<=(NUM_LEDS*4); numline+=NUM_LEDS) {
    for(int led=0; led<NUM_LEDS; led++) {
      line[led] = chunk[led+numline];
    }
    printLine(line);
  }
  printLine(emptyline); // chunk space
  //Serial.println("chunk DONE");
}
//--------------------------------------------------//


// animation function
void setAnimation(int animationNb)
{
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
