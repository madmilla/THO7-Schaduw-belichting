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
#include "RemoveLight.h"

using namespace ImageLib;
using namespace std;




/*int * coordinates(std::vector<int, int> TopLeft, std::vector<int, int> TopRight, std::vector<int, int> BottomLeft, std::vector<int, int> BottomRight){
	int * returnCoordinates = new int[4];
	//returnCoordinates[0] = (TopLeft. > TopRight) ?  : (var_R * 12.92);
	return returnCoordinates;
}*/

int main(){
	shared_ptr<ImageRGB> img = loadImg("license_plate_81.jpg");
	ImageRGB test(*img);
	ShadowTest st;

	/*std::vector<int, int> TopLeft = { 663, 617 };
	std::vector<int, int> TopRight = { 3873, 1361 };
	std::vector<int, int> BottomLeft = { 601, 1201 };
	std::vector<int, int> BottomRight = { 3625, 2305 };*/
	
	BaseTimer bt;
	//bt.start();
	Overexposure_Test OT;
	if (OT.Overexposure_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) == true){
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
	if (st.Shadow_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) == true){
		RemoveLight rl;
		rl.Remove(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630);
		//testert(img, 1796, 1447, 2580, 1692, st.getDarkestFoundPixel());
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
