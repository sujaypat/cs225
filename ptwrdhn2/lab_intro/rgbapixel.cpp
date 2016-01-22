#include "rgbapixel.h"

RGBAPixel::RGBAPixel(){
  red = 0xFF;
  green = 0xFF;
  blue = 0xFF;
}
RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b){
  red = r;
  green = g;
  blue = b;
}
