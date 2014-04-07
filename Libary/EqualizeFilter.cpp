#include "stdafx.h"
#include "EqualizeFilter.h"

EqualizeFilter::EqualizeFilter(Image img) :Filter(img){

}

void EqualizeFilter::EqualizeImage(int * histogram, int range, int total, int channel){
	// histogram[0..#grey_ranges] is normalized histogram 

	int * equalizedHistogram = new int[range];

	double alpha = (double)(range-1)/ (double)total;
	equalizedHistogram[0] = alpha*histogram[0];
	for (int i = 1; i < range; i++){
		int test = round(equalizedHistogram[i - 1] + alpha*histogram[i]);
		if (test >= range-1){
			test = range-1;
		}
		equalizedHistogram[i] = test;
	}

	for (int r = 0; r < image.Height(); r++){
		for (int c = 0; c < image.Width(); c++){
			*editedImage.Data(c, r, channel) = equalizedHistogram[(int)*image.Data(c, r, channel)];
		}
	}
}

void EqualizeFilter::Equalize(int range){
	Histogram h(image);
	h.MakeAHistogram(range, 0);
	EqualizeImage(h.getHistogram(), range, h.getTotal(), 0);
	h.MakeAHistogram(range, 1);
	EqualizeImage(h.getHistogram(), range, h.getTotal(), 1);
	h.MakeAHistogram(range, 2);
	EqualizeImage(h.getHistogram(), range, h.getTotal(), 2);
}