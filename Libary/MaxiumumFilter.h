#ifndef MAXFILTER_H
#define MAXFILTER_H
#include "Filter.h"

class MaxFilter : public Filter{
public:
	//Constructor MaxFiltering
	//
	//Constructor will automaticly call filterHistogram and will apply Max filtering on the image img.
	MaxFilter(Image img, int value);
	//MaxFiltering based on histogram
	//
	//This function will use a histogram to calculate and apply a Max filter
	//Value is the size of the mask.
	void FilterHistogram(int value);
};
#endif