#ifndef NEIGHBOORHOODFILTER_H
#define NEIGHBOORHOODFILTER_H
#include "ImageV2.h"
#include "Filter.h"

class NeighboorhoodFilter : Filter{
protected:
	unsigned int kernel;
	int xOffset;
	int yOffset;
public:
	NeighboorhoodFilter(Image img);
	void NeighboorhoodConvert(int value, int xOffset, int yOffset);
};
#endif