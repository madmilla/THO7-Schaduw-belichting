#include <cmath>
#include "image.h"

#pragma once

class thresholdDetermination: public image  {

private:
	u_int64 meanCorners, meanAllOthers, tOld, tNew;

public:
	thresholdDetermination(CImage &c):image(c){};
	thresholdDetermination(image &c):image(c){};
	void convert();

	inline unsigned int getIntensity(unsigned int pixel) {
		return std::floor(0.11f * (pixel & 0xFF) + 0.59f * ((pixel >> 8) & 0xFF) + 0.30f * (pixel >> 16));
	}

};