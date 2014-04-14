#include "BaseTimer.h"
#include "Overexposure_Test.h"

#include <ImageLoader.h>
#include <iostream>

using namespace std;
using namespace ImageLib;

int main(){
	BaseTimer bt;


	shared_ptr<ImageRGB> img = loadImg("SH-HR-91.jpg");

	bt.start();
	Overexposure_Test OT;
	cout << OT.Overexposure_Detection(img, 1353, 989, 2189, 796, 1344, 1181, 2147, 939) << '\n';
	//OT.Overexposure_Removal(img, 1353, 989, 2189, 796, 1344, 1181, 2147, 939);

	/*if (OT.Overexposure_Detection(img, 145, 145, 605, 137, 155, 240, 605, 235)){
		OT.Overexposure_Removal(img, 145, 145, 605, 137, 155, 240, 605, 235);
	}*/

	
	bt.stop();

	cout << bt.elapsedSeconds() << '\n';
	system("pause");
	return 0;
}