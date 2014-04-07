/*
Jeroen Huisen
When it works this file will be cleaned and maded usefull
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