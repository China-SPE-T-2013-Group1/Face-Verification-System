#include "stdafx.h"

vector<Mat> openTrainingSet(string name);
int noOfImages(string name);
std::vector<Rect> detectionAndDisplay2(Mat frame, CascadeClassifier face_cascade, CascadeClassifier eyes_cascade);
Mat showNormalizeFace2(vector<Rect> detectedfaces, Mat frame);