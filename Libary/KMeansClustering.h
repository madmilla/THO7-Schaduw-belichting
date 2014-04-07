#ifndef KMEANSCLUSTERING_H
#define KMEANSCLUSTERING_H

#include "ImageV2.h"
#include "Filter.h"

class KMeansClustering : public Filter{
private:
	int kValue;
	unsigned char ** cluster; //clusters are saved here
public:
	//image, and k amount of clusters
	KMeansClustering(Image img, int k);
	//make clusters
	void clusterRGB();
};
#endif