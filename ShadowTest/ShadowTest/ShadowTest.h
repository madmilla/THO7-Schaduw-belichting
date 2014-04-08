// Arthur van der Weiden
#pragma once
#include <ImageLib.h>
#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>

using namespace ImageLib;

class ShadowTest{

private:
	
	bool FoundShadow = 0;

public:

	ShadowTest(){}
	bool ShadowSearch(std::string FileName, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY,int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);

};