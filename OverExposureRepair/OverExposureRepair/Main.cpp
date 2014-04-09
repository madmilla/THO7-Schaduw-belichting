#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>
#include "ColorSpace.h"
#include "OverExposure.h"

using namespace ImageLib;
using namespace std;

int main(){
	unique_ptr<ImageRGB> img = loadImg("DSC_0006.jpg");
	ImageRGB test(*img);
	cout<<img->height();
	ColorSpace cs(test);

	cs.ToLAB();
	OverExposure oe(*cs.getEditedImage());
	oe.ThresholdRepair(90, 20);
	ColorSpace cs2(*oe.getEditedImage());
	cs2.setA(cs.getA());
	cs2.setB(cs.getB());
	cs2.ToRGB();

	ImageRGB output(*cs2.getEditedImage());
	saveImg(output, "output.jpg");
}