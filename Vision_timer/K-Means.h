#pragma once
#include "Image.h"
#include <math.h>

#define KMEANS_MAX_ITERATIONS 25

class KMeans {
public:
	KMeans(int clusters);
	~KMeans();

	void Apply(Image & img);

private:
	int _Clusters;

	struct PixelSpot {
		int x, y, z;

		int index;
		double CentrumDistance;
		int Group;
	};

	struct PixelCentrum {
		int x, y, z;
		int Count;
	};

	inline double CalculateDistance(PixelSpot & p1, PixelCentrum & p2);
};

