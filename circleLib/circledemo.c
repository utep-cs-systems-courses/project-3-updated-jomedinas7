#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "abCircle.h"

AbRect rect10 = {abRectGetBounds, abRectCheck, {10,10}};; /**< 10x10 rectangle */

u_int bgColor = COLOR_BLUE;


Layer layer1 = {		/**< Layer with a red square */
  (AbShape *)&rect10,
  {screenWidth/2, screenHeight/2}, /**< center */
  {0,0}, {0,0},				    /* next & last pos */
  COLOR_RED,
  0
};

Layer layer0 = {		/**< Layer with an orange circle */
  (AbShape *)&circle20,
  {(screenWidth/2)/*+10*/, (screenHeight/2)/*+5*/}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* next & last pos */
  COLOR_RED,
  &layer1
};

Layer layer2 = {
  (AbShape *)&circle20,
  {(screenWidth/4), (screenHeight/2)
  },
  {0,0}, {0,0},
  COLOR_RED,
  &layer0
};

void drawDiamond(char center, u_int shapeColor)

{
  for(u_char r = 0; r < 11; r++) {
    for(u_char c = 0; c <= r; c++) {
      drawPixel(center+c, r+84, shapeColor);
      drawPixel(center-c, r+84, shapeColor);
    }
  }

  for(u_char c = 0; c < 42; c++) {
    for(u_char r = 10; r <= 40-c; r++) {
      drawPixel(center+c, r+84, shapeColor);
      drawPixel(center-c, r+84, shapeColor);
    }
  }
}  

int
main()
{
  configureClocks();
  lcd_init();

  clearScreen(COLOR_BLUE);
  

  layerDraw(&layer2);
  // layerDraw(&layer1);
  drawDiamond(48,COLOR_RED);
  drawString5x7(10,40, "Spread the love.", COLOR_GREEN, COLOR_RED);
}
