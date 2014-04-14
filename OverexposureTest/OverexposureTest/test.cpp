#include "BaseTimer.h"
#include "Overexposure_Test.h"

#include <ImageLoader.h>
#include <iostream>

using namespace std;
using namespace ImageLib;

int main(){
	BaseTimer bt;


	shared_ptr<ImageRGB> img = loadImg("license_plate_8.jpg");

	bt.start();
	Overexposure_Test OT;
	cout << OT.Overexposure_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) << '\n';
	//OT.Overexposure_Removal(img, 145, 145, 605, 137, 155, 240, 605, 235);
	//OT.OverExposure_T(img, 145, 145, 605, 137, 155, 240, 605, 235);

	/*if (OT.Overexposure_Detection(img, 145, 145, 605, 137, 155, 240, 605, 235)){
		OT.Overexposure_Removal(img, 145, 145, 605, 137, 155, 240, 605, 235);
	}*/

	
	bt.stop();

	cout << bt.elapsedSeconds() << '\n';
	system("pause");
	return 0;
}