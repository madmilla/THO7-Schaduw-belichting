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
	//ImageRGB* image;//original input image
	//ImageRGB* editedImage; //editedImage is a image which should be used to save the edited image
	std::shared_ptr<ImageRGB> editedImage;
	std::shared_ptr<ImageRGB> image;
public:
	Filter(ImageRGB rgb_img){
		editedImage = std::make_shared<ImageRGB>(rgb_img.width(), rgb_img.height());
		/*cout<<rgb_img.height();
		image = &rgb_img;
		cout << image->height();
		ImageRGB test((int)rgb_img.width(), (int)rgb_img.height(), rgb_img.data(0,0,Channel::Red));
		editedImage = &test;*/
		image = std::make_shared<ImageRGB>(rgb_img);
	}

	/*~Filter(){
		delete &editedImage;
		delete &image;
	}*/

	std::shared_ptr<ImageRGB> getImage(){//Return image
		cout << "\nimg" << editedImage->height() << "\n";
		cout << "bagger" <<image->height();
		return image;
	}
	std::shared_ptr<ImageRGB> getEditedImage(){//Return editedImage
		return editedImage;
	}

	void Copy(){//Copy data from image to editedImage
		for (int y = 0; y < image->height(); y++){
			for (int x = 0; x < image->width(); x++){
				*editedImage->data(x, y, Channel::Red) = *image->data(x, y, Channel::Red);
				*editedImage->data(x, y, Channel::Green) = *image->data(x, y, Channel::Green);
				*editedImage->data(x, y, Channel::Blue) = *image->data(x, y, Channel::Blue);
			}
		}
	}
};
#endif