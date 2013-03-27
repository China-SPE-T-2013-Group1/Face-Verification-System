#include "stdafx.h"

vector<Mat> openTrainingSet(string name);
int noOfImages(string name);
std::vector<Rect> detectionAndDisplay(Mat frame, CascadeClassifier face_cascade, CascadeClassifier eyes_cascade);
Mat showNormalizeFace(vector<Rect> detectedfaces, Mat frame);