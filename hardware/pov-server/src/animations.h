//** Animation NB order
//** 0: default.h
//** 1: 1c1.h
//** 2: bach.h
//** 3: chachacha.h
//** 4: kalinka.h
//** 5: marche_turque.h
//** 6: marin.h
//** 7: pascal.h
//** 8: ragtime.h

#include "animations/1c1.h"
#include "animations/bach.h"
#include "animations/chachacha.h"
#include "animations/kalinka.h"
#include "animations/marche_turque.h"
#include "animations/marin.h"
#include "animations/pascal.h"
#include "animations/ragtime.h"


//**********************************Animation Group********************************//
// Each animation is a "frame" of the group
int animation_1[] = {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1};
int animation_2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int animation_3[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int animation_4[] = {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int animation_5[] = {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int animation_6[] = {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int animation_7[] = {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
int animation_8[] = {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};

//**********************************Default Group********************************//
int default_1[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int default_2[] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int default_3[] = {1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int default_4[] = {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int default_5[] = {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int animNb = 0; // Name of the animation


//**********************************Utils********************************//
int emptyline[] = {0,0,0,0,0,0,0,0};




#define NUM_LEDS 8 // amount of leds available
int pins[] = {0, 4, 16, 17, 5, 18, 23,19}; // led pins
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
int delayTime = 500;

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

  
// Depending on animName import the correct animation.h file
  switch(animNb)
  {
  case 0:
    // 1c1.h animations memcpy
    memcpy(animation_1, c1_1, sizeof(animation_1));
    memcpy(animation_2, c1_2, sizeof(animation_2));
    memcpy(animation_3, c1_3, sizeof(animation_3));
    memcpy(animation_4, c1_4, sizeof(animation_4));
    memcpy(animation_5, c1_5, sizeof(animation_5));
  case 1:
    // bach
    memcpy(animation_1, bach_1, sizeof(animation_1));
    memcpy(animation_2, bach_2, sizeof(animation_2));
    memcpy(animation_3, bach_3, sizeof(animation_3));
    memcpy(animation_4, bach_4, sizeof(animation_4));
  case 2:
    //chachacha
    memcpy(animation_1, chachacha_1, sizeof(animation_1));
    memcpy(animation_2, chachacha_2, sizeof(animation_2));
    memcpy(animation_3, chachacha_3, sizeof(animation_3));
    memcpy(animation_4, chachacha_4, sizeof(animation_4));
    memcpy(animation_5, chachacha_5, sizeof(animation_5));
  case 3:
    // kalinka
    memcpy(animation_1, kalinka_1, sizeof(animation_1));
    memcpy(animation_2, kalinka_2, sizeof(animation_2));
    memcpy(animation_3, kalinka_3, sizeof(animation_3));
    memcpy(animation_4, kalinka_4, sizeof(animation_4));
  case 4:
    // marche_turque
    memcpy(animation_1, marche_turque_1, sizeof(animation_1));
    memcpy(animation_2, marche_turque_2, sizeof(animation_2));
    memcpy(animation_3, marche_turque_3, sizeof(animation_3));
    memcpy(animation_4, marche_turque_4, sizeof(animation_4));
    memcpy(animation_5, marche_turque_5, sizeof(animation_5));
    memcpy(animation_6, marche_turque_6, sizeof(animation_6));
  case 5:
    // marin
    memcpy(animation_1, marin_1, sizeof(animation_1));
    memcpy(animation_2, marin_2, sizeof(animation_2));
    memcpy(animation_3, marin_3, sizeof(animation_3));
    memcpy(animation_4, marin_4, sizeof(animation_4));
    memcpy(animation_5, marin_5, sizeof(animation_5));
    memcpy(animation_6, marin_6, sizeof(animation_6));
    memcpy(animation_7, marin_7, sizeof(animation_7));
    memcpy(animation_8, marin_8, sizeof(animation_8));
  case 6:
    // pascal
    memcpy(animation_1, pascal_1, sizeof(animation_1));
    memcpy(animation_2, pascal_2, sizeof(animation_2));
    memcpy(animation_3, pascal_3, sizeof(animation_3));
    memcpy(animation_4, pascal_4, sizeof(animation_4));
    memcpy(animation_5, pascal_5, sizeof(animation_5));
    memcpy(animation_6, pascal_6, sizeof(animation_6));
  case 7:
    // ragtime
    memcpy(animation_1, ragtime_1, sizeof(animation_1));
    memcpy(animation_2, ragtime_2, sizeof(animation_2));
    memcpy(animation_3, ragtime_3, sizeof(animation_3));
    memcpy(animation_4, ragtime_4, sizeof(animation_4));
    memcpy(animation_5, ragtime_5, sizeof(animation_5));
    memcpy(animation_6, ragtime_6, sizeof(animation_6));
  default:
    break;
  }

  if (animationNb == 1)
  {
          printAnim(animation_1);
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
  if (animationNb == 4)
  {
          printAnim(animation_4);
          //Serial.println("animation 3");
  }
  if (animationNb == 5)
  {
          printAnim(animation_5);
          //Serial.println("animation 3");
  }
  if (animationNb == 6)
  {
          printAnim(animation_6);
          //Serial.println("animation 3");
  }
  if (animationNb == 7)
  {
          printAnim(animation_7);
          //Serial.println("animation 3");
  }
  if (animationNb == 8)
  {
          printAnim(animation_8);
          //Serial.println("animation 3");
  }

}
