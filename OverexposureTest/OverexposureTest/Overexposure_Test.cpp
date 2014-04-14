#include "Overexposure_Test.h"

using namespace ImageLib;
using namespace std;

/**
*	\Atheur Hendrik Cornelisse
*
*	\Date 14/04/2014
*/

int TotalPixels = 0;
int Overexposed_pixels = 0;
int Big_Y, Small_Y;
int sum = 0;
int temp_Red = 0;
int temp_Green = 0;
int temp_Blue = 0;
int count_Pixels = 0;
int average_Red, average_Green, average_Blue;
int temp_Red_Black, temp_Blue_Black;
float percentage = 0;
bool count_Pix = false;

/** Constuctor */
Overexposure_Test::Overexposure_Test(){
}

bool Overexposure_Test::Overexposure_Detection(shared_ptr<ImageRGB> img, int Top_Left_X, int Top_Left_Y, int Top_Right_X, int Top_Right_Y, int Bottom_Left_X, int Bottom_Left_Y, int Bottom_Right_X, int Bottom_Right_Y){

	/**
	*	Making a bounding box with the coordinates of the license plate.
	*	Check what the smalles top Y value is.
	*/
	if (Top_Left_Y < Top_Right_Y){
		Small_Y = Top_Left_Y;
	}
	else{
		Small_Y = Top_Right_Y;
	}
	
	/** Check what the biggest bottom Y value is. */
	if (Bottom_Left_Y > Bottom_Right_Y){
		Big_Y = Bottom_Left_Y;
	}
	else{
		Big_Y = Bottom_Right_Y;
	}

	/** Total pixels of het license plate. */
	TotalPixels = (Bottom_Right_X - Top_Left_X) * (Big_Y - Small_Y);

	/**
	*	1 for loop is for the height of the license plate and the other is for the width of the license plate.
	*	from the edges of the license plate we take 5 pixels less so that code beyond won't get use values outside the license plate.
	*/ 
	for (int y = Small_Y + 5; y < Big_Y - 5; y++){
		for (int x = Top_Left_X + 5; x < Bottom_Right_X - 5; x++){

			/** The X and Y gradient are calculated with the color blue. */
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue * 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue * 2 - *img->data(x - 1, y + 1).blue;

			sum = abs(xGradient) + abs(yGradient);
			
			/** If the sum of the X and Y gradient bigger is than 255 it will be detected as edge. */
			if (sum >= 255){
				percentage = ((float)Overexposed_pixels / (float)TotalPixels) * 100;

				/** If percentage is 1 or bigger than 1 then return true. */
				if (percentage >= 1){
					return true;
				}
				
				/** This code will look for white pixels around the gradient edge. */
				for (int h = y - 5; h < y + 5; h++){
					for (int w = x - 5; w < x + 5; w++){
						/** If the red, green and blue are bigger than 210 then it is overexposed. */
						if ((*img->data(w, h).red > 210) && (*img->data(w, h).green > 210) && (*img->data(w, h).blue > 210)){
							if (count_Pix == false){
								Overexposed_pixels++;
								count_Pix = true;
							}	
						}
					}
				}
			}
			count_Pix = false;
		}
	}
	/** If percentage < 1 return false. */
	return false;
}

