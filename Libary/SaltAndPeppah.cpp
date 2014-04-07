#include "stdafx.h"
#include "SaltAndPeppah.h"
#include <random>

SaltAndPepper::SaltAndPepper(Image img, int per):Filter(img){
	Copy();
	setNoise(per);
}

void SaltAndPepper::setNoise(int per){
	percentage = per;
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, image.Width()-1); // define the range
	std::uniform_int_distribution<> distr2(0, image.Height()-1); // define the range
	std::uniform_int_distribution<> distrColor(0, 1); // define the range

	int x = 0;
	int y = 0;
	for (int n = 0; n < image.Width()*image.Height() / 100 * percentage; ++n){//This will not result in excatly percentage because its possible 1 pixel will be edited multiple times. The percentage will be lower in reality
		x = distr(eng);//without this it looks like confetti because the pixels will change so only 1 color will change.
		y = distr2(eng);
		if (distrColor(eng) == 0){//black
			*editedImage.Data(x, y, 0) = 0;
			*editedImage.Data(x, y, 1) = 0;
			*editedImage.Data(x, y, 2) = 0;
		}
		else{//white
			*editedImage.Data(x, y, 0) = 255;
			*editedImage.Data(x, y, 1) = 255;
			*editedImage.Data(x, y, 2) = 255;
		}
	}
}

int SaltAndPepper::getPercentage(){
	return percentage;
}