#include "Filter.h"
#include "Histogram.h"

class EqualizeFilter :public Filter{
public:
	EqualizeFilter(Image img);

	//Equalize the image
	//
	//The image will be equalized when using this function.
	//Therefor is a equalized histogram needed which should be given by param.
	//Value is range of colors. If it's 0-255, 256 is the range.
	//Total is the total of the values of the histogram.
	//Channel determinates which channel should be equalized.
	void EqualizeImage(int * histogram, int range, int total, int channel);


	//Equalize the image
	//
	//The image will be equalized when using this function. 
	//Therefor is not equalized histogram needed this will be created inside this function using the value for the size of the histogram. 256 will be used for range
	//All channels will be equalized
	void Equalize(int range);
};