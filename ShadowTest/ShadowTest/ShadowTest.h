// Arthur van der Weiden

#ifndef SHADOW_TEST
#define SHADOW_TEST

#include <ImageLoader.h>
#define YELLOWGRAY 60

using namespace ImageLib;

class ShadowTest{

private:
	
	bool FoundShadow = 0;
	int BigY, SmallY;
	int tempRed2 = 0, tempRed = 0, tempBlue = 0, tempBlue2 = 0, tempGreen = 0, tempGreen2 = 0, temp_aantal = 0, red = 0, blue = 0, green = 0;
	int sum;
	int DarkestFoundPixel = 0;
	float percentage;
	int ShadowPixels = 0;

public:

	ShadowTest(){}
	bool Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	
	inline int getDarkestFoundPixel(){
		return DarkestFoundPixel;
	}

	inline void setDarkestFoundPixel(int value);
};
#endif