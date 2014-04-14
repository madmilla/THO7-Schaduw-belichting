#include "BaseTimer.h"
#include "Overexposure_Test.h"

#include <ImageLoader.h>
#include <iostream>

using namespace std;
using namespace ImageLib;

int main(){
	BaseTimer bt;


	shared_ptr<ImageRGB> img = loadImg("license_plate_ex_5.bmp");

	bt.start();
	Overexposure_Test OT;
	//cout << OT.Overexposure_Detection(img, 187, 213, 265, 214, 187, 229, 265, 230) << '\n';
	OT.Overexposure_Removal(img, 145, 145, 605, 137, 155, 240, 605, 235);

	/*if (OT.Overexposure_Detection(img, 145, 145, 605, 137, 155, 240, 605, 235)){
		OT.Overexposure_Removal(img, 145, 145, 605, 137, 155, 240, 605, 235);
	}*/

	
	bt.stop();

	cout << bt.elapsedSeconds() << '\n';
	system("pause");
	return 0;
}