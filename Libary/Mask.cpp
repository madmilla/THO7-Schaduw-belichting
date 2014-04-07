#include "stdafx.h"
#include "Mask.h"


Mask::Mask(Image img, int s){
	size = s;
	image = img;
	mask = new unsigned char[s*s];
}

Mask::~Mask(){
	delete mask;
}

unsigned char * Mask::getMask(int x, int y, int channel){
	if (image.Height() < y + size / 2 || image.Width() < x + size / 2){//check for exceeding image size
		int filterNumber = 0;//used for saving the mask from left to right in mask.
		for (int filterY = -(size - 1) / 2; filterY <= (size - 1) / 2; filterY++){//Controls y starts from the top of the mask ends at the bottom
			for (int filterX = -(size - 1) / 2; filterX <= (size - 1) / 2; filterX++){//Controls x starts from the left of the mask ends at the right
				mask[filterNumber] = *image.Data(x + filterX, y + filterY, channel); //get pixel and save in mask
				filterNumber++;
			}
		}
		return mask;
	}
	else{
		std::cerr << "The used mask isn't valid, it exceeds the image size."; //warning when exceeding image size
		for (int i = 0; i < size*size; i++){
			mask[i] = 0; //Make the mask complete 0, so on a image it will look black
		}
		return mask;
	}
}