
#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>

using namespace ImageLib;
using namespace std;

int main(){
	unique_ptr<ImageRGB> img = loadImg("alex.jpg");

	img->at(5, 2, Channel::Red) = 255;
	int width = img->width();
	for (int w = 0; w < img->width(); w++){
		for (int h = 0; h < img->height(); h++){
			img->at(w, h).red = 255;
			img->at(w, h).green = 0;
			img->at(w, h).blue = 0;
		}
	}
	// or
	img->at(5, 2).red = 255;

	// with pointers:

	*(img->data(5, 2).red) = 255;
	// or
	*img->data(5, 2, Channel::Red) = 255;
	saveImg(*img, "test.jpg");
	std::cin.ignore();
	cout << "FUCK" << endl;
}