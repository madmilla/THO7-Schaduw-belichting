#include "stdafx.h"
#include "Histogram.h"
#include <iostream>

Histogram::Histogram(Image image){
	Histogram::image = image;
	total = image.Height() * image.Width();
	val = 0;
}

void Histogram::MakeAHistogram(int value, int channel){
	if ((value > 0) && (value <= 256)){
		val = value;
		aHistogram = new int[value];

		for (int i = 0; i < value; i++){
			aHistogram[i] = 0;
		}

		for (int r = 0; r < image.Height(); r++){
			for (int c = 0; c < image.Width(); c++){
				aHistogram[(int)((*image.Data(c,r, channel) * value) / 256)]++;
			}
		}
	}
	else{
		std::cerr << "value klopt niet";
	}
}

int * Histogram::getHistogram(){
	return aHistogram;
}

int Histogram::getTotal(){
	return total;
}


void Histogram::SaveHistogram(const char * filename){
	ofstream greyfilecsv;
	string redcsv = "Histogram_";
	redcsv += filename;
	redcsv += ".csv";
	greyfilecsv.open(redcsv, ios::out | ios::binary);
	for (int i = 0; i < val; i++){
		double test = (double)((double)aHistogram[i] / ((double)total));
		greyfilecsv << i << ";" << setprecision(10) << fixed << showpoint << test << "\n";
	}
	greyfilecsv.close();
}