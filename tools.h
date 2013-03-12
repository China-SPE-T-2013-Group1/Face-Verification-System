#include "stdafx.h"

vector<Mat> openTrainingSet(string name);
Mat asRowMatrix(const vector<Mat>& src, int rtype, double alpha = 1, double beta = 0);
Mat norm_0_255(const Mat& src);