#include "ImageV2.h"
#include <iostream>

class Mask{
private:
	Image image;
	int size;
	unsigned char * mask;
public:
	//Constructor Mask
	//
	//Saves s, the size of the mask
	//Img, the image of which the mask should be applied too.
	//Also the mask pointer is allocated.
	Mask(Image img, int s);

	//Destructor Mask
	//
	//Deletes allocated mask pointer
	~Mask();

	//Returns the mask
	//
	//The function will return the mask and calculate the values according to x,y and channel.
	//X and y are the x and y coordinates of the mid pixel. The mask will be checked if it will exceed the image size.
	//Channel is the channel of the image which the mask should be applied.
	//It returns mask, which contains the mask from topleft to rightbottom.
	unsigned char * getMask(int x, int y, int channel);
};