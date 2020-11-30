#include "lcdutils.h"
#include "lcddraw.h"
#include "abCircle.h"
#include "shape.h"

void drawHeart(char center,char height, u_int shapeColor)
{
  
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
