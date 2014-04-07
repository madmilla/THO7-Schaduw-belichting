#include "K-Means.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <random>

KMeans::KMeans(int clusters) :
_Clusters(clusters)
{
	srand((unsigned int)time(0));
}


KMeans::~KMeans() {

}

void KMeans::Apply(Image & img) {
	RGBAPixel * PixelData = img.GetPixelData();

	int ImageWidth = img.GetWidth();
	int ImageHeight = img.GetHeight();
	int ImageSize = img.GetSize();

	// Choose k random pixel values as means
	PixelCentrum * ClusterCentrum = new PixelCentrum[_Clusters];
	for (int i = 0; i < _Clusters; i++) {
		int RandomValue = (int)(ImageSize * (float)rand() / (float)RAND_MAX);
		ClusterCentrum[i].x = PixelData[RandomValue].Red;
		ClusterCentrum[i].y = PixelData[RandomValue].Green;
		ClusterCentrum[i].z = PixelData[RandomValue].Blue;

		ClusterCentrum[i].Count = 0;
	}

	PixelSpot * Spots = new PixelSpot[ImageSize];
	for (int iterations = 0; iterations < KMEANS_MAX_ITERATIONS; iterations++) {
		for (int i = 0; i < ImageSize; i++) {
			//assign each pixel (from image data) to the nearest mean
			Spots[i].x = PixelData[i].Red;
			Spots[i].y = PixelData[i].Green;
			Spots[i].z = PixelData[i].Blue;
			Spots[i].index = i;

			Spots[i].CentrumDistance = -1;
			for (int centrum = 0; centrum < _Clusters; centrum++) {
				double distance = CalculateDistance(Spots[i], ClusterCentrum[centrum]);
				if (Spots[i].CentrumDistance > distance || Spots[i].CentrumDistance < 0) {
					Spots[i].CentrumDistance = distance;
					Spots[i].Group = centrum;
				}
			}

			ClusterCentrum[Spots[i].Group].Count++;
		}

		int UnchangedClusters = 0;
		for (int i = 0; i < _Clusters; i++) {
			// mean of cluster i <-- mean of all pixels with label i
			double newX = 0, newY = 0, newZ = 0;
			for (int counter = 0; counter < ImageSize; counter++) {
				if (Spots[counter].Group == i) {
					newX += Spots[counter].x;
					newY += Spots[counter].y;
					newZ += Spots[counter].z;
				}
			}
			//assign new cluster centers
			newX /= (double)(ClusterCentrum[i].Count);
			newY /= (double)(ClusterCentrum[i].Count);
			newZ /= (double)(ClusterCentrum[i].Count);

			if (ClusterCentrum[i].x != (int)newX ||
				ClusterCentrum[i].y != (int)newY ||
				ClusterCentrum[i].z != (int)newZ)
			{
				ClusterCentrum[i].x = (int)(newX);
				ClusterCentrum[i].y = (int)(newY);
				ClusterCentrum[i].z = (int)(newZ);
			}
			else {
				// when a cluster center isn't changed add a unchanged cluster
				UnchangedClusters++;
			}

			ClusterCentrum[i].Count = 0;
		}
		//when all clusters stopped changing the program quits
		if (UnchangedClusters == _Clusters) {
			std::cout << "Program Used: " << iterations << " iterations" << std::endl;
			break;
		}
	}

	for (int i = 0; i < _Clusters; i++) {
		for (int counter = 0; counter < ImageSize; counter++) {
			if (Spots[counter].Group == i) {
				PixelData[counter].Red = ClusterCentrum[i].x;
				PixelData[counter].Green = ClusterCentrum[i].y;
				PixelData[counter].Blue = ClusterCentrum[i].z;
			}
		}
	}

	delete[] ClusterCentrum;
	delete[] Spots;
}

inline double KMeans::CalculateDistance(PixelSpot & p1, PixelCentrum & p2) {
	double Distance = 0;
	//calculate the value distance between the pixel and the center pixel
	Distance = pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2) + pow((p2.z - p1.z), 2);
	Distance = sqrt(Distance);

	return Distance;
}