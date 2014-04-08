// THO7OverExposure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ImageV2.h"
#include "ColorSpace.h"
#include "OverExposure.h"
#include "EdgeDetectionFilter.h"


int main(int argc, char* argv[])
{
	Image img(argv[1]);
	/*Image img(1, 1, 3);
	*img.Data(0, 0, 0) = 236;
	*img.Data(0, 0, 1) = 250;
	*img.Data(0, 0, 2) = 200;*/
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
	csTEST.getEditedImage().SaveImage("convert1.bmp");

	OverExposure oe(img);
	//oe.M();
	//oe.Threshold(90);
	oe.ThresholdRepair(90, 20);
	//oe.ThresholdRepairOpposite(20);
	//EdgeDetectionFilter edf;
	//edf.SobelEdgeDetector(oe.getEditedImage(), img, 0);
	ColorSpace cs1(oe.getEditedImage());
	cs1.setA(cs.getA());
	cs1.setB(cs.getB());
	cs1.ToRGB();
	//img = cs1.getEditedImage();
	cs1.getEditedImage().SaveImage("testert.bmp");


	system("pause");
	return 0;
}

