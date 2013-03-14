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
#include "facerec.hpp"

void test()
{
	vector<Mat> test = openTrainingSet("Alexis");

	// Build a matrix with the observations in row:
    Mat data = asRowMatrix(test, CV_32FC1);
  
	// Number of components to keep for the PCA:
    int num_components = 3;

	Fisherfaces fisherTest = Fisherfaces();
}