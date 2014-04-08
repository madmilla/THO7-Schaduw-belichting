#include "stdafx.h"
#include "OverExposure.h"
#include <iostream>

OverExposure::OverExposure(Image img) :Filter(img){
}



void OverExposure::M(){
	//based on http://www.comp.nus.edu.sg/~tsim/documents/cvpr2010-final-reduced.pdf
	//The implementation isn't done so it will not produce usefull results.
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);//Lightness of the pixel with coordinates x and y
			int Ci = pow(*image.Data(x, y, 1)**image.Data(x, y, 2), 2);
			float m = 0.5*(tanh(1.0 / 60.0*((Li - 80.0) + (40 - Ci))) + 1); //formula, see link 3.1
			*editedImage.Data(x, y, 0) = m*255;
			*editedImage.Data(x, y, 1) = m*255;
			*editedImage.Data(x, y, 2) = m*255;
		}
	}
	
	editedImage.SaveImage("testM.bmp");
}

void OverExposure::ThresholdFunction(int threshold){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);//get the lightness value
			if (Li > threshold){ //checks if higher, when higher pixel becomes white.
				*editedImage.Data(x, y, 0) = 255; 
				*editedImage.Data(x, y, 1) = 255;
				*editedImage.Data(x, y, 2) = 255;
			}
			else{
				//if lower pixel becomes black
				*editedImage.Data(x, y, 0) = 0;
				*editedImage.Data(x, y, 1) = 0;
				*editedImage.Data(x, y, 2) = 0;
			}
		}
	}

	//editedImage.SaveImage("testOverExposureThreshold.bmp");
}

void OverExposure::ThresholdRepair(int threshold, int power){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);
			if (Li > threshold){ //if higher than threshold lower lightness of pixel
				*editedImage.Data(x, y, 0) = Li - power; //Not a complete repair but will lower the lightness
				//*editedImage.Data(x, y, 0) = 0; //this is overexposed show.
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);//just copy image channels
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
			else if (Li > threshold - power){ //if its lower than threshold but higher than edited ligthness is changed into.
												//This makes sure its not higher than edited lightness value.
				*editedImage.Data(x, y, 0) = Li - (Li - ( threshold - power));
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);//just copy image channels
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
			else{//In anyother case keep the default lightness
				*editedImage.Data(x, y, 0) = Li;
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);//just copy image channels
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
		}
	}

	//editedImage.SaveImage("testOverExposureThresholdRepair.bmp");
}


void OverExposure::ThresholdRepairOpposite(int threshold){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);
			if (Li < threshold){ //if higher than threshold lower lightness of pixel
				//*editedImage.Data(x, y, 0) = Li + threshold / 7; //Not a complete repair but will lower the lightness
				*editedImage.Data(x, y, 0) = 100; //this is overexposed show.
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);//just copy image channels
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
			else if (Li < threshold + threshold / 7){ //if its lower than threshold but higher than edited ligthness is changed into.
				//This makes sure its not higher than edited lightness value.
				*editedImage.Data(x, y, 0) = Li + (Li - (threshold - threshold / 7));
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);//just copy image channels
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
			else{//In anyother case keep the default lightness
				*editedImage.Data(x, y, 0) = Li;
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);//just copy image channels
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
		}
	}

	//editedImage.SaveImage("testOverExposureThresholdRepair.bmp");
}



