// Arthur van der Weiden

#include "Image.h"
#include <string>

#define YELLOWGRAY 50
#define BLACKGRAY 200
#define SHADOWMARGE 30

class ShadowFinder{

public:
	ShadowFinder();
	bool ShadowTest(Image& Img, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
	struct coordinate{
		int x, y;
	};
};