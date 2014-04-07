/*
Jeroen Huisen
When it works this file will be cleaned and maded usefull
*/

#include "stdafx.h"
#include "ColorSpace.h"-

ColorSpace::ColorSpace(Image img):Filter(img){
	A = new float[img.Height() * img.Width()];
	B = new float[img.Height() * img.Width()];
}

float * XYZtoRGB(double X, double Y, double Z)
{

	double var_R = X * 3.2404542 + Y * -1.5371385 + Z * -0.4985314;
	double var_G = X * -0.9692660 + Y * 1.8760108 + Z* 0.0415560;
	double var_B = X * 0.0556434 + Y * -0.2040259 + Z * 1.0572252;

	var_R = var_R / 100.0;
	var_G = var_G / 100.0;
	var_B = var_B / 100.0;

	//std::cout << var_R << "\n" << var_G << "\n" << var_B << "\n";

	if (var_R >  0.0031308){
		var_R = pow(var_R, (1.0 / 2.4));
		var_R = var_R * 1.055 - 0.055;
	}
	else{
		var_R = var_R * 12.92;
	}
	if (var_G > 0.0031308){
		var_G = pow(var_G, (1.0 / 2.4));
		var_G = var_G * 1.055 - 0.055;
	}
	else{
		var_G = var_G * 12.92;
	}
	if (var_B >  0.0031308){
		var_B = pow(var_B, (1.0 / 2.4));
		var_B = var_B * 1.055 - 0.055;
	}
	else{
		var_B = var_B * 12.92;
	}

	//std::cout << "between\n" << var_R << "\n" << var_G << "\n" << var_B << "\n";

	double R = (double)((double)var_R * (double)255);        //R from 0 to 255
	double G = (double)((double)var_G * (double)255);        //G from 0 to 255
	double B = (double)((double)var_B * (double)255);        //B from 0 to 255

	if (R >= 255){
		R = 255;
	}
	else if (R <= 0){
		R = 0;
	}
	if (G >= 255){
		G = 255;
	}
	else if (G <= 0){
		G = 0;
	}
	if (B >= 255){
		B = 255;
	}
	else if (B <= 0){
		B = 0;
	}


	float * returnValue = new float[3];
	returnValue[0] = R;
	returnValue[1] = G;
	returnValue[2] = B;


	return returnValue;
}


float * ToColorLAB(float  L, float  A, float B)
{
	float y = (L + 16.0) / 116.0;
	float x = A / 500.0 + y;
	float z = y - B / 200.0;

	//std::cout << x << "\n" << y << "\n" << z << "\n\n";

	float x3 = x * x * x;
	float z3 = z * z * z;

	float X = 95.047;
	float Y = 100.000;
	float Z = 108.883;
	X = X * (x3 > (216 / 24389) ? x3 : (x - 16.0 / 116.0) / 7.787);
	Y = Y * (L > ((24389 / 27) * (216 / 24389)) ? pow(((L + 16.0) / 116.0), 3) : L / (24389 / 27));
	Z = Z * (z3 > (216 / 24389) ? z3 : (z - 16.0 / 116.0) / 7.787);

	//std::cout << X << "\n" << Y << "\n" << Z << "\n";

	return XYZtoRGB(X,Y,Z);
}

float * ToColorLABTEST(float  L, float  A, float B)
{
	float y = (L + 16.0) / 116.0;
	float x = A / 500.0 + y;
	float z = y - B / 200.0;

	//std::cout << x << "\n" << y << "\n" << z << "\n\n";

	float x3 = x * x * x;
	float y3 = y * y * y;
	float z3 = z * z * z;

	float X = 95.047;
	float Y = 100.000;
	float Z = 108.883;

	if (x3 > 0.008856){
		X = X* x3;
	}
	else{
		X = X * ((x - 16.0 / 116.0) / 7.787);
	}
	if (y3 > 0.008856){
		Y = Y * y3;
	}
	else{
		Y = Y * ((y - 16.0 / 116.0) / 7.787);
	}
	if (z3 > 0.008856){
		Z = Z * z3;
	}
	else{
		Z = Z * ((z - 16.0 / 116.0) / 7.787);
	}
	//X = X * (x3 > (216 / 24389) ? x3 : (x - 16.0 / 116.0) / 7.787);
	//Y = Y * (L > ((24389 / 27) * (216 / 24389)) ? pow(((L + 16.0) / 116.0), 3) : L / (24389 / 27));
	//Z = Z * (z3 > (216 / 24389) ? z3 : (z - 16.0 / 116.0) / 7.787);

	//std::cout << X << "\n" << Y << "\n" << Z << "\n";

	return XYZtoRGB(X, Y, Z);
}

void ColorSpace::ToRGB(){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			float* test = ToColorLABTEST(*image.Data(x, y, 0), A[x+x*y], *(B + x +x*y));
			//float* test = ToColorLABTEST(*image.Data(x, y, 0),0,0);
			*editedImage.Data(x, y, 0) = test[0];
			*editedImage.Data(x, y, 1) = test[1];
			*editedImage.Data(x, y, 2) = test[2];

		}
	}
	editedImage.SaveImage("testRGBCOLOR.bmp");
}

