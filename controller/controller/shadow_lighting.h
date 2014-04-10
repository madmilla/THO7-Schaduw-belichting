#ifndef Shadow_Lighting_H
#define Shadow_Lighting_H
#define YELLOWGRAY 60
#include <memory>
#include <ImageLoader.h>
#include "shadowExceptions.h"
#include "ColorSpace.h"
#include "overexposure.h"

// File: shadow_lighting.h
// @Author Lars Veenendaal 1633223
// @Author Arthur van der Weiden
// 0.2 - Migration of tests,
// 0.1 - Skeleton setup
/*
	Still holds nothing.
*/
using namespace ImageLib;
using namespace std;

class Shadow_Lighting{
private:
	int DarkestFoundPixel = 0;
	bool FoundShadow = 0;
	int TotalPixels = 0;
	int Overexposed_pixels = 0;
	float percentage = 0;
	int sum = 0;
	int BigY, SmallY;
public:
	void checkForDefects(ImageRGB *, int i);
	void ApplyShadowFiltering();
	void ApplyLightingFiltering(ImageRGB *);
	// Shadow
	bool Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	inline void setDarkestFoundPixel(int value);
	inline int  getDarkestFoundPixel();
	// Overexposure
	bool Overexposure_Detection(ImageRGB * img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
};	//(std::shared_ptr<ImageRGB>
#endif

