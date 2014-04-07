// THO7OverExposure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ImageV2.h"
#include "ColorSpace.h"
#include "OverExposure.h"


int main(int argc, char* argv[])
{
	Image img(argv[1]);

	ColorSpace cs(img);
	cs.ToXYZ();
	cs.ToLAB();
	cs.Test();
	cs.getEditedImage().SaveImage("dikkiedik.bmp");
	img = cs.getEditedImage();
	ColorSpace csTEST(img);
	csTEST.setA(cs.getA());
	csTEST.setB(cs.getB());
	csTEST.ToRGB();
	csTEST.getEditedImage().SaveImage("convert.bmp");
	OverExposure oe(img);
	//oe.M();
	//oe.Threshold(90);
	oe.ThresholdRepair(90);
	ColorSpace cs1(oe.getEditedImage());
	cs1.setA(cs.getA());
	cs1.setB(cs.getB());
	cs1.ToRGB();
	cs1.getEditedImage().SaveImage("testert.bmp");

	system("pause");
	return 0;
}

