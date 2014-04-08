#ifndef FILTER_H
#define FILTER_H
#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>

using namespace std;
using namespace ImageLib;

class Filter{
protected:
	ImageRGB image;//original input image
	ImageRGB editedImage; //editedImage is a image which should be used to save the edited image
public:
	Filter(ImageRGB img){
		image = img;
		editedImage = ImageRGB(img.width(), img.height()); //Make a new empty image with same dimensions and channels
	}

	ImageRGB getImage(){//Return image
		return image;
	}
	ImageRGB getEditedImage(){//Return editedImage
		return editedImage;
	}

	void Copy(){//Copy data from image to editedImage
		for (int y = 0; y < image.height(); y++){
			for (int x = 0; x < image.width(); x++){
				*editedImage.data(x, y, Channel::Red) = *image.data(x, y, Channel::Red);
				*editedImage.data(x, y, Channel::Green) = *image.data(x, y, Channel::Green);
				*editedImage.data(x, y, Channel::Blue) = *image.data(x, y, Channel::Blue);
			}
		}
	}
};
#endif