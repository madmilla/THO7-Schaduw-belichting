#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>
#include "ColorSpace.h"
#include "OverExposure.h"
#include "basetimer.h"

using namespace ImageLib;
using namespace std;

int main(){
	unique_ptr<ImageRGB> img = loadImg("license_plate_ex_5.jpg");
	ImageRGB test(*img);

	BaseTimer bttotal;
	BaseTimer bt;
	bttotal.start();
	bt.start();
	ColorSpace cs(test);
	cs.Copy();
	cs.ToLAB();
	//cs.ToLAB(145, 145, 605, 240);
	bt.stop();
	cout << bt.elapsedSeconds() << '\n';
	bt.reset();
	bt.start();
	OverExposure oe(*cs.getEditedImage());
	oe.Copy();
	oe.ThresholdRepair(90, 20);
	//oe.ThresholdRepair(90, 20, 145, 145, 605, 240);
	bt.stop();
	cout << bt.elapsedSeconds() << '\n';
	bt.reset();
	bt.start();
	ColorSpace cs2(*oe.getEditedImage());
	cs2.setA(cs.getA());
	cs2.setB(cs.getB());
	cs2.Copy();
	cs2.ToRGB();
	//cs2.ToRGB(149, 140, 605, 239);
	bt.stop();
	cout << bt.elapsedSeconds() << '\n';
	bt.reset();
	bttotal.stop();
	cout << bttotal.elapsedSeconds();
	ImageRGB output(*cs2.getEditedImage());
	saveImg(output, "output.jpg");
	system ("pause");
}