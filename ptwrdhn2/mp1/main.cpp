#include "png.h"

int main(){

	PNG img("in.png");
	int width = img.width();
	int height = img.height();

	PNG res(width, height);

	for (int i = 0; i < width; ++i){
		for (int j = 0; j < height; ++j){
			RGBAPixel out = *img(width-i-1,height-j-1);
			res(i,j)->red = out.red;
			res(i,j)->green = out.green;
			res(i,j)->blue = out.blue;
			res(i,j)->alpha = out.alpha;
		}
	}
	res.writeToFile("out.png");



	return 0;
}