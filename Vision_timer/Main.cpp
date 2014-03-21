#include "exectimer.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "Image.h"
#include "GrayScale.h"
#include "ShadowFinder.h"

int main(int argc, char** argv) {
	/*=========================     Program parameters     =========================*/

//	std::string inputName = "LenaNoise.jpg";
//	std::string inputName = "Lena.bmp";
//	std::string inputName = "flower.jpg";
//	std::string inputName = "Knikker.bmp";
//	std::string inputName = "TestImage.bmp";
//	std::string inputName = "Busjes.jpg";
//	std::string inputName = "BusjesGroot.jpg";
//	std::string inputName = "Waterfall.jpg";
//	std::string inputName = "Testschaduw..jpg";
	std::string inputName = "Untitled.jpg";

	bool grayOn = false;
	

	/*=========================     Program parameters     =========================*/

	/*
	Read the chosen file
	*/
	if(argv[1] != nullptr) {
		inputName = argv[1];
		std::cout << "File is: " << inputName << "\n\n";
	} else {
		std::cout << "File is: " << inputName << "\n\n";
	}

	//Load the image in the Image class
	Image originalImage(inputName);

	//Filter image with grayscale
	if(grayOn) {
		Image grayImage(originalImage);
		GrayScale gray;
		gray.CreateGrayScaleImage(originalImage, grayImage);
		grayImage.SaveImageToFile("GRAY_");

		std::cout << std::endl;
	}

	if (!grayOn){
		Image img(originalImage);
		ShadowFinder shadow;
		shadow.ShadowTest(originalImage);
	}

	//Save the original image
	originalImage.SaveImageToFile("ORIGINAL_");
	std::cout << std::endl;

	//End program
	std::cout << "Program ended, Press a key to continue\n";
	std::cin.ignore();
	return 0;
}


