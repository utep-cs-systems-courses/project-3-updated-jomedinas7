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


short redrawScreen = 1;

static char button = 0;
u_int bgColor = COLOR_WHITE; 
char heart_state = 0;

/*board methods go in here*/
void wdt_c_handler()
{
   u_int switches = p2sw_read();
   if(switches & 256){
       	clearScreen(COLOR_WHITE);
	switch(heart_state){
	case(2):
	  drawHeart(48,84,COLOR_RED);
	  break;
	case(4):
	  drawHeart(80,20,COLOR_BLUE);
	  break;
	case(6):
	  drawHeart(50,50,COLOR_PURPLE);
	  break;
	case(8):
	  heart_state = 0;
	  break;
	}
	heart_state++;
	button = 1;
      }
      else if(switches & 512){
       	clearScreen(COLOR_PURPLE);
	button = 2;
      }
      else if(switches & 1024){
	button = 3;
      }
      else if(switches & 2048){
      	button = 4;
      }

  static int secCount = 0;  
  if(++secCount!= 250){
    // secCount =0;
    switch(button){
    case(1):
      redrawScreen = 1;
      break;
    case(2):
      redrawScreen = 1;
      play_song();
      break;
    case(3):
      assyNoteScale();
      drawString8x12(20,20,"Goodbye!", COLOR_WHITE,COLOR_BLACK);
      redrawScreen = 1;
      break;
    case(4):
      redrawScreen = 1;
      state_advance();
      buzzer_set_period(0);
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
  // char heart_state = 0;
  //u_int switches = p2sw_read();
  /*drawing methods go in here*/
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;      
      // u_int switches = p2sw_read();
      
      /* if(switches & 256){
       	clearScreen(COLOR_WHITE);
	switch(heart_state){
	case(2):
	  drawHeart(48,84,COLOR_RED);
	  break;
	case(4):
	  drawHeart(80,20,COLOR_BLUE);
	  break;
	case(6):
	  drawHeart(50,50,COLOR_PURPLE);
	  break;
	case(8):
	  heart_state = 0;
	  break;
	}
	heart_state++;
	//button = 1;
      }
      else if(switches & 512){
       	clearScreen(COLOR_PURPLE);
	button = 2;
      }
      else if(switches & 1024){
	button = 3;
	// 	clearScreen(COLOR_BLACK);
      }
      else if(switches & 2048){
      	button = 4;
	}*/
      drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_BLUE);
      // redrawScreen = 0;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



