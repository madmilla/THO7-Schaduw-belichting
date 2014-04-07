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
#include "ImageV2.h"
#include "Filter.h"
#include <math.h>
#include <iostream>

class ColorSpace : public Filter{
private:
	double* RGBtoXYZ(unsigned char R, unsigned char G, unsigned char B);
	float* XYZtoLAB(float x, float y, float z);

	float * A;
	float * B;
public:
	ColorSpace(Image img);
	void ToXYZ();
	void ToLAB();
	void ToRGB();
	
	float * getA(){
		return A;
	}
	float * getB(){
		return B;
	}

	void setA(float * Ab){
		A = Ab;
	}
	void setB(float * Bb){
		B = Bb;
	}
	void Test();
};
#endif