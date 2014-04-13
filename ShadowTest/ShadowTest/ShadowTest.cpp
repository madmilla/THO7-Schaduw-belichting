// Arthur van der Weiden

#include "ShadowTest.h"

bool ShadowTest::Shadow_Detection(std::shared_ptr<ImageRGB> img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY,
								int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){

	int TopBigY, TopSmallY, BottomBigY, BottomSmallY;
	//! Bounding Box
	//! 
	//! These if statements calculates the bounding box of the license plate.
	//! The shadow check will be in the bounding box.
	if (TopLeftY < TopRightY){
		TopBigY = TopRightY;
		TopSmallY = TopLeftY;
	}else {
		TopBigY = TopLeftY;
		TopSmallY = TopRightY;
	}
	if (BottomLeftY < BottomRightY){
		BottomBigY = BottomRightY;
		BottomSmallY = BottomLeftY;
	}else {
		BottomBigY = BottomLeftY;
		BottomSmallY = BottomRightY;
	}

	int LicensePlateWidth = BottomRightX;
	int LicensePlateHeight = BottomBigY - TopSmallY;

	int TotalPixels = LicensePlateHeight * LicensePlateWidth;
	float percentage;
	int ShadowPixels = 0;
	auto rgb_ptrs = img->data(TopLeftX + 1, TopLeftY + 1);
	auto Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);
	auto Darkest = Grayval;
	setDarkestFoundPixel(Darkest);
	
	//! Darkest pixel
	//!
	//! To find the bottom threshold for the shadow detection,
	//! the algorithm loops through the picture in search of the darkest pixel.
	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);

			if ((int)Grayval < (int)Darkest){
				Darkest = Grayval;
				setDarkestFoundPixel(Darkest);
			}
		}
	}
	//! Shadow search
	//! 
	//! When a pixel is considered as a shadowpixel, a counter will be added.
	//! When a percentage of 2% shadow pixels is reached the function will return true, else it will return false.
	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);

			rgb_ptrs.red++;
			rgb_ptrs.blue++;
			rgb_ptrs.green++;	
			
			if (((rgb_ptrs.blue > rgb_ptrs.green) && (rgb_ptrs.blue > rgb_ptrs.red)) && (Grayval >= Darkest && Grayval <= YELLOWGRAY)){
				ShadowPixels++;
				img->at(x, y).red = 255;
				img->at(x, y).green = 0;
				img->at(x, y).blue = 0;
			}
			percentage = ((float)ShadowPixels / (float)TotalPixels) * 100;
			if (percentage > 2.0f){	
				return true;
			}
		}
	}
	return false;
	
}
void ShadowTest::setDarkestFoundPixel(int value){
	DarkestFoundPixel = value;
}