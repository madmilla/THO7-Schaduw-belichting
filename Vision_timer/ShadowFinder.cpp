//Arthur van der Weiden

#include "ShadowFinder.h"
ShadowFinder::ShadowFinder(){
}

bool ShadowFinder::ShadowTest(Image& img){
	int PixelVal = 0, NextPixelVal = 0, PrevPixelVal = 0;
	Image destinationImage("Test.jpg", img.GetWidth(), img.GetHeight());

	for (int y = 0; y <= img.GetHeight() - 1; y++){
		for (int x = 0; x <= img.GetWidth() - 1; x++){
			PrevPixelVal = img.GetPixel((x - 1) % img.GetWidth(), (y - 1) % img.GetHeight());
			PixelVal = img.GetPixel(x, y);
			NextPixelVal = img.GetPixel((x + 1) % img.GetWidth(), (y + 1) % img.GetHeight());
			if (PrevPixelVal > PixelVal && NextPixelVal <= PixelVal && PixelVal >= 0) {
				destinationImage.SetPixel(x, y, PixelVal);
				return true;
			}
		}
		
	}
	return false;
	destinationImage.SaveImageToFile("OUTPUT_");
}