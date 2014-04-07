#include "stdafx.h"
#include "AutoThreshold.h"

AutoThreshold::AutoThreshold(Image img): Filter(img){
}

void AutoThreshold::Threshold(int threshold){
	for (int y = 0; y < image.Height(); y++){
		unsigned char * p = image.Data(0, y, 0);
		unsigned char * ep0 = image.Data(0, y, 0);
		unsigned char * ep1 = image.Data(0, y, 1);
		unsigned char * ep2 = image.Data(0, y, 2);
		for (int x = 0; x < image.Width(); x++){
			if(*(p + x) >= threshold){
				*(ep0 + x) = 255;
				*(ep1 + x) = 255;
				*(ep2 + x) = 255;
			}
			else{
				*(ep0 + x) = 0;
				*(ep1 + x) = 0;
				*(ep2 + x) = 0;
			}
		}
	}
}

void AutoThreshold::ThresholdCalc(){
	//compute u1, the mean grey level of the cornerpixels
	int totalPixelCorners = *image.Data(0, 0, 0) + *image.Data(image.Width()-1, 0, 0) + *image.Data(0, image.Height()-1, 0) + *image.Data( image.Width()-1, image.Height()-1, 0);
	int u1 = totalPixelCorners / 4;
	//compute u2, the mean grey level of all other pixels
	int totalPixels = 0;
	for (int y = 0; y < image.Height(); y++){
		unsigned char * p = image.Data(0, y, 0);
		for (int x = 0; x < image.Width(); x++){
			totalPixels += *(p + x);
		}
	}
	int u2 = (totalPixels - totalPixelCorners) / (image.Height() * image.Width() - 4);

	int tOld = 0;
	int tNew = (u1 + u2) / 2;
	int totalBigger = 0;
	int totalSmaller = 0;
	int amountBigger = 0;
	int amountSmaller = 0;
	while (tOld != tNew){
		totalBigger = 0;
		totalSmaller = 0;
		amountBigger = 0;
		amountSmaller = 0;
		for (int y = 0; y < image.Height(); y++){
			unsigned char * p = image.Data(0, y, 0);
			for (int x = 0; x < image.Width(); x++){
				if (*(p + x) < tNew){
					totalSmaller += *(p + x);
					amountSmaller++;
				}
				else{
					totalBigger += *(p + x);
					amountBigger++;
				}
				//totalPixels += *(p + x);
			}
		}
		u1 = totalSmaller / amountSmaller;
		u2 = totalBigger / amountBigger;
		tOld = tNew;
		tNew = (u1 + u2) / 2;
	}
	Threshold(tNew);
}