//Arthur van der Weiden

#include "ShadowFinder.h"
ShadowFinder::ShadowFinder(){
}

bool ShadowFinder::ShadowTest(Image& img){
	bool found = false;
	bool done = false;
	Image destinationImage("test.png", 5, 5);

	for (int y = 0; y < img.GetHeight(); y++){
		for (int x = 0; x < img.GetWidth(); x++){
			int PixelVal = (int)((img.GetPixelRed(x, y) * 0.30) + (img.GetPixelGreen(x, y) * 0.59) + (img.GetPixelBlue(x, y) * 0.11));
			destinationImage.SetPixel(x, y, (PixelVal << redPixelShift) | (PixelVal << greenPixelShift) | (PixelVal << bluePixelShift));
			//std::cout << PixelVal << ' ' << x << ' ' << y << std::endl;
		}
	}
	destinationImage.SaveImageToFile("test_");
	
	return found;
}