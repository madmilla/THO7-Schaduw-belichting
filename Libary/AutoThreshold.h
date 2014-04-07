#ifndef AUTOTHRESHOLD_H
#define AUTOTHRESHOLD_H

#include "ImageV2.h"
#include "Filter.h"

class AutoThreshold : public Filter{
private:

public:
	//Constructor autothreshold
	//
	//input image which should be autothresholded
	AutoThreshold(Image img);
	//Calc thresholdvalue
	//
	//This functions calculates the threshold value
	void ThresholdCalc();
	//threshold image
	//
	//This functions threshold the input image with the value of threshold
	void Threshold(int threshold);
};
#endif