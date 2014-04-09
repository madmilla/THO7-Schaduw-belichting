#include "BaseTimer.h"
#include "Overexposure_Test.h"

#include <ImageLoader.h>
#include <iostream>

using namespace std;
using namespace ImageLib;

int main(){
	BaseTimer bt;
	Overexposure_Test OT;

	shared_ptr<ImageRGB> img = loadImg("license_plate_8.bmp");

	bt.start();
	//cout << OT.Overexposure_Detection(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630) << '\n';
	OT.Overexposure_gone(img, 1796, 1518, 2562, 1447, 1815, 1692, 2580, 1630);
	bt.stop();

	cout << bt.elapsedSeconds() << '\n';
	system("pause");
	return 0;
}