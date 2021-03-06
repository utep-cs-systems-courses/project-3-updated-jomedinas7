#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "assyStates.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "drawing.h"

char scaleNote = 1;
short note = 0;  
char count = 0;
  
void stateInit()

{
  startX = 60;
  startY = 60;
  heartState = 0;
  button = 4;
}


short noteToBuz(short note){
  return 2000000/note;
}

void heart_states(){
  clearScreen(COLOR_WHITE);
      /*this switch statement will alternate between hearts being drawn on the lcd*/
  switch(heartState){
  case(0):
    drawHeart(startX,startY,COLOR_RED);
    heartState++;
    break;
  case(2):
    drawHeart(startX,startY,COLOR_BLUE);
    heartState++;
    break;
  case(4):
    drawHeart(startX,startY,COLOR_PURPLE);
    heartState++;
    break;
  case(6):
    heartState = 0;
    break;
  default:
    heartState++;
      }
}


void assyNoteScale()
{
  
  if(++count != 250){
    switch(scaleNote){
    case 1:
      //note 350
      // clearScreen(COLOR_AQUAMARINE);
      break;
    case 2:
      //note 440
      clearScreen(COLOR_RED);
      break;
    case 3:
      clearScreen(COLOR_VIOLET);
      //note 523
      break;
    case 4:
      clearScreen(COLOR_ORANGE);
      //note 698
      break;
    default:
      clearScreen(COLOR_WHITE);
      // scaleNote = -1;
      //note 0
      break;
    }
    //note = assySong(scaleNote);
    //buzzer_set_period(note);
    convert();
    if(scaleNote == 4){
      scaleNote = 0;
    }else{
      scaleNote++;
    }
  }
}
void tgl_red_on()
{
  red_on = 1;
  led_update();
}

void tgl_green_on()
{
  green_on = 1;
  led_update();
}

void tgl_red_off()
{
  red_on = 0;
  led_update();
}

void tgl_green_off()
{
  green_on = 0;
  led_update();
}

//will dim red light to 25% brightness
void dim_red_25()
{
  static char state = 0;
  char changed = 0;

  switch(state){
  case 0:
    tgl_red_off();
    state = 1;
    changed = 1;
    break;
  case 1:
    tgl_red_off();
    state = 2;
    break;
  case 2:
    tgl_red_off();
    state = 3;
    break;
  case 3:
    tgl_red_on();
    changed = 1;
    state = 0;
    break;
  }
  led_changed = changed;
  led_update();
}
//will dim red light to 50%
void dim_red_50(){
  static char state = 0;
  char changed = 0;

  switch(state){
  case 0:
    tgl_red_on();
    state = 1;
    changed =1;
    break;
  case 1:
    tgl_red_off();
    state = 0;
    changed = 1;
    break;
  }
  led_changed = changed;
  led_update();
}

//will dim red light to 75%
void dim_red_75()
{
  static char state = 0;
  char changed = 0;

  switch(state){
  case 0:
    tgl_red_off();
    state = 1;
    changed = 1;
    break;
  case 1:
    tgl_red_on();
    changed = 1;
    state = 2;
    break;
  case 2:
    tgl_red_on();
    state = 3;
    break;
  case 3:
    tgl_red_on();
    state = 0;
    break;
  }
  led_changed = changed;
  led_update();
}

//will progress through 25%,50%, and 75% dimness 
void state_advance()
{
  static char count = 0;
  static char state  = 1;
  if(++count != 250){
    switch(state) {
    case 1:
      dim_red_25();
      break;
    case 2:
      dim_red_75();
      break;
    case 3:
      dim_red_50();
      break;
    }
     
    led_changed = 1;
    led_update();
  }
  else{
    //start states loop over
    if(state == 3){
      state  = 1;
      count = 0;
    }else{
      //advance state
      state++;
    }
  }
}
//will cycle red and green LEDs through pattern
void both_lights()
{
  static char b_count = 0;
  static char b_state = 1;
  if(++b_count != 250){
    switch(b_state){
    case 1:
      red_on = 0;
      green_on = 0;
      break;
    case 2:
      red_on = 1;
      break;
    case 3:
      green_on =1;
      break;
    case 4:
      red_on = 0;
      green_on = 0;
      break;
    case 5:
      red_on = 1;
      green_on = 1;
      break;
    }
    led_changed =1;
    led_update();
  }else{
    //if in final state, start loop over
    if(b_state == 5){
      b_state = 1;
      b_count = 1;
    }else{
      //advance to next state
      b_state++;
    }
  }
}

