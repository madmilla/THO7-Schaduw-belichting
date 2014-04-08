#include "Alg.h"

#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <ImageLoader.h>
#include <memory>

using namespace ImageLib;
using namespace std;

Alg::Alg(){
	
}

void Alg::Gradiant(int threshold, int l_b_x, int l_b_y, int r_b_x, int r_b_y, int r_o_x, int r_o_y, int l_o_x, int l_o_y){
	unique_ptr<ImageRGB> img = loadImg("license_plate_8.bmp");

	int Y_g, Y_k;

	if (l_b_y < r_b_y){
		Y_g = l_b_y;
	}
	else{
		Y_g = r_b_y;
	}

	/*if (r_b_x < r_o_x){
		X_g = r_o_x;
	}*/
	
	if (l_o_y > r_o_y){
		Y_k = l_o_y;
	}
	else{
		Y_k = r_o_y;
	}

	cout << Y_g << '\n';
	cout << Y_k << '\n';
	int overbelichting = 0;
	float procent = 0;
	int opp = (r_o_x - l_b_x) * (l_o_y - l_b_y);
	for (int y = Y_g; y < Y_k; y++){
		for (int x = l_b_x; x < r_o_x; x++){
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue* 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue* 2 - *img->data(x - 1, y + 1).blue;
			
			int sum = abs(xGradient) + abs(yGradient);

			if (sum > 255){
				sum = 255;
			}
			else if (sum < 0){
				sum = 0;
			}

			if (sum >= threshold){
				for (int h = y - 12; h < y + 12; h++){
					for (int w = x - 12; w < x + 12; w++){
						if ((*img->data(w, h).blue > 210) &&  (*img->data(w, h).green > 200) && (*img->data(w, h).red > 200))
						{	
							overbelichting++;
							img->at(w, h).red = 255;
							img->at(w, h).green = 0;
							img->at(w, h).blue = 0;
						}
					}
				}
			}
		}
	}
	procent = ((float)overbelichting / (float)opp) * 100;
	//cout << opp << '\n';
	//cout << overbelichting << '\n';
	cout << procent << '\n';
	saveImg(*img, "test.jpg");
}