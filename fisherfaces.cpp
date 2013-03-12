#include "stdafx.h"
#include "fisherfaces.h"

#include "Form1.h"
#include "tools.h"

void test()
{
	vector<Mat> test = openTrainingSet("Alexis");

	// Build a matrix with the observations in row:
    Mat data = asRowMatrix(test, CV_32FC1);
  
	// Number of components to keep for the PCA:
    int num_components = 3;
 
    // Perform a PCA:
    PCA pca(data, Mat(), CV_PCA_DATA_AS_ROW, num_components);
	
    // And copy the PCA results:
    Mat mean = pca.mean.clone();
    Mat eigenvalues = pca.eigenvalues.clone();
    Mat eigenvectors = pca.eigenvectors.clone();
 
    // The mean face:
    imshow("avg", norm_0_255(mean.reshape(1, test[1].rows)));
 
    // The first three eigenfaces:
    imshow("pc1", norm_0_255(pca.eigenvectors.row(0)).reshape(1, test[0].rows));
    imshow("pc2", norm_0_255(pca.eigenvectors.row(1)).reshape(1, test[0].rows));
}