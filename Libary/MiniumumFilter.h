#ifndef MINFILTER_H
#define MINFILTER_H
#include "Filter.h"

class MinFilter : public Filter{
public:
	//Constructor MinFiltering
	//
	//Constructor will automaticly call filterHistogram and will apply Min filtering on the image img.
	MinFilter(Image img, int value);
	//MinFiltering based on histogram
	//
	//This function will use a histogram to calculate and apply a Min filter
	//Value is the size of the mask.
	void FilterHistogram(int value);
};
#endif