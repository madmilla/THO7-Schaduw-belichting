#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>
#include "ColorSpace.h"
#include "OverExposure.h"
#include "ShadowTest.h"
#include "Alg.h"

using namespace ImageLib;
using namespace std;

int main(){
	shared_ptr<ImageRGB> img = loadImg("license_plate_8.jpg");
	ImageRGB test(*img);
	ShadowTest st;
	if (st.Shadow_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) == true){
		cout << "shadow\n";
	}
	Overexposure_Test OT;
	if(OT.Overexposure_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) == true){
		cout << "overexposure\n";
		ColorSpace cs(test);
		cs.Copy();
		//cs.ToLAB();
		cs.ToLAB(1796, 1447, 2580, 1692);
		OverExposure oe(*cs.getEditedImage());
		oe.Copy();
		//oe.ThresholdRepair(90, 20);
		oe.ThresholdRepair(90, 20, 1796, 1447, 2580, 1692);
		ColorSpace cs2(*oe.getEditedImage());
		cs2.setA(cs.getA());
		cs2.setB(cs.getB());
		cs2.Copy();
		//cs2.ToRGB();
		cs2.ToRGB(1796, 1447, 2580, 1692);
		ImageRGB output(*cs2.getEditedImage());
		saveImg(output, "output1.jpg");
	}



	saveImg(*img, "output.jpg");
}