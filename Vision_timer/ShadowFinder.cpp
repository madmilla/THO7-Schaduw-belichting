//Arthur van der Weiden
//7-4-2014

#include "ShadowFinder.h"
ShadowFinder::ShadowFinder(){
	
}

bool ShadowFinder::ShadowTest(Image& Img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, 
								int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY ){
	
	int LicenseplateWidth = TopRightX, LicenseplateHeight = BottomLeftY;
	int Width = Img.GetWidth();
	int Height = Img.GetHeight();
	int PixelData = Img.GetPixel(TopLeftX, TopLeftY);
	int GrayValue, PrevPrevGrayValue, PrevGrayValue, NextGrayValue;
	int totalPixels = LicenseplateHeight * LicenseplateWidth;
	Image outputImage("Test.jpg", Width, Height);

	int i = 0;
	for (int y = TopLeftY ; y <= LicenseplateHeight; y++){
		for (int x = TopLeftX + 2; x <= LicenseplateWidth; x++){
			outputImage.SetPixel(x, y, Img.GetPixel(x, y));
			PrevPrevGrayValue = (int)((Img.GetPixelRed((x - 2) % LicenseplateWidth, y) * 0.30)
				+ (Img.GetPixelGreen((x - 2) % LicenseplateWidth, y) * 0.59)
				+ (Img.GetPixelBlue((x - 2) % LicenseplateWidth, y) * 0.11));
			PrevGrayValue = (int)((Img.GetPixelRed((x - 1) % LicenseplateWidth, y) * 0.30)
				+ (Img.GetPixelGreen((x - 1) % LicenseplateWidth, y) * 0.59)
				+ (Img.GetPixelBlue((x - 1) % LicenseplateWidth, y) * 0.11));
			GrayValue = (int)((Img.GetPixelRed(x, y) * 0.30) + (Img.GetPixelGreen(x, y) * 0.59) + (Img.GetPixelBlue(x, y) * 0.11));
			NextGrayValue = (int)((Img.GetPixelRed((x + 1) % LicenseplateWidth, y) * 0.30)
				+ (Img.GetPixelGreen((x + 1) % LicenseplateWidth, y) * 0.59)
				+ (Img.GetPixelBlue((x + 1) % LicenseplateWidth, y) * 0.11));
			if (NextGrayValue < BLACKGRAY){
				if ( abs(PrevPrevGrayValue - PrevGrayValue) < SHADOWMARGE){
					if (abs(GrayValue - PrevGrayValue) > SHADOWMARGE && abs(NextGrayValue - GrayValue) < SHADOWMARGE){
						i++;
						outputImage.SetPixel(x, y, (255 << redPixelShift) | (0 << greenPixelShift) | (0 << bluePixelShift));
					}
				}
			}
		PixelData = Img.GetPixel(x, y);
		}
	}	
	std::cout << i << std::endl;
	std::cout << totalPixels << std::endl;

	outputImage.SaveImageToFile("OUTPUT_");
	if (i < totalPixels / totalPixels * 2){
		std::cout << "false" << std::endl;
		return false;
	}
	else {
		std::cout << "true" << std::endl;
		return true;
	}

	
}