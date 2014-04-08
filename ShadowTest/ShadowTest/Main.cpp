
#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>
#include "ShadowTest.h"
#include <stdlib.h>
using namespace ImageLib;
using namespace std;

int main(){	
	ShadowTest shadow;
	//std::cout << shadow.ShadowSearch("license_plate_1.jpg", 298, 39, 1441, 236);
	//std::cout << shadow.ShadowSearch("license_plate_2.jpg", 659, 701, 992, 778);
	//std::cout << shadow.ShadowSearch("license_plate_3.jpg", 341, 354, 562, 410);
	//std::cout << shadow.ShadowSearch("license_plate_4.jpg", 928, 582, 1087, 614);
	//std::cout << shadow.ShadowSearch("license_plate_5.jpg", 212, 281, 382, 318);
	//std::cout << shadow.ShadowSearch("license_plate_6.jpg", 1377, 1473, 2224, 1509);
	//std::cout << shadow.ShadowSearch("license_plate_7.jpg", 398, 388, 1193, 537);
	std::cout << shadow.ShadowSearch("license_plate_8.jpg", 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630);
	//std::cout << shadow.ShadowSearch("license_plate_9.jpg", 108, 191, 698, 235);
	//std::cout << shadow.ShadowSearch("license_plate_10.jpg", 718, 802, 1847, 964);
	//std::cout << shadow.ShadowSearch("license_plate_11.jpg", 656, 1326, 1001, 1402);
	//std::cout << shadow.ShadowSearch("license_plate_ex_2.jpg", 757, 634, 895, 677);
	//std::cout << shadow.ShadowSearch("license_plate_ex_3.jpg", 2610, 1237, 2900, 1300);
	//std::cout << shadow.ShadowSearch("license_plate_ex_4.png", 63, 6, 563, 122);
	//std::cout << shadow.ShadowSearch("license_plate_ex_5.jpg", 145, 145, 605, 235);
	//std::cout << shadow.ShadowSearch("license_plate_ex_6.jpg", 187, 213, 265, 230);
	//std::cout << shadow.ShadowSearch("license_plate_ex_7.jpg", 129, 185, 208, 208);
	system("Kip.jpg");
	std::cin.ignore();
}