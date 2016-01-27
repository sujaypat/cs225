#IFNDEF IMAGE_H
#DEFINE IMAGE_H
#include <cstdint>
#include <iostream>
class Image{

 public:
  void flipleft();
  void adjustbrightness(int r, int g, int b);
  void invertcolors();


};

#endif
