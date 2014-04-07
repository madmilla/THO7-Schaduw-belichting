#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H
#include "Filter.h"

class MedianFilter: public Filter{
public:
	//Constructor MedianFiltering
	//
	//Constructor will automaticly call filterHistogram and will apply median filtering on the image img.
	MedianFilter(Image img, int value);
	//MedianFiltering based on histogram
	//
	//This function will use a histogram to calculate and apply a median filter
	//Value is the size of the mask.
	void FilterHistogram(int value);
};
#endif