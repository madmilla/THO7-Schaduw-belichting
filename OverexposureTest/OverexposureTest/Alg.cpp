#include "Alg.h"

#include <ImageLoader.h>

using namespace ImageLib;
using namespace std;

int TotalPixels = 0;
int Overexposed_pixels = 0;
float percentage = 0;
int sum = 0;
int BigY, SmallY;

Overexposure_Test::Overexposure_Test(){
	
}

bool Overexposure_Test::Overexposure_Detection(shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	if (TopLeftY < TopRightY){
		SmallY = TopLeftY;
	}
	else{
		SmallY = TopRightY;
	}
	
	if (BottomLeftY > BottomRightY){
		BigY = BottomLeftY;
	}
	else{
		BigY = BottomRightY;
	}

	TotalPixels = (BottomRightX - TopLeftX) * (BigY - SmallY);
	for (int y = SmallY + 5; y < BigY - 5; y++){
		for (int x = TopLeftX + 5; x < BottomRightX - 5; x++){
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue* 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue* 2 - *img->data(x - 1, y + 1).blue;
			
			sum = abs(xGradient) + abs(yGradient);

			if (sum > 255){
				sum = 255;
			}
			else if (sum < 0){
				sum = 0;
			}

			if (sum >= 255){
				percentage = ((float)Overexposed_pixels / (float)TotalPixels) * 100;

				if (percentage >= 1){
					return true;
				}
				for (int h = y - 10; h < y + 10; h++){
					for (int w = x - 10; w < x + 10; w++){
						if ((*img->data(w, h).blue > 210) &&  (*img->data(w, h).green > 200) && (*img->data(w, h).red > 200)){	
							Overexposed_pixels++;
						}
					}
				}
			}	
		}
	}
	return false;
}
