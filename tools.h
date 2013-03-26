#include "stdafx.h"

vector<Mat> openTrainingSet(string name);
int noOfImages(string name);
void testYale(Eigenfaces* eigenFace, Fisherfaces* fisherFace);
void testYale2(Eigenfaces* eigenFace, Fisherfaces* fisherFace);
void testYale3(Eigenfaces* eigenFace, Fisherfaces* fisherFace);
std::vector<Rect> detectionAndDisplay(Mat frame, CascadeClassifier face_cascade, CascadeClassifier eyes_cascade);
Mat showNormalizeFace(vector<Rect> detectedfaces, Mat frame);