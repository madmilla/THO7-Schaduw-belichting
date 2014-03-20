// Arthur van der Weiden

#include "Image.h"
#include <string>

class ShadowFinder{

	Image* img;
	std::string filename;

	ShadowFinder(std::string filename);
	bool ShadowTest(Image& img);

};