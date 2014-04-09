// Arthur van der Weiden

#ifndef SHADOW_TEST
#define SHADOW_TEST

#include <ImageLoader.h>
#define YELLOWGRAY 60

using namespace ImageLib;

class ShadowTest{

private:
	
	bool FoundShadow = 0;

public:

	ShadowTest(){}
	bool Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);

};
#endif