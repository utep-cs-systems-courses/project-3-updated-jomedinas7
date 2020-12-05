#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "buzzerStateMachines.h"
#include "p2switches.h"

#include "abCircle.h"
#include "shape.h"
#include "drawing.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;

u_int bgColor = COLOR_WHITE; 
char heart_state = 0;
int offsetHeart = 0;

void wdt_c_handler()
{
  static int secCount = 0;
  secCount ++;

  u_int switches = p2sw_read();

  
  if((switches & 256)){
    s0IsPressed = (s0IsPressed) ? 0 : 1;
    if(button != 0){
      buttonChanged = 1;
    }
    if(s0IsPressed){
      button = 0;
    }
  }
  if((switches & 512)){
    s1IsPressed = (s1IsPressed) ? 0 : 1;
    if(button != 1){
      buttonChanged = 1;
    }
    if(s1IsPressed){
      button = 1;
    }
  }
  if((switches & 1024)){
    s2IsPressed = (s2IsPressed) ? 0 : 1;
    if(button != 2){
      buttonChanged = 1;
    }
    if(s2IsPressed){
      button = 2;
    }
  }
  if((switches & 2048)){
    s3IsPressed = (s3IsPressed) ? 0 : 1;
    if(button != 3){
      buttonChanged = 1;
    }
    if(s3IsPressed){
      button = 3;
    }
  }
  
  switch(button){
  case 0:
    if(secCount % 225 == 0) redrawScreen = 1;
    break;
  case 1:
    if(secCount == 251)
    redrawScreen = 1;
    break;
  case 2:
    redrawScreen = 1;
    break;
  case 3:
    redrawScreen = 1;
    break;
  }
  if(secCount % 250 == 0){
    secCount == 0;
  }
}



void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  
  configureClocks();
  lcd_init();
  p2sw_init(15);
  buzzer_init();
  led_init();
  stateInit();

  clearScreen(COLOR_PINK);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  while (1) {
   if (redrawScreen) {      
    switch(button){
    case 0:
      if(buttonChanged){
	tgl_green_off();
	clearScreen(COLOR_WHITE);
      }
      heart_states();
      break;
    case 1:
      if(buttonChanged){
	tgl_green_off();
	clearScreen(COLOR_WHITE);
      }
       drawHeart(60,70,COLOR_YELLOW);
     //drawString8x12(15,30,"Now playing:",COLOR_WHITE,COLOR_PURPLE);
     break;
    case 2:
      if(buttonChanged){
	tgl_green_off();
	clearScreen(COLOR_BLACK);
      }
      play_song();
      break;
    case 3:
      assyNoteScale();
      break;
    }
    buttonChanged = 0;
    redrawScreen = 0;
   }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
/* forever */

  }
}

    
    