double* ColorSpace::RGBtoXYZ(unsigned char R, unsigned char G, unsigned char B)
{
//	R = 255;
//	G = 255;
//	B = 0;
	double var_R = (double)((double)R / (double)255);        //R from 0 to 255
	double var_G = (double)((double)G / (double)255);        //G from 0 to 255
	double var_B = (double)((double)B / (double)255);        //B from 0 to 255

	//std::cout << "between1\n" << var_R << "\n" << var_G << "\n" << var_B << "\n";

	if (var_R > 0.04045){
		var_R = pow(((var_R + 0.055) / 1.055), 2.4);
	}
	else{
		var_R = var_R / 12.92;
	}
	if (var_G > 0.04045){
		var_G = pow(((var_G + 0.055) / 1.055), 2.4);
	}
	else{
		var_G = var_G / 12.92;
	}
	if (var_B > 0.04045){
		var_B = pow(((var_B + 0.055) / 1.055), 2.4);
	}
	else{
		var_B = var_B / 12.92;
	}

	//std::cout << "between\n" << var_R << "\n" << var_G << "\n" << var_B << "\n";

	var_R = var_R * 100;
	var_G = var_G * 100;
	var_B = var_B * 100;

	//Observer. = 2°, Illuminant = D65
	double * returnValue = new double[3];
	returnValue[0] = var_R * 0.4124564 + var_G * 0.3575761 + var_B * 0.1804375;
	returnValue[1] = var_R * 0.2126729 + var_G * 0.7151522 + var_B * 0.0721750;
	returnValue[2] = var_R * 0*.0193339 + var_G * 0.1191920 + var_B * 0.9503041;

 
	return returnValue;
}

void ColorSpace::ToXYZ(){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			double* test = RGBtoXYZ(*image.Data(x, y, 0), *image.Data(x, y, 1), *image.Data(x, y, 2));
			*editedImage.Data(x, y, 0) = test[0];
			*editedImage.Data(x, y, 1) = test[1];
			*editedImage.Data(x, y, 2) = test[2];
		}
	}
	editedImage.SaveImage("testXYZ.bmp");
}

float * ColorSpace::XYZtoLAB(float x, float y, float z)
{
	//std::cout << "\nXYZtoLAB\n";
	float ref_X = 95.047;
	float ref_Y = 100.000;
	float ref_Z = 108.883;

	float var_X = (float)x / (float)ref_X;         
	float var_Y = (float)y / (float)ref_Y;        
	float var_Z = (float)z / (float)ref_Z;  

	//std::cout << var_X << "\n" << var_Y << "\n" << var_Z << "\n\n";

	if (var_X > 0.008856){
		var_X = pow(var_X,(1.0 / 3.0));
	}
	else{
		var_X = (903.3 * var_X + 16.0) / 116.0;
	}
	if (var_Y > 0.008856){
		var_Y = pow(var_Y,(1.0 / 3.0));
	}
	else{
		var_Y = (903.3 * var_Y + 16.0) / 116.0;
	}
	if (var_Z > 0.008856){
		var_Z = pow(var_Z, (1.0 / 3.0));
	}
	else{
		var_Z = (903.3 * var_Z + 16.0) / 116.0;
	}

	//std::cout << var_X << "\n" << var_Y << "\n" << var_Z << "\n";

	float* returnValue = new float[3];
	returnValue[0] = (116 * var_Y) - 16;
	returnValue[1] = 500 * (var_X - var_Y);
	returnValue[2] = 200 * (var_Y - var_Z);



	return	returnValue;
}

void ColorSpace::ToLAB(){
	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			double* test = RGBtoXYZ(*image.Data(x, y, 0), *image.Data(x, y, 1), *image.Data(x, y, 2));
			float* test2 = XYZtoLAB(test[0], test[1], test[2]);
			A[x + x*y] = test2[1];
			*(B + x + x*y) = test2[2];
			*editedImage.Data(x, y, 0) = test2[0];
			*editedImage.Data(x, y, 1) = test2[1];
			*editedImage.Data(x, y, 2) = test2[2];
		}
	}
	editedImage.SaveImage("testLAB.bmp");
}


void ColorSpace::Test(){
/*	std::cout << (int)*image.Data(100, 100, 0) << "\n";
	std::cout << (int)*image.Data(100, 100, 1) << "\n";
	std::cout << (int)*image.Data(100, 100, 2) << "\n";

	double* test = RGBtoXYZ(*image.Data(100, 100, 0), *image.Data(100, 100, 1), *image.Data(100, 100, 2));
	*/

	double * test = RGBtoXYZ(255, 20, 255);
	std::cout << "\nRGB to XYZ:\n";
	std::cout << test[0] << "\n";
	std::cout << test[1] << "\n";
	std::cout << test[2] << "\n";

	float* test2 = XYZtoLAB(test[0], test[1], test[2]);

	std::cout << "\nXYZ to LAB:\n";
	std::cout << test2[0] << "\n";
	std::cout << test2[1] << "\n";
	std::cout << test2[2] << "\n";

	std::cout << "\nLAB to RGB:\n";
	/*float* test3 = ToColorLAB(test2[0], test2[1], test2[2]);
	std::cout << test3[0] << "\n";
	std::cout << test3[1] << "\n";
	std::cout << test3[2] << "\n";*/

	float* test3 = ToColorLABTEST(test2[0], test2[1], test2[2]);

	std::cout << test3[0] << "\n";
	std::cout << test3[1] << "\n";
	std::cout << test3[2] << "\n";
}