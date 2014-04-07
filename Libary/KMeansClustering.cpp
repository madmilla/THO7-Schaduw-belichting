#include "stdafx.h"
#include "KMeansClustering.h"
#include <random>
#include <string>
#include <iostream>
#define maxIterations 20;

KMeansClustering::KMeansClustering(Image img, int k) : Filter(img){
	kValue = k;
}

void KMeansClustering::clusterRGB(){
	//init: choose k random pixel values as means
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, image.Width() - 1); // pick x coordinate
	std::uniform_int_distribution<> distr2(0, image.Height() - 1); // pick y coordinate

	cluster = new unsigned char*[kValue];//cluster will save the chosen clusters
	for (int i = 0; i < kValue; i++){
		cluster[i] = new unsigned char[3];
	}
	int i = 0;
	while (i < kValue){
		int x = distr(eng);
		int y = distr2(eng);

		cluster[i][0] = *image.Data(x, y, 0);//save cluster red value
		cluster[i][1] = *image.Data(x, y, 1);//save cluster green value
		cluster[i][2] = *image.Data(x, y, 2);//save cluster blue value
		i++; //maybe there should be a check that this aren't the same values, so the clusters won't  the same
	}

	//assign pixels to cluster
	int ** allPixels = new int*[image.Width()];
	for (int i = 0; i < image.Width(); i++){
		allPixels[i] = new int[image.Height()];
	}

	int * average = new int[kValue * 3];
	for (int i = 0; i < kValue * 3; i++){
		average[i] = 0;
	}
	bool changed = true;
	int iterations = 0;
	int maxIterations1 = maxIterations;
	while (changed == true && iterations < maxIterations1){//average doesn't change anymore
		for (int y = 0; y < image.Height(); y++){
			for (int x = 0; x < image.Width(); x++){
				int lowestDifference = abs(cluster[0][0] - *image.Data(x, y, 0)) + abs(cluster[0][1] - *image.Data(x, y, 1)) + abs(cluster[0][2] - *image.Data(x, y, 2));
				int lowestDifferenceCluster = 0;
				for (int k = 0; k < kValue; k++){
					if (abs(cluster[k][0] - *image.Data(x, y, 0)) + abs(cluster[k][1] - *image.Data(x, y, 1)) + abs(cluster[k][2] - *image.Data(x, y, 2)) < lowestDifference){
						lowestDifferenceCluster = k;
					}
				}
				//assign each pixel(from image data) to the nearest mean
				allPixels[x][y] = lowestDifferenceCluster;
			}
		}
		int ** allMeans = new int*[kValue];
		int * meansAverage = new int[kValue];
		for (int i = 0; i < kValue; i++){
			allMeans[i] = new int[3];
			allMeans[i][0] = 0;
			allMeans[i][1] = 0;
			allMeans[i][2] = 0;
			meansAverage[i] = 1;
		}

		for (int y = 0; y < image.Height(); y++){
			for (int x = 0; x < image.Width(); x++){
				allMeans[allPixels[x][y]][0] += *image.Data(x, y, 0);
				allMeans[allPixels[x][y]][1] += *image.Data(x, y, 1);
				allMeans[allPixels[x][y]][2] += *image.Data(x, y, 2);
				meansAverage[allPixels[x][y]] += 1;
			}
		}
		changed = false;
		for (int j = 0; j < kValue; j++){
			cluster[j][0] = allMeans[j][0] / meansAverage[j];
			cluster[j][1] = allMeans[j][1] / meansAverage[j];
			cluster[j][2] = allMeans[j][2] / meansAverage[j];

			if (abs(average[j] - cluster[j][0]) > 0 || abs(average[j*2] - cluster[j][1]) > 0 || abs(average[j*3] - cluster[j][2]) > 0){
				changed = true;
				average[j] = cluster[j][0];
				average[j*2] = cluster[j][1];
				average[j*3] = cluster[j][2];
			}
		}
		iterations++;
	}
	if (iterations == maxIterations1){
		std::cout << "max iterations\n";
	}

	//final: change all pixels colors to match color of the
	//cluster mean

	for (int y = 0; y < image.Height(); y++){
		for (int x = 0; x < image.Width(); x++){
			*editedImage.Data(x, y, 0) = cluster[allPixels[x][y]][0];
			*editedImage.Data(x, y, 1) = cluster[allPixels[x][y]][1];
			*editedImage.Data(x, y, 2) = cluster[allPixels[x][y]][2];
		}
	}
}