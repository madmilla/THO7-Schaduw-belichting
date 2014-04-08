// Arthur van der Weiden

#include "ShadowTest.h"

bool ShadowTest::ShadowSearch(std::string FileName, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY,
								int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY){
	int TopBigY, TopSmallY, BottomBigY, BottomSmallY;

	if (TopLeftY < TopRightY){
		TopBigY = TopRightY;
		TopSmallY = TopLeftY;
	}
	else {
		TopBigY = TopLeftY;
		TopSmallY = TopRightY;
	}if (BottomLeftY < BottomRightY){
		BottomBigY = BottomRightY;
		BottomSmallY = BottomLeftY;
	}
	else {
		BottomBigY = BottomLeftY;
		BottomSmallY = BottomRightY;
	}

	int LicensePlateWidth = BottomRightX;
	int LicensePlateHeight = BottomBigY;

	int TotalPixels = LicensePlateHeight * LicensePlateWidth;
	std::unique_ptr<ImageRGB> TestImage = loadImg(FileName);
	auto rgb_ptrs = TestImage->data(TopLeftX + 1, TopLeftY + 1);
	auto Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);
	int ShadowPixels = 0;
	auto Darkest = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);
	
	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);
			if ((int)Grayval < (int)Darkest){
				Darkest = Grayval;
			}
		}
	}

	for (int x = TopLeftX + 1; x <= LicensePlateWidth; x++){
		for (int y = TopSmallY + 1; y <= BottomBigY; y++){
			Grayval = (*rgb_ptrs.red * 0.21) + (*rgb_ptrs.blue * 0.71) + (*rgb_ptrs.green * 0.07);

			rgb_ptrs = TestImage->data(x, y);
			rgb_ptrs.red++;
			rgb_ptrs.blue++;
			rgb_ptrs.green++;	
			TestImage->at(x, y).blue = Grayval;
			TestImage->at(x, y).green = Grayval;
			TestImage->at(x, y).red = Grayval;
			
			if ((rgb_ptrs.blue > rgb_ptrs.green && rgb_ptrs.blue > rgb_ptrs.red) && (Grayval >= Darkest && Grayval <= 60)){
				ShadowPixels++;
				TestImage->at(x, y).blue = 0;
				TestImage->at(x, y).green = 0;
				TestImage->at(x, y).red = 255;
			}
		}
	}

	float percentage = ((float)ShadowPixels / (float)TotalPixels) * 100;
	if (percentage > 2.0f){
		FoundShadow = true;
	}
	std::cout << TopSmallY << std::endl;
	std::cout << BottomBigY << std::endl;
	std::cout << percentage << std::endl;
	saveImg(*TestImage, "Output.jpg");
	return FoundShadow;
}