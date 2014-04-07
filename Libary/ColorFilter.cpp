#include "stdafx.h"
#include "ColorFilter.h"

ColorFilter::ColorFilter(Image img): Filter(img){
}

void ColorFilter::makeRed(){
	for (int r = 0; r < image.Height(); r++){
		for (int c = 0; c < image.Width(); c++){
			*editedImage.Data(c, r, 0) = *image.Data(c, r, 2);
			*editedImage.Data(c, r, 1) = 0;
			*editedImage.Data(c, r, 2) = 0;
		}
	}
}

void ColorFilter::makeGreen(){
	for (int r = 0; r < image.Height(); r++){
		for (int c = 0; c < image.Width(); c++){
			*editedImage.Data(c, r, 0) = 0;
			*editedImage.Data(c, r, 1) = *image.Data(c, r, 2);
			*editedImage.Data(c, r, 2) = 0;
		}
	}
}

void ColorFilter::makeBlue(){
	for (int r = 0; r < image.Height(); r++){
		for (int c = 0; c < image.Width(); c++){
			*editedImage.Data(c, r, 0) = 0;
			*editedImage.Data(c, r, 1) = 0;
			*editedImage.Data(c, r, 2) = *image.Data(c, r, 2);
		}
	}
}

void ColorFilter::makeGrey(){
	for (int r = 0; r < image.Height(); r++){
		for (int c = 0; c < image.Width(); c++){
			unsigned char lum = (unsigned char)(((unsigned char)*image.Data(c, r, 0) * 0.30) + ((unsigned char)*image.Data(c, r, 1) * 0.59) + ((unsigned char)*image.Data(c, r, 2) * 0.11));
			*editedImage.Data(c, r, 0) = lum;
			*editedImage.Data(c, r, 1) = lum;
			*editedImage.Data(c, r, 2) = lum;
		}
	}
}