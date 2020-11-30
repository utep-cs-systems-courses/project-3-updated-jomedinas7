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

static char button = 0;

u_int bgColor = COLOR_WHITE; 
char heart_state = 0;
int offsetHeart = 0;
void wdt_c_handler()
{
  u_int switches = p2sw_read();
   
  if(switches & 256){ //button 1 pressed
    offsetHeart+=2;
    clearScreen(COLOR_WHITE);
    drawString8x12(0,0,"Press S1 <3",COLOR_RED,COLOR_WHITE);
    /*this switch statement will alternate between hearts being drawn on the lcd*/
    switch(heart_state){
    case(2):
      drawHeart(48+offsetHeart,84+offsetHeart,COLOR_RED);
      drawString8x12(0,0,"Press S1 again!",COLOR_RED,COLOR_WHITE);
      break;
    case(4):
      drawHeart(80+offsetHeart,20+offsetHeart,COLOR_BLUE);
      drawString8x12(0,0,"And again!",COLOR_RED,COLOR_WHITE);
      break;
    case(6):
      drawHeart(50+offsetHeart,50+offsetHeart,COLOR_PURPLE);
       drawString8x12(0,0,"One more time?",COLOR_RED,COLOR_WHITE);
      break;
    case(8):
      heart_state = 0;
      break;
    }
    heart_state++;
    button = 1;
  }
   else if(switches & 512){ //button 2 pressed
     clearScreen(COLOR_PURPLE);
     drawHeart(60,70,COLOR_YELLOW);
     drawString8x12(15,30,"Now playing:",COLOR_WHITE,COLOR_PURPLE);
     drawString8x12(20, 50, "Il Vento Di",COLOR_YELLOW,COLOR_PURPLE);
     drawString8x12(45,65, "Oro",COLOR_YELLOW,COLOR_PURPLE);
     button = 2;
   }
   else if(switches & 1024){ //button 3 pressed
     clearScreen(COLOR_PINK);
     drawString8x12(20,20,"Song paused.",COLOR_AQUAMARINE,COLOR_PINK);
      drawString8x12(0,40,"> S1:<3",COLOR_RED,COLOR_PINK);
      drawString8x12(0,80,"> S2:Resume",COLOR_PURPLE,COLOR_PINK);
     button = 3;
   }
   else if(switches & 2048){ //button 4 pressed
     button = 4;
   }
  
  //this section of code handles interrupt dependent methods

  static int secCount = 0;
  if(++secCount!= 250){ //250 interrupts/sec
    switch(button){
    case(1):
      redrawScreen = 1;
      break;
    case(2):
      redrawScreen = 1;
      play_song();
      break;
    case(3):
      redrawScreen = 1;
      state_advance(); //red led dim cycles
      buzzer_set_period(0);
      break;
    case(4):
      assyNoteScale();
      drawString8x12(20,20,"Goodbye!", COLOR_WHITE,COLOR_BLACK);
      redrawScreen = 1;
      break;
    }
  }else{
    secCount = 0;
    redrawScreen =1;}
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
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;      
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



