#include "stdafx.h"
#include "fisherfaces.h"
#include "Form1.h"
#include "tools.h"
#include "eigenvalueDecomposition.h"
#include <iostream>
#include <map>
using namespace std;
#include <vector>
#include <set>
#include "lda.h"

void test()
{
	vector<Mat> test = openTrainingSet("Alexis");

	// Build a matrix with the observations in row:
    Mat data = asRowMatrix(test, CV_32FC1);
  
	// Number of components to keep for the PCA:
    int num_components = 3;
 
    // Perform a PCA:
    //PCA pca(data, Mat(), CV_PCA_DATA_AS_ROW, num_components);
	
	// Perform LDA
	double d[11][2] = {
			{2, 3},
			{3, 4},
			{4, 5},
			{5, 6},
			{5, 7},
			{2, 1},
			{3, 2},
			{4, 2},
			{4, 3},
			{6, 4},
			{7, 6}};
	int c[11] = {0,0,0,0,0,1,1,1,1,1,1};
	// convert into OpenCV representation
	Mat _data = Mat(11, 2, CV_64FC1, d).clone();
	vector<int> _classes(c, c + sizeof(c) / sizeof(int));
	// perform the lda
	LDA lda(_data, _classes);

    // And copy the PCA results:
    //Mat mean = pca.mean.clone();
    //Mat eigenvalues = pca.eigenvalues.clone();
    //Mat eigenvectors = pca.eigenvectors.clone();
 
    // The mean face:
    //imshow("avg", norm_0_255(mean.reshape(1, test[1].rows)));
 
    // The first three eigenfaces:
    //imshow("pc1", norm_0_255(pca.eigenvectors.row(0)).reshape(1, test[0].rows));
    //imshow("pc2", norm_0_255(pca.eigenvectors.row(1)).reshape(1, test[0].rows));
}