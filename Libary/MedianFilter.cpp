#include "stdafx.h"
#include "MedianFilter.h"

//#include <iostream>



MedianFilter::MedianFilter(Image img, int value):Filter(img){
	FilterHistogram(value);
}


void MedianFilter::FilterHistogram(int value){//size of filter
	unsigned char* filterRed = new unsigned char[value * value];
	unsigned char* filterGreen = new unsigned char[value * value];
	unsigned char* filterBlue = new unsigned char[value * value];

	unsigned char* filterRedHistogram = new unsigned char[256];
	unsigned char* filterGreenHistogram = new unsigned char[256];
	unsigned char* filterBlueHistogram = new unsigned char[256];

	for (int i = 0; i < 256; i++){
		filterRedHistogram[i] = 0;
		filterGreenHistogram[i] = 0;
		filterBlueHistogram[i] = 0;
	}

	int filterNumber = 0;
	int total = 0;
	for (int y = (value - 1) / 2; y < image.Height() - (value - 1) / 2; y++){
		total++;
		for (int x = (value - 1) / 2; x < image.Width() - (value - 1) / 2; x++){
			total++;
			filterNumber = 0;
			for (int filterY = -(value - 1) / 2; filterY <= (value - 1) / 2; filterY++){
				for (int filterX = -(value - 1) / 2; filterX <= (value - 1) / 2; filterX++){
					filterRedHistogram[*image.Data(x + filterX, y + filterY, 0)] ++;
					filterGreenHistogram[*image.Data(x + filterX, y + filterY, 1)] ++;
					filterBlueHistogram[*image.Data(x + filterX, y + filterY, 2)] ++;
					//std::cout << filterNumber<<"\n";
				}
				//filterNumber += value;
			}
			//Histogram
			int foundRed = 0;
			int foundGreen = 0;
			int foundBlue = 0;
			int searchRed = 0;
			int searchGreen = 0;
			int searchBlue = 0;
			for (int i = 0; i < 256; i++){
				if (foundRed <= (value * value - 1) / 2){
					foundRed += filterRedHistogram[i];
					searchRed++;
				}
				if (foundGreen <= (value * value - 1) / 2){
					foundGreen += filterGreenHistogram[i];
					searchGreen++;
				}
				if (foundBlue <= (value * value - 1) / 2){
					foundBlue += filterBlueHistogram[i];
					searchBlue++;
				}
				filterRedHistogram[i] = 0;
				filterGreenHistogram[i] = 0;
				filterBlueHistogram[i] = 0;
			}
			*editedImage.Data(x, y, 0) = searchRed-1;
			*editedImage.Data(x, y, 1) = searchGreen-1;
			*editedImage.Data(x, y, 2) = searchBlue-1;
		}
	}
}