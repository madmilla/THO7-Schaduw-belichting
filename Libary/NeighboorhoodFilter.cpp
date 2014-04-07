#include "stdafx.h"
#include "NeighbourhoodFilter.h"

NeighboorhoodFilter::NeighboorhoodFilter(Image img) :Filter(img){

}

void NeighboorhoodFilter::NeighboorhoodConvert(int value, int xOffset, int yOffset){
	unsigned char* filterRed = new unsigned char[value * value];
	unsigned char* filterGreen = new unsigned char[value * value];
	unsigned char* filterBlue = new unsigned char[value * value];

	int filterNumber = 0;
	for (int y = (value - 1) / 2; y < image.Height() - (value - 1) / 2; y++){
		for (int x = (value - 1) / 2; x < image.Width() - (value - 1) / 2; x++){
			filterNumber = 0;
			for (int filterY = -(value - 1) / 2; filterY <= (value - 1) / 2; filterY++){
				for (int filterX = -(value - 1) / 2; filterX <= (value - 1) / 2; filterX++){
					filterRed[filterNumber] = *image.Data(x + filterX, y + filterY, 0);
					filterGreen[filterNumber] = *image.Data(x + filterX, y + filterY, 1);
					filterBlue[filterNumber] = *image.Data(x + filterX, y + filterY, 2);
					
					filterNumber++;
				}
			}
			*editedImage.Data(x, y, 0) = filterRed[(value*value - 1) / 2];
			*editedImage.Data(x, y, 1) = filterGreen[(value*value - 1) / 2];
			*editedImage.Data(x, y, 2) = filterBlue[(value*value - 1) / 2];
		}
	}
}
