#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
#include "tools.h"

vector<Mat> openTrainingSet(string name)
{
	int imageNumberInt = 1;
	char imageNumberString[4];
	sprintf(imageNumberString, "%d", imageNumberInt);
	Mat image;
	vector<Mat> out;
	image = imread("Training set/" + name + "/" + imageNumberString + ".jpg", CV_LOAD_IMAGE_GRAYSCALE);		
	
	while (image.data)
	{
		out.push_back(image);
		imageNumberInt++;
		sprintf(imageNumberString, "%d", imageNumberInt);
		image = imread("Training set/" + name + "/" + imageNumberString + ".jpg", CV_LOAD_IMAGE_GRAYSCALE);
	}

	Mat a;
	return out;
}