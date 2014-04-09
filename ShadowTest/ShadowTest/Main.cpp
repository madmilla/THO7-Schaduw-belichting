#include <iostream>
#include <ImageLoader.h>
#include "ShadowTest.h"
#include "BaseTimer.h"

using namespace ImageLib;
using namespace std;

int main(){	
	ShadowTest shadow;
	shared_ptr<ImageRGB> TestImage = loadImg("license_plate_8.jpg");
	BaseTimer bt;
	bt.start();
	cout << shadow.Shadow_Detection(TestImage, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) << endl;
	//cout << shadow.Shadow_Detection(TestImage, 145, 145, 605, 145, 155, 240, 605, 235) << endl;
	bt.stop();
	cout << bt.elapsedSeconds() << endl;
	cin.ignore();
}

//cout << shadow.ShadowSearch("license_plate_1.jpg",	298, 39, 1441, 236);
//cout << shadow.ShadowSearch("license_plate_2.jpg",	659, 701, 992, 778);
//cout << shadow.ShadowSearch("license_plate_3.jpg",	341, 354, 562, 410);
//cout << shadow.ShadowSearch("license_plate_4.jpg",	928, 582, 1087, 614);
//cout << shadow.ShadowSearch("license_plate_5.jpg",	212, 281, 382, 318);
//cout << shadow.ShadowSearch("license_plate_6.jpg",	1377, 1473, 2224, 1509);
//cout << shadow.ShadowSearch("license_plate_7.jpg",	398, 388, 1193, 537);
//cout << shadow.ShadowSearch("license_plate_8.jpg",	1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630);
//cout << shadow.ShadowSearch("license_plate_9.jpg",	108, 191, 698, 235);
//cout << shadow.ShadowSearch("license_plate_10.jpg",	718, 802, 1847, 964);
//cout << shadow.ShadowSearch("license_plate_11.jpg",	656, 1326, 1001, 1402);
//cout << shadow.ShadowSearch("license_plate_ex_2.jpg", 757, 634, 895, 677);
//cout << shadow.ShadowSearch("license_plate_ex_3.jpg", 2610, 1237, 2900, 1300);
//cout << shadow.ShadowSearch("license_plate_ex_4.png", 63, 6, 563, 122);
//cout << shadow.ShadowSearch("license_plate_ex_5.jpg", 145, 145, 605, 235);
//cout << shadow.ShadowSearch("license_plate_ex_6.jpg", 187, 213, 265, 230);
//cout << shadow.ShadowSearch("license_plate_ex_7.jpg", 129, 185, 208, 208);