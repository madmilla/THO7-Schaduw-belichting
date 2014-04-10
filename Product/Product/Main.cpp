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


void testert(std::shared_ptr<ImageRGB> image, int xmin, int ymin, int xmax, int ymax, int value){
	for (int y = ymin; y < ymax; y++){
		for (int x = xmin; x < xmax; x++){
			auto rgb_ptrs = image->data(x, y);
			float Rx = (float)*rgb_ptrs.red / 255;
			float Gx = (float)*rgb_ptrs.green / 255;
			float Bx = (float)*rgb_ptrs.blue / 255;
			float test = max(Rx, Gx);
			float K = 1 - max(test, Bx);
			float C = (1 - Rx-K) / (1-K);
			float M = (1 - Gx-K) / (1-K);
			float Y = (1 - Bx-K) / (1-K);
			if (Y < 0.5){
				Y = 0.5;
			}
			//cout << (int)*rgb_ptrs.red << "\n";
			*rgb_ptrs.red = 255 * (1 - C) * (1 - K);
			*rgb_ptrs.green = 255 * (1 - M) * (1 - K);
			*rgb_ptrs.blue = 255 * (1 - Y) * (1 - K);
			//cout << (int)*rgb_ptrs.red << "\n\n";
		}
	}
}

/*int * coordinates(std::vector<int, int> TopLeft, std::vector<int, int> TopRight, std::vector<int, int> BottomLeft, std::vector<int, int> BottomRight){
	int * returnCoordinates = new int[4];
	//returnCoordinates[0] = (TopLeft. > TopRight) ?  : (var_R * 12.92);
	return returnCoordinates;
}*/

int main(){
	shared_ptr<ImageRGB> img = loadImg("license_plate_ex_12.jpg");
	ImageRGB test(*img);
	ShadowTest st;

	/*std::vector<int, int> TopLeft = { 663, 617 };
	std::vector<int, int> TopRight = { 3873, 1361 };
	std::vector<int, int> BottomLeft = { 601, 1201 };
	std::vector<int, int> BottomRight = { 3625, 2305 };*/
	
	BaseTimer bt;
	//bt.start();
	Overexposure_Test OT;
	if (OT.Overexposure_Detection(img, 663, 617, 3873, 1361, 601, 1201, 3625, 2305) == true){
		cout << "overexposure\n";
		/*BaseTimer bt;
		bt.start();
		ColorSpace cs;
		//cs.ToLAB(img, 601, 617, 3873, 2305);
		cs.ToLAB(img, 601, 617, 3873, 2305);
		bt.stop();
		cout << bt.elapsedSeconds() << '\n';
		bt.reset();
		bt.start();
		OverExposure oe;
		oe.ThresholdRepair(img, 90, 20, 601, 617, 3873, 2305);
		bt.stop();
		cout << bt.elapsedSeconds() << '\n';
		bt.reset();
		bt.start();
		cs.ToRGB(img, 601, 617, 3873, 2305);
		bt.stop();
		cout << bt.elapsedSeconds() << '\n';
		bt.reset();
		bt.start();
		bt.stop();
		cout << bt.elapsedSeconds();
		bt.reset();
		saveImg(*img, "output1.jpg");*/
	}
	//shared_ptr<ImageRGB> img2 = loadImg("output1.jpg");
	//ImageRGB test2(*img2);
	bt.stop();
	cout << bt.elapsedSeconds();
	bt.reset();
	bt.start();
	if (st.Shadow_Detection(img, 663, 617, 3873, 1361, 601, 1201, 3625, 2305) == true){
		testert(img, 601, 617, 3873, 2305, st.getDarkestFoundPixel());
		cout << "shadow\n";
		/*ColorSpace cs(test2);
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
	cout << "\nhoi"<< st.getDarkestFoundPixel() << "\n";
	bt.stop();
	cout << bt.elapsedSeconds();
	bt.reset();
	system("pause");
	saveImg(*img, "output.jpg");
}
