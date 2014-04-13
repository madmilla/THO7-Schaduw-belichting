#include <iostream>
#include <ImageLoader.h>
#include "ShadowTest.h"
#include "BaseTimer.h"

using namespace ImageLib;
using namespace std;

int main(){	
	ShadowTest shadow;
	BaseTimer t;
	t.start();
	shared_ptr<ImageRGB> TestImage1 = loadImg("license_plate_1.jpg");
	shared_ptr<ImageRGB> TestImage2 = loadImg("license_plate_2.jpg");
	shared_ptr<ImageRGB> TestImage3 = loadImg("license_plate_3.jpg");
	shared_ptr<ImageRGB> TestImage4 = loadImg("license_plate_4.jpg");
	shared_ptr<ImageRGB> TestImage5 = loadImg("license_plate_5.jpg");
	shared_ptr<ImageRGB> TestImage6 = loadImg("license_plate_6.jpg");
	shared_ptr<ImageRGB> TestImage7 = loadImg("license_plate_7.jpg");
	shared_ptr<ImageRGB> TestImage8 = loadImg("license_plate_8.jpg");
	shared_ptr<ImageRGB> TestImage9 = loadImg("license_plate_9.jpg");
	shared_ptr<ImageRGB> TestImage10 = loadImg("license_plate_10.jpg");
	shared_ptr<ImageRGB> TestImage11 = loadImg("license_plate_11.jpg");
	shared_ptr<ImageRGB> TestImageEx1 = loadImg("license_plate_ex_1.jpg");
	shared_ptr<ImageRGB> TestImageEx2 = loadImg("license_plate_ex_2.jpg");
	shared_ptr<ImageRGB> TestImageEx3 = loadImg("license_plate_ex_3.jpg");
	shared_ptr<ImageRGB> TestImageEx4 = loadImg("license_plate_ex_4.png");
	shared_ptr<ImageRGB> TestImageEx5 = loadImg("license_plate_ex_5.jpg");
	shared_ptr<ImageRGB> TestImageEx6 = loadImg("license_plate_ex_6.jpg");
	shared_ptr<ImageRGB> TestImageEx7 = loadImg("license_plate_ex_7.jpg");
	shared_ptr<ImageRGB> TestImageEx8 = loadImg("license_plate_ex_12.jpg");
	t.stop();
	cout << "Checking for shadows: " << endl;
	BaseTimer bt;
	bt.start();
	cout << "Normal 1: " << shadow.Shadow_Detection(TestImage1, 298, 39, 1487, 8, 349, 247, 1441, 236) << endl;
	cout << "Normal 2: " << shadow.Shadow_Detection(TestImage2, 659, 701, 997, 706, 657, 773, 992, 778) << endl;
	cout << "Normal 3: " << shadow.Shadow_Detection(TestImage3, 341, 354, 559, 345, 351, 419, 562, 410) << endl;
	cout << "Normal 4: " << shadow.Shadow_Detection(TestImage4, 928, 582, 1085, 579, 930, 618, 1087, 614) << endl;
	cout << "Normal 5: " << shadow.Shadow_Detection(TestImage5, 212, 281, 382, 284, 213, 317, 382, 318) << endl;
	cout << "Normal 6: " << shadow.Shadow_Detection(TestImage6, 1377, 1473, 2243, 1317, 1374, 1667, 2224, 1509) << endl;
	cout << "Normal 7: " << shadow.Shadow_Detection(TestImage7, 398, 388, 1200, 373, 410, 557, 1193, 537) << endl;
	cout << "Normal 8: " << shadow.Shadow_Detection(TestImage8, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) << endl;
	cout << "Normal 9: " << shadow.Shadow_Detection(TestImage9, 108, 191, 708, 116, 130, 366, 698, 235) << endl;
	cout << "Normal 10: " << shadow.Shadow_Detection(TestImage10, 718, 802, 1877, 766, 749, 995, 1847, 964) << endl;
	cout << "Normal 11: " << shadow.Shadow_Detection(TestImage11, 656, 1326, 1000, 1306, 658, 1426, 1001, 1402) << endl;
	cout << "Extended 1: " << shadow.Shadow_Detection(TestImageEx1, 559, 204, 661, 247, 460, 664, 537, 720) << endl;
	cout << "Extended 2: " << shadow.Shadow_Detection(TestImageEx2, 757, 634, 893, 641, 758, 672, 895, 677) << endl;
	cout << "Extended 3: " << shadow.Shadow_Detection(TestImageEx3, 2610, 1237, 2874, 1226, 2634, 1314, 2900, 1300) << endl;
	cout << "Extended 4: " << shadow.Shadow_Detection(TestImageEx4, 63, 6, 568, 63, 123, 6, 568, 123) << endl;
	cout << "Extended 5: " << shadow.Shadow_Detection(TestImageEx5, 145, 145, 605, 137, 155, 240, 605, 235) << endl;
	cout << "Extended 6: " << shadow.Shadow_Detection(TestImageEx6, 187, 213, 265, 214, 187, 229, 265, 230) << endl;
	cout << "Extended 7: " << shadow.Shadow_Detection(TestImageEx7, 129, 185, 210, 187, 128, 207, 208, 208) << endl;
	cout << "Extended 8: " << shadow.Shadow_Detection(TestImageEx8, 663, 617, 3873, 1361, 601, 1201, 3625, 2305) << endl;
	cout << "1 == True, 0 == False" << endl;
	bt.stop();
	cout << "Checking the images took: "<< bt.elapsedSeconds() << " seconds" << endl;
	cin.ignore();
}

//cout << shadow.ShadowSearch("license_plate_1.jpg", 298, 39, 1441, 236);
//cout << shadow.ShadowSearch("license_plate_2.jpg", 659, 701, 992, 778);
//cout << shadow.ShadowSearch("license_plate_3.jpg", 341, 354, 562, 410);
//cout << shadow.ShadowSearch("license_plate_4.jpg", 928, 582, 1087, 614);
//cout << shadow.ShadowSearch("license_plate_5.jpg", 212, 281, 382, 318);
//cout << shadow.ShadowSearch("license_plate_6.jpg", 1377, 1473, 2224, 1509);
//cout << shadow.ShadowSearch("license_plate_7.jpg", 398, 388, 1193, 537);
//cout << shadow.ShadowSearch("license_plate_8.jpg", 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630);
//cout << shadow.ShadowSearch("license_plate_9.jpg", 108, 191, 698, 235);
//cout << shadow.ShadowSearch("license_plate_10.jpg", 718, 802, 1847, 964);
//cout << shadow.ShadowSearch("license_plate_11.jpg", 656, 1326, 1001, 1402);
//cout << shadow.ShadowSearch("license_plate_ex_2.jpg", 757, 634, 895, 677);
//cout << shadow.ShadowSearch("license_plate_ex_3.jpg", 2610, 1237, 2900, 1300);
//cout << shadow.ShadowSearch("license_plate_ex_4.png", 63, 6, 563, 122);
//cout << shadow.Shadow_Detection(TestImage, 145, 145, 605, 145, 155, 240, 605, 235) << endl;
//cout << shadow.ShadowSearch("license_plate_ex_6.jpg", 187, 213, 265, 230);
//cout << shadow.ShadowSearch("license_plate_ex_7.jpg", 129, 185, 208, 208);