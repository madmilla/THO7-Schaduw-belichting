#include "OverExposure.h"
#include <iostream>

OverExposure::OverExposure(){

}

/*void OverExposure::M(){
	//based on http://www->comp->nus->edu->sg/~tsim/documents/cvpr2010-final-reduced->pdf
	//The implementation isn't done so it will not produce usefull results->
	for (int y = 0; y < image->height(); y++){
		for (int x = 0; x < image->width(); x++){
			int Li = *image->data(x, y, Channel::Red);//Lightness of the pixel with coordinates x and y
			int Ci = pow((*image->data(x, y, Channel::Green) * *image->data(x, y, Channel::Blue)), 2);
			float m = 0.5*(tanh(1.0 / 60.0*((Li - 80.0) + (40 - Ci))) + 1); //formula, see link 3->1
			*editedImage->data(x, y, Channel::Red) = m*255;
			*editedImage->data(x, y, Channel::Green) = m*255;
			*editedImage->data(x, y, Channel::Blue) = m*255;
		}
	}
}*/


void OverExposure::ThresholdRepair(std::shared_ptr<ImageRGB> image, int threshold, int power, int xmin, int ymin, int xmax, int ymax){
	for (int y = ymin; y < ymax; y++){
		for (int x = xmin; x < xmax; x++){
			int Li = *image->data(x, y, Channel::Red);
			if (Li > threshold){ //if higher than threshold lower lightness of pixel
				*image->data(x, y, Channel::Red) = Li - power; //Not a complete repair but will lower the lightness
				//*editedImage->Data(x, y, 0) = 0; //this is overexposed show->
				*image->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*image->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else if (Li > threshold - power){ //if its lower than threshold but higher than edited ligthness is changed into->
												//This makes sure its not higher than edited lightness value->
				*image->data(x, y, Channel::Red) = Li - (Li - ( threshold - power));
				*image->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*image->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else{//In anyother case keep the default lightness
				*image->data(x, y, Channel::Red) = Li;
				*image->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*image->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
		}
	}

	//editedImage->SaveImage("testOverExposureThresholdRepair->bmp");
}


void OverExposure::ThresholdRepairOpposite(std::shared_ptr<ImageRGB> image, int threshold, int lowest, int power, int xmin, int ymin, int xmax, int ymax){
	for (int y = ymin; y < ymax; y++){
		for (int x = xmin; x < xmax; x++){
			int Li = *image->data(x, y, Channel::Red);
			if (Li < threshold && Li > lowest){ //if higher than threshold lower lightness of pixel
				//*editedImage->Data(x, y, 0) = Li + threshold / 7; //Not a complete repair but will lower the lightness
				*image->data(x, y, Channel::Red) = 100; //Not a complete repair but will lower the lightness
				//*editedImage->Data(x, y, 0) = 0; //this is overexposed show->
				*image->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*image->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else if (Li < threshold + power && Li > lowest){ //if its lower than threshold but higher than edited ligthness is changed into.
				//This makes sure its not higher than edited lightness value->
				*image->data(x, y, Channel::Red) = 80;
				*image->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*image->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
			else{//In anyother case keep the default lightness
				*image->data(x, y, Channel::Red) = Li;
				*image->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);//just copy image channels
				*image->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
		}
	}

	//editedImage->SaveImage("testOverExposureThresholdRepair.bmp");
}

