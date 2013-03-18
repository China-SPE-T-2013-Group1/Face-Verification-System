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
#include <windows.h>

void test()
{
	vector<Mat> images = openTrainingSet("Alexis");

	// Number of components
    int num_components = 3;

	//Fisherfaces fisherTest = Fisherfaces();
	vector<int> labels;
	labels.push_back(0);
	labels.push_back(1);
	labels.push_back(1);
	labels.push_back(1);
	Fisherfaces fisherTest(images, labels, num_components);

	Mat testImage = imread("Training set/Alexis/2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	int a = fisherTest.predict(testImage);
	if (a == 0)
	{
		MessageBox(NULL, L"0", L"", MB_OK);
	}
	if (a == 1)
	{
		MessageBox(NULL, L"1", L"", MB_OK);
	}
}