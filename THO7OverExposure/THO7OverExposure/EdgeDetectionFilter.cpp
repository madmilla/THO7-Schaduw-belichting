#include "stdafx.h"
#include "EdgeDetectionFilter.h"
#include <iostream>
#include <vector>


void EdgeDetectionFilter::SobelEdgeDetector(Image source, Image target, int threshold){
	for (int y = 1; y < source.Height()-1; y++){
		unsigned char * target_offset = (unsigned char *) target.Data(0, y, 0);
		for (int x = 1; x < source.Width()-1; x++){
			int xGradient = *source.Data(x-1, y+1, 0) + *source.Data(x-1, y, 0) * 2 + *source.Data(x-1, y-1, 0) - *source.Data(x+1, y+1, 0) - *source.Data(x+1, y, 0) * 2 - *source.Data(x+1, y-1, 0);
			int yGradient = *source.Data(x - 1, y - 1 , 0) + *source.Data(x, y -1, 0) * 2 + *source.Data(x + 1, y - 1, 0) - *source.Data(x, y + 1, 0) - *source.Data(x , y+1, 0) * 2 - *source.Data(x - 1, y + 1, 0);

			int sum = abs(xGradient) + abs(yGradient);
			//sum = sum > 255 ? 255 : sum;
			//sum = sum < 0 ? 0 : sum;
			if (sum > 255){
				sum = 255;//edge?
			}
			if (sum < 0){
				sum = 0; //not possible because of abs right? not sure..
			}
			if (sum >= threshold){
				*target.Data(x, y, 0) = sum;
				*target.Data(x, y, 1) = *source.Data(x, y, 1);
				*target.Data(x, y, 2) = *source.Data(x, y, 2);
			}
			else{
				*target.Data(x, y, 0) = *source.Data(x, y, 0);
				*target.Data(x, y, 1) = *source.Data(x, y, 1);
				*target.Data(x, y, 2) = *source.Data(x, y, 2);
			}
		}

	}
	target.SaveImage("test.bmp");
	//cornerDetector(target, target, treshold, 10);
}
