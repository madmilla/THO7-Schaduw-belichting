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


void testert(std::shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY, int value){
	/*int meanRTopL = 0;
	int meanGTopL = 0;
	int meanBTopL = 0;


	for (int y = TopLeftY; y < TopLeftY + 3; y++){
		auto samples = image->data(TopLeftX, y);
		for (int x = TopLeftX; x < TopLeftX + 3; x++){
			meanRTopL += *samples.red;
			meanGTopL += *samples.green;
			meanBTopL += *samples.blue;
			samples.red++;
			samples.green++;
			samples.blue++;
		}
	}
	meanRTopL /= 9;
	meanGTopL /= 9;
	meanBTopL /= 9;

	int meanRTopR = 0;
	int meanGTopR = 0;
	int meanBTopR = 0;

	
	for (int y = TopRightY; y < TopLeftY + 3; y++){
		auto samples = image->data(TopRightX, y);
		for (int x = TopRightX; x < TopLeftX + 3; x++){
			meanRTopL += *samples.red;
			meanGTopL += *samples.green;
			meanBTopL += *samples.blue;
			samples.red--;
			samples.green--;
			samples.blue--;
		}
	}
	meanRTopR /= 9;
	meanGTopR /= 9;
	meanBTopR /= 9;

	int meanRBottomL = 0;
	int meanGBottomL = 0;
	int meanBBottomL = 0;

	for (int y = BottomLeftY; y > BottomLeftY - 3; y--){
		auto samples = image->data(BottomLeftX,y);
		for (int x = BottomLeftX; x < BottomLeftX + 3; x++){
			meanRBottomL += *samples.red;
			meanGBottomL += *samples.green;
			meanBBottomL += *samples.blue;
			samples.red++;
			samples.green++;
			samples.blue++;
		}
	}
	meanRBottomL /= 9;
	meanGBottomL /= 9;
	meanBBottomL /= 9;

	int meanRBottomR = 0;
	int meanGBottomR = 0;
	int meanBBottomR = 0;

	for (int y = BottomRightY; y > BottomRightY - 3; y--){
		auto samples = image->data(BottomRightX, y);
		for (int x = BottomRightX; x < BottomRightX + 3; x++){
			meanRBottomR += *samples.red;
			meanGBottomR += *samples.green;
			meanBBottomR += *samples.blue;
			samples.red--;
			samples.green--;
			samples.blue--;
		}
	}
	meanRBottomR /= 9;
	meanGBottomR /= 9;
	meanBBottomR /= 9;
		

	//float Rx = (float)*rgb_ptrs.red / 255;
	//float Gx = (float)*rgb_ptrs.green / 255;
	//float Bx = (float)*rgb_ptrs.blue / 255;
	//float test = max(Rx, Gx);
	//float K = 1 - max(test, Bx);
	//float Y = (1 - Bx - K) / (1 - K);
	*/

	//some easy and ugly max and min

	int tempA = max(TopLeftX, TopRightX);
	int tempB = max(BottomLeftX, BottomRightX);
	int xmax  = max(tempA, tempB);
	tempA	  = min(TopLeftX, TopRightX);
	tempB	  = min(BottomLeftX, BottomRightX);
	int xmin = min(tempA, tempB);

	tempA = max(TopLeftY, TopRightY);
	tempB = max(BottomLeftY, BottomRightY);
	int ymax = max(tempA, tempB);
	tempA = min(TopLeftY, TopRightY);
	tempB = min(BottomLeftY, BottomRightY);
	int ymin = min(tempA, tempB);

	int yellowLastYValue = 0;
	int yellowLastKValue = 0;
	int blackLastYValue = 0;
	int blackLastKValue = 0;
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
			/*if (Y < 0.5){
				Y = 1;
			}*/
			/*if (Y > 0.5 && K < 0.5){
				Y = 1;
				K = 0;
			*/
			
			if (K < 0.1 && Y > 0.1){ //geel
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
				yellowLastYValue = Y;
				yellowLastKValue = K;
			}
			else if (K < 0.05 && Y < 0.1 && C < 0.1 && M < 0.1){ //wit
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}
			else if (K < 0.5 && Y < 0.1){
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
				blackLastKValue = K;
				blackLastYValue = Y;
			}
			else if (K > 0.5 && Y < 0.2){
				C = 0;
				M = 0;
				Y = 0;
				K = 1;
				blackLastKValue = K;
				blackLastYValue = Y;
			}
			else if (K < 0.4 && Y > 0.95){
				C = 0;
				M = 0;
				Y = 1;
				K = 0;
			}

			*rgb_ptrs.red = 255 * (1 - C) * (1 - K);
			*rgb_ptrs.green = 255 * (1 - M) * (1 - K);
			*rgb_ptrs.blue = 255 * (1 - Y) * (1 - K);
		}
	}
}

/*int * coordinates(std::vector<int, int> TopLeft, std::vector<int, int> TopRight, std::vector<int, int> BottomLeft, std::vector<int, int> BottomRight){
	int * returnCoordinates = new int[4];
	//returnCoordinates[0] = (TopLeft. > TopRight) ?  : (var_R * 12.92);
	return returnCoordinates;
}*/

int main(){
	shared_ptr<ImageRGB> img = loadImg("license_plate_ex_5.jpg");
	ImageRGB test(*img);
	ShadowTest st;

	/*std::vector<int, int> TopLeft = { 663, 617 };
	std::vector<int, int> TopRight = { 3873, 1361 };
	std::vector<int, int> BottomLeft = { 601, 1201 };
	std::vector<int, int> BottomRight = { 3625, 2305 };*/
	
	BaseTimer bt;
	//bt.start();
	Overexposure_Test OT;
	if (OT.Overexposure_Detection(img, 145, 145, 605, 137, 155, 240, 605, 235) == true){
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
	if (st.Shadow_Detection(img, 145, 145, 605, 137, 155, 240, 605, 235) == true){
		testert(img, 145, 145, 605, 137, 155, 240, 605, 235, st.getDarkestFoundPixel());
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
