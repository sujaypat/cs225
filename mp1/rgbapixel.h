#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H
//using std::uint8_t;
class RGBAPixel
{
	public: 
		RGBAPixel();
		RGBAPixel(unsigned char red, unsigned char green, unsigned char blue);
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;
};

#endif
