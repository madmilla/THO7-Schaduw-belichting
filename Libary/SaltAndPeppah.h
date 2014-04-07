#ifndef SALTANDPEPPER_H
#define SALTANDPEPPER_H
#include "ImageV2.h"
#include "Filter.h"
#include <fstream>
#include <iomanip>
using namespace std;

class SaltAndPepper: public Filter{
private:
	int percentage;
public:
	//percentage of noise and image are params to add salt and pepper
	SaltAndPepper(Image img, int per);
	//set noise percentage
	void setNoise(int per);
	//returns percentage
	int getPercentage();
};
#endif