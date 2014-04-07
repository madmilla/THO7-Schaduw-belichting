#ifndef FILTER_H
#define FILTER_H
#include "ImageV2.h"

class Filter{
protected:
	Image image;//
	Image editedImage; //editedImage is a image which should be used to 
public:
	Filter(Image img){
		image = img;
		editedImage = Image(img.Width(), img.Height(), img.GetChannels()); //Make a new empty image with same dimensions and channels
		editedImage.SetFilename(img.GetFilename()); //Otherwise editedImage will not have a good filename but can be changed later on
	}

	Image getImage(){//Return image
		return image;
	}
	Image getEditedImage(){//Return editedImage
		return editedImage;
	}

	void Copy(){//Copy data from image to editedImage
		for (int y = 0; y < image.Height(); y++){
			for (int x = 0; x < image.Width(); x++){
				*editedImage.Data(x, y, 0) = *image.Data(x, y, 0); //Copy data
				*editedImage.Data(x, y, 1) = *image.Data(x, y, 1);
				*editedImage.Data(x, y, 2) = *image.Data(x, y, 2);
			}
		}
	}
};
#endif