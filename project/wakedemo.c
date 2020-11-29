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

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
//u_int fontFgColor = COLOR_GREEN;
static char button = 0;

u_int bgColor = COLOR_WHITE; 

/*board methods go in here*/
void wdt_c_handler()
{
  static int secCount = 0;  
  if(++secCount!= 250){
    redrawScreen = 1;
    secCount =0;
    switch(button){
    case(1):
      // buzzer_set_period(2000000/500);
      break;
    case(2):
      green_on = 0;
      led_changed =1;
      led_update();
      play_song();
      break;
    case(3):
      buzzer_set_period(2000000/700);
      break;
    case(4):
      state_advance();
      buzzer_set_period(0);
      break;
    }
  }
}



void drawHeart(char center,char height, u_int shapeColor){
Layer layer1 = {
  (AbShape *)&circle20,
  {center+17, height
  },
  {0,0}, {0,0},
  shapeColor,
  0
};
Layer layer2 = {
  (AbShape *)&circle20,
  {center-17, height
  },
  {0,0}, {0,0},
  shapeColor,
  &layer1
};
 layerDraw(&layer2);
  for(u_char r = 0; r < 15; r++) {
    for(u_char c = 0; c <= r; c++) {
      drawPixel(center+c, r+height, shapeColor);
      drawPixel(center-c, r+height, shapeColor);
    }
  }

  for(u_char c = 0; c < 45; c++) {
    for(u_char r = 12; r <= 45-c; r++) {
      drawPixel(center+c, r+height, shapeColor);
      drawPixel(center-c, r+height, shapeColor);
    }
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
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  /*drawing methods go in here*/
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      
      u_int switches = p2sw_read();
      
      if(switches & 256){
       	clearScreen(COLOR_WHITE);
	drawHeart(48,84,COLOR_RED);
	drawHeart(80,20,COLOR_BLUE);
	button = 1;
      }
      else if(switches & 512){
       	clearScreen(COLOR_PURPLE);
	button = 2;
      }
      else if(switches & 1024){
	button = 3;
       	clearScreen(COLOR_BLACK);
      }
      else if(switches & 2048){
      	button = 4;
      }
      drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_BLUE);
      redrawScreen = 0;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



