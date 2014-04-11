/*
	Jeroen Huisen - Schaduw & Belichting
	Version: 0.1	7-4-2014
	Summary:		This class will convert colorspace
	Description:	This class will convert colorspaces. This will be used to convert from rgb to lab and lab to rgb.
					Before this is possible rgb should be converted to xyz and after that, xyz can be converted to lab.
					When lab is converted back to rgb doesnt this go in 1 stap. 
					It also has to be converted from lab to xyz and xyz to rgb.
					This class is used for overexposure, this class needs lab because the l channel is lightness
*/
#ifndef COLORSPACE_H
#define COLORSPACE_H
#include <ImageLoader.h>
#include <math.h>
#include <iostream>

using namespace ImageLib;

class ColorSpace{
private:
	//rgb to xyz
	inline float* RGBtoLAB(unsigned char R, unsigned char G, unsigned char B);
	//xyz to lab
	inline float* XYZtoLAB(float X, float Y, float Z);
	//xyz to rgb
	inline float* XYZtoRGB(float X, float Y, float Z);
	inline float* RGBtoXYZ(float R, float G, float B);
	//lab to rgb
	inline float* LABtoRGB(float  L, float  A, float B);

	//test function will be deleted
	float* LABtoRGBTEST(float  L, float  A, float B); 

	//float * A;//this is used because A channel goes from -128 to 128 and image class uses unsigned this will be changed
	//float * B;//this is used because B channel goes from -128 to 128 and image class uses unsigned this will be changed
public:
	ColorSpace();


	//Convert rgb to xyz colorspace
	void ToXYZ(std::shared_ptr<ImageRGB> image, int xmin, int ymin, int xmax, int ymax);
	void ToRGBfromXYZ(std::shared_ptr<ImageRGB> image, int xmin, int ymin, int xmax, int ymax);
	//convert xyz to lab
	//
	//Convert xyz to lab colorspace
	void ToLAB(std::shared_ptr<ImageRGB> image, int xmin, int ymin, int xmax, int ymax);
	//convert lab to rgb
	//
	//Convert lab to rgb, intern lab is converted to xyz and xyz to rgb
	void ToRGB(std::shared_ptr<ImageRGB> image, int xmin, int ymin, int xmax, int ymax);



	//test
	//
	//Test function which will be deleted in the official release.
	void Test();
};
#endif