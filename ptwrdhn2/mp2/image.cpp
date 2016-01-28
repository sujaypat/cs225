#include "image.h"

void Image::flipleft(){

  int width = (*this).width();
  int height = (*this).height();
  RGBAPixel currPix;

  for(int i = 0; i < width / 2; i++){
    for(int j = 0; j < height; j++){
	
      currPix = *(*this)(i, j);
      *(*this)(i, j) = *(*this)(width - 1 - i, j);
      *(*this)(width - 1 - i, j) = currPix;

    }
    
  }

}

void Image::adjustbrightness(int r, int g, int b){

  int width = (*this).width();
  int height = (*this).height();

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
	
      RGBAPixel *currPix = (*this)(i,j);
      currPix->red = currPix->red + r > 255 ? 255 : currPix->red + r < 0 ? 0 : currPix->red + r; 
      currPix->green = currPix->green + g > 255 ? 255 : currPix->green + g < 0 ? 0 : currPix->green + g; 
      currPix->blue = currPix->blue + b > 255 ? 255 : currPix->blue + b < 0 ? 0 : currPix->blue + b;

    }
   
  }

}

void Image::invertcolors(){
    
  int width = this->width();
  int height = this->height();
    
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){

      RGBAPixel *currPix = (*this)(i,j);
      currPix->red = 255-currPix->red;
      currPix->green = 255-currPix->green;
      currPix->blue = 255-currPix->blue;

    }

  }

}
