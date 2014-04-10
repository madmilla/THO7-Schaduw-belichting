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
#include "basetimer.h"

using namespace ImageLib;
using namespace std;

int main(){
	shared_ptr<ImageRGB> img = loadImg("license_plate_ex_12.jpg");
	ImageRGB test(*img);
	ShadowTest st;
	
	BaseTimer bt;
	bt.start();
	Overexposure_Test OT;
	if (OT.Overexposure_Detection(img, 663, 617, 3873, 1361, 601, 1201, 3625, 2305) == true){
		/*cout << "overexposure\n";
		BaseTimer bt;
		bt.start();
		ColorSpace cs;
		cs.ToLAB(img, 601, 617, 3873, 2305);
		bt.stop();
		cout << bt.elapsedSeconds() << '\n';
		bt.reset();
		bt.start();
		OverExposure oe(*img);
		oe.Copy();
		//oe.ThresholdRepair(90, 20);
		oe.ThresholdRepair(90, 20, 601, 617, 3873, 2305);
		bt.stop();
		cout << bt.elapsedSeconds() << '\n';
		bt.reset();
		bt.start();
		ColorSpace cs2;
//		cs2.setA(cs.getA());
//		cs2.setB(cs.getB());
		//cs2.ToRGB();
		cs2.ToRGB(img, 601, 617, 3873, 2305);
		bt.stop();
		cout << bt.elapsedSeconds() << '\n';
		bt.reset();
		bt.start();
		//cs.Test();
		ImageRGB output(*img);
		bt.stop();
		cout << bt.elapsedSeconds();
		bt.reset();
		saveImg(output, "output1.jpg");*/
	}
	//shared_ptr<ImageRGB> img2 = loadImg("output1.jpg");
	//ImageRGB test2(*img2);
	bt.stop();
	cout << bt.elapsedSeconds();
	bt.reset();
	bt.start();
	if (st.Shadow_Detection(img, 663, 617, 3873, 1361, 601, 1201, 3625, 2305) == true){
		/*cout << "shadow\n";
		ColorSpace cs(test2);
		cs.Copy();
		//cs.ToLAB();
		cs.ToLAB(601, 617, 3873, 2305);
		OverExposure oe(*cs.getEditedImage());
		oe.Copy();
		//oe.ThresholdRepair(90, 20);
		oe.ThresholdRepairOpposite(20, 60, 90, 601, 617, 3873, 2305);
		ColorSpace cs2(*oe.getEditedImage());
//		cs2.setA(cs.getA());
//		cs2.setB(cs.getB());
		cs2.Copy();
		//cs2.ToRGB();
		cs2.ToRGB(601, 617, 3873, 2305);
		ImageRGB output(*cs2.getEditedImage());
		saveImg(output, "output2.jpg");*/
	}

	bt.stop();
	cout<<bt.elapsedSeconds();
	bt.reset();
	system("pause");
	saveImg(*img, "output.jpg");
	//system("pause");
}