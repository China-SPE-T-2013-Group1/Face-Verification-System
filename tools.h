#include "stdafx.h"

vector<Mat> openTrainingSet(string name);
Mat asRowMatrix(const vector<Mat>& src, int rtype, double alpha = 1, double beta = 0);
Mat norm_0_255(const Mat& src);
vector<int> argsort(const Mat& src, bool ascending);
void sortMatrixColumnsByIndices(const Mat& src, const vector<int>& indices, Mat& dst);
Mat sortMatrixColumnsByIndices(const Mat&  src, const vector<int>& indices);