#ifndef HISTOGRAM
#define HISTOGRAM
#include "ImageV2.h"
#include <fstream>
#include <iomanip>

using namespace std;

class Histogram{
private:
	Image image;
	int val;
	int* aHistogram;
	int total;

public:
	//Histogram takes param on which image histogram should be applied too
	Histogram(Image image);
	//Makes the histogram choose value for range and channel for which channel of image should make a histogram
	void MakeAHistogram(int value, int channel);
	//returns histogram
	int * getHistogram();
	//returns total
	int getTotal();
	//saves the histogram with filenam
	void SaveHistogram(const char * filename);
};
#endif