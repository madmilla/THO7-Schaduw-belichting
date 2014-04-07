#ifndef OVEREXPOSURE_H
#define OVEREXPOSURE_H
#include "ImageV2.h"
#include "Filter.h"
#include <math.h>
#include <iostream>

class OverExposure : public Filter{
private:
public:
	OverExposure(Image img);
	void M();
	void Threshold(int threshold);
	void ThresholdRepair(int threshold);
};
#endif