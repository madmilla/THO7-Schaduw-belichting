//!@author Arthur van der Weiden 1619815

#ifndef SHADOW_TEST
#define SHADOW_TEST

#include <ImageLoader.h>
#define YELLOWGRAY 60

using namespace ImageLib;

class ShadowTest{

private:
	int TotalPixels;
	int LicensePlateHeight;
	int LicensePlateWidth;
	int TopBigY, TopSmallY, BottomBigY, BottomSmallY;
	int DarkestFoundPixelR, DarkestFoundPixelG, DarkestFoundPixelB;
	int DarkestFoundPixel = 0;
	float Percentage;
	int ShadowPixels = 0;

public:
	//! Constructor
	//! 
	//! Constructs an object of the ShadowTest type
	ShadowTest(){ DarkestFoundPixelR = 0; DarkestFoundPixelG = 0; DarkestFoundPixelB = 0; }
	
	//! Shadow_Detection
	//! @param img, TopLeftX, TopLeftY, TopRightX, TopRightY, BottomLeftX, BottomLeftY, BottomRightX, BottomRightY, the image and coordinates within which will be tested
	//!
	//! Detects whether an image has shadow in it.
	//! The image will be tested within the coordinates passed through the parameters.
	bool Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	
	//! getDarkestFoundPixel
	//!
	//! Returns the darkest found pixel
	inline int getDarkestFoundPixel(){
		return DarkestFoundPixel;
	}
	
	//! setDarkestFoundPixel
	//! @param value the new value for the darkest found pixel
	//! 
	//! Sets the darkest found pixel to the value passed through the parameter
	inline void setDarkestFoundPixel(int value);

	//! getDarkestFoundPixelR
	//!
	//! Returns the darkest found pixel the red value
	inline int getDarkestFoundPixelR(){
		return DarkestFoundPixelR;
	}
	//! getDarkestFoundPixelG
	//!
	//! Returns the darkest found pixel the green value
	inline int getDarkestFoundPixelG(){
		return DarkestFoundPixelG;
	}
	//! getDarkestFoundPixelB
	//!
	//! Returns the darkest found pixel the blue value
	inline int getDarkestFoundPixelB(){
		return DarkestFoundPixelB;
	}
};
#endif