#include "stdafx.h"
#include "OverExposure.h"
#include <iostream>

OverExposure::OverExposure(Image img) :Filter(img){
}



void OverExposure::M(){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);
			int Ci = pow(*image.Data(x, y, 1)**image.Data(x, y, 2), 2);
			float m = 0.5*(tanh(1.0 / 60.0*((Li - 80.0) + (40 - Ci))) + 1);
			*editedImage.Data(x, y, 0) = m*255;
			*editedImage.Data(x, y, 1) = m*255;
			*editedImage.Data(x, y, 2) = m*255;
		}
	}
	
	editedImage.SaveImage("testM.bmp");
}

void OverExposure::Threshold(int threshold){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);
			if (Li > threshold){
				*editedImage.Data(x, y, 0) = 255;
				*editedImage.Data(x, y, 1) = 255;
				*editedImage.Data(x, y, 2) = 255;
			}
			else{
				*editedImage.Data(x, y, 0) = 0;
				*editedImage.Data(x, y, 1) = 0;
				*editedImage.Data(x, y, 2) = 0;
			}
		}
	}

	editedImage.SaveImage("testOverExposureThreshold.bmp");
}

void OverExposure::ThresholdRepair(int threshold){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);
			*editedImage.Data(x, y, 0) = Li;
			*editedImage.Data(x, y, 1) = Li;
			*editedImage.Data(x, y, 2) = Li;
		}
	}

	editedImage.SaveImage("testOverExposureThresholdBEFORERepair.bmp");

	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			int Li = *image.Data(x, y, 0);
			if (Li > threshold){
				*editedImage.Data(x, y, 0) = Li - threshold/10; //Not a real repair...
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
			else if (Li > threshold - Li / 10){
				*editedImage.Data(x, y, 0) = Li - (Li - ( threshold - threshold / 10));
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
			else{
				*editedImage.Data(x, y, 0) = Li;
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
		}
	}

	editedImage.SaveImage("testOverExposureThresholdRepair.bmp");
}


