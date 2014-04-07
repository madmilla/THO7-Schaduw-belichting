#include "thresholdDetermination.h"
#include <iostream>

void thresholdDetermination::convert() {

	meanCorners = (getIntensity(getPixel(0, 0)) + getIntensity(getPixel(nWidth-1, 0)) + getIntensity(getPixel(0, nHeight-1)) + getIntensity(getPixel(nWidth-1, nHeight-1))) / 4;
	meanAllOthers = 0;

	for (int h = 0; h < nHeight; ++h) {
		for (int w = 0; w < nWidth; ++w) {

			if (!((w == 0 && h == 0) || (w == nWidth-1 && h == 0) || (w == 0 && h == nHeight-1) || (w == nWidth-1 && h == nHeight-1))) {
				meanAllOthers += getIntensity(getPixel(w, h));
			}

		}
	}

	meanAllOthers /= ((nWidth*nHeight)-4);

	tOld = 0;
	tNew = (meanCorners + meanAllOthers) / 2;


	unsigned int u1count = 0, u2count = 0;

	while (tNew != tOld) {

		meanAllOthers = 0;
		meanCorners = 0;
		for (int h = 0; h < nHeight; ++h) {
			for (int w = 0; w < nWidth; ++w) {


				if (getIntensity(getPixel(w,h)) < tNew){
					meanCorners += getIntensity(getPixel(w,h));
					u1count++;
				} else if(getIntensity(getPixel(w,h)) >= tNew){
					meanAllOthers +=  getIntensity(getPixel(w,h));
					u2count++;
				}

			}
		}

		meanCorners /= u1count;
		meanAllOthers /= u2count;
		u1count = 0;
		u2count = 0;
		tOld = tNew;
		tNew = (meanCorners + meanAllOthers) / 2;

	}

	for (int h = 0; h < nHeight; ++h) {
		for (int w = 0; w < nWidth; ++w) {

			if (getIntensity(getPixel(w,h)) < tNew){
				setPixel(w, h, 0);
			} else if (getIntensity(getPixel(w,h)) >= tNew){
				setPixel(w, h, 0xFFFFFF);
			}

		}
	}

}