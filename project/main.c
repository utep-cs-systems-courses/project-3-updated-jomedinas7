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

  
  if((switches & 1) == 0){
      button = 0;
  }
  if((switches & 2) == 0){
      button = 1;
  }
  if((switches & 4) == 0){
      button = 2;
  }
  if((switches & 8) == 0){
      button = 3;
  }
  
  switch(button){
  case 0:
    if(secCount % 200 == 0) redrawScreen = 1;
    break;
  case 1:
    if(secCount%50 == 0){
      redrawScreen = 1;
      offsetHeart++;
    }
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
      heart_states();
      buzzer_set_period(0);
      break;
    case 1:
      drawString8x12(30, 30,"Ciao :)",COLOR_PURPLE, COLOR_WHITE);
      drawHeart(60,70+offsetHeart,COLOR_YELLOW);
     break;
    case 2:
      play_song();
      state_advance();
      break;
    case 3:
      assyNoteScale();
      break;
    }
    redrawScreen = 0;
   }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
/* forever */

  }
}

    
    



