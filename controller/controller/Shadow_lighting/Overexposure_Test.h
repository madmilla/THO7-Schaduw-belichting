#ifndef OVEREXPOSURE_TEST
#define OVEREXPOSURE_TEST

#include <ImageLoader.h>

using namespace ImageLib;

class Overexposure_Test{
public:
	Overexposure_Test();
	bool Overexposure_Detection(ImageRGB img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	void Overexposure_Removal(ImageRGB img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
};
#endif