void Overexposure_Test::Overexposure_Removal(shared_ptr<ImageRGB> img, int Top_Left_X, int Top_Left_Y, int Top_Right_X, int Top_Right_Y, int Bottom_Left_X, int Bottom_Left_Y, int Bottom_Right_X, int Bottom_Right_Y){
	
	/**
	*	Making a bounding box with the coordinates of the license plate.
	*	Check what the smalles top Y value is.
	*/
	if (Top_Left_Y < Top_Right_Y){
		Small_Y = Top_Left_Y;
	}
	else{
		Small_Y = Top_Right_Y;
	}

	/** Check what the biggest bottom Y value is. */
	if (Bottom_Left_Y > Bottom_Right_Y){
		Big_Y = Bottom_Left_Y;
	}
	else{
		Big_Y = Bottom_Right_Y;
	}

	/**
	*	1 for loop is for the height of the license plate and the other is for the width of the license plate. 
	*	from the edges of the license plate we take 5 pixels less so that code beyond won't use values outside the license plate.
	*/
	for (int y = Small_Y + 5; y < Big_Y - 5; y++){
		for (int x = Top_Left_X + 5; x < Bottom_Right_X - 5; x++){

			/** The X and Y gradient are calculated with the color blue. */
			int xGradient = *img->data(x - 1, y + 1).blue + *img->data(x - 1, y).blue * 2 + *img->data(x - 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x + 1, y).blue * 2 - *img->data(x + 1, y - 1).blue;
			int yGradient = *img->data(x - 1, y - 1).blue + *img->data(x, y - 1).blue * 2 + *img->data(x + 1, y - 1).blue - *img->data(x + 1, y + 1).blue - *img->data(x, y + 1).blue * 2 - *img->data(x - 1, y + 1).blue;

			sum = abs(xGradient) + abs(yGradient);

			/** If the sum of the X and Y gradient bigger is than 255 it will be detected as edge. */
			if (sum >= 255){
				for (int h = y - 5; h < y + 5; h++){
					for (int w = x - 5; w < x + 5; w++){
						/** 
						*	The red value minus green value or vice versa so that the value can't be negative. 
						*	We do this so we can sie of there is a gray pixel.
						*/
							if (*img->data(w, h).green < *img->data(w, h).red){
								temp_Red_Black = *img->data(w, h).red - *img->data(w, h).green;
							}
							else{
								temp_Red_Black = *img->data(w, h).green - *img->data(w, h).red;
							}

							/** 
							*	The blue value minus green value or vice versa so that the value can't be negative. 
							*	We do this so we can sie of there is a gray pixel.
							*/
							if (*img->data(w, h).blue < *img->data(w, h).green){
								temp_Blue_Black = *img->data(w, h).green - *img->data(w, h).blue;
							}
							else{
								temp_Blue_Black = *img->data(w, h).blue - *img->data(w, h).green;
							}

							/** The minus of the collors must be < 30 and the red must be < 245 then we know ut is gray. */
							if ((temp_Red_Black < 30) && (temp_Blue_Black < 30) && (*img->data(w, h).red < 245)){
								/** If the pixel is gray then set the pixel black. */
								img->at(w, h).red = 0;
								img->at(w, h).green = 0;
								img->at(w, h).blue = 0;
							}
							/** Check of the pixel is yellow. */
							if ((*img->data(w, h).red >= 185) && (*img->data(w, h).green >= 185) && (*img->data(w, h).blue <= 50)){
								/** Save the values of the yellow pixels. */
								temp_Red += *img->data(w, h).red;
								temp_Green += *img->data(w, h).green;
								temp_Blue += *img->data(w, h).blue;
								count_Pixels++;
						}
					}
				}
				/** Check of the value isn't zero. */
				if (count_Pixels != 0){
					/** Count the average of the colors. */
					average_Red = temp_Red / count_Pixels;
					average_Green = temp_Green / count_Pixels;
					average_Blue = temp_Blue / count_Pixels;

					for (int h = y - 5; h < y + 5; h++){
						for (int w = x - 5; w < x + 5; w++){
							/** If the values of the red, green and blue pixels are bigger than 210 then it wil be seen as white. */
							if ((*img->data(x, y).red > 210) && (*img->data(w, h).green > 210) && (*img->data(w, h).blue > 210)){
								/** The white pixels will get the average of the yellow color. */
								img->at(w, h).red = average_Red;
								img->at(w, h).green = average_Green;
								img->at(w, h).blue = average_Blue;
							}
						}
					}
					/** The values to get the average yellow color will be set to zero. */
					average_Red = 0;
					average_Green = 0;
					average_Blue = 0;
					temp_Red = 0;
					temp_Green = 0;
					temp_Blue = 0;
					count_Pixels = 0;
				}
			}
		}
	}
}
