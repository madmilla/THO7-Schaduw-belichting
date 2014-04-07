#ifndef IMAGE_H
#define IMAGE_H
#include "Cimg.h"

using namespace cimg_library;
class Image{
private:
	unsigned char ** channelsArray; //saves image data

	int channels;//amount of channels

	int height; //height of image
	int width; //width of image

	const char * filename; //filename of image

public:
	//load image data
	//
	//Loads image data, filename is imagename which is loaded
	//channels amount of channels which are saved.
	Image(const char * filename, int channels);
	//load image data
	//
	//Loads image data, filename is imagename which is loaded
	//channels will be chosen automaticly.
	Image(const char * filename);
	//empty image
	//
	//Creates empty image with width, height and channels
	Image(int width, int height, int channels);
	Image(){};

	//Returns all channels
	unsigned char ** GetChannelsArray();
	//returns only 1 channel
	unsigned char * GetChannelArray(int channel);

	//return pointer to data of image of x,y posistion with right channel
	unsigned char * Data(int x, int y, int channel);
	//return value of x,y position on the right channel
	unsigned char GetValue(int x, int y, int channel);

	//returns amount of channels
	int GetChannels();

	//returns height of image
	int Height();
	//returns width of image
	int Width();

	//returns filename
	const char * GetFilename();
	//sets filename
	void SetFilename(const char * filename);

	//saves image to file using the filename
	void SaveImage(const char * filename);
};
#endif