#ifndef COLORFILTER_H
#define COLORFILTER_H
#include "ImageV2.h"
#include "Filter.h"

class ColorFilter: public Filter{
private:
public:
	//input image, constructor colorfilter
	ColorFilter(Image img);
	//'make image red
	void makeRed();
	//make image green
	void makeGreen();
	//make image blue
	void makeBlue();
	//make image grey
	void makeGrey();
};
#endif