#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
#include "tools.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//Function which returns a matrix containing the imagages contained in a SINGLE folder
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

// Function does not work but need to be implemented afterwards
/*void testSystem() {

	system("dir C:\ > C:\Users\Tof\Desktop\toto");
}
*/

// Function to count the number of images in a folder
int noOfImages(string name) {
	
	int imageNumberInt = 1;
	Mat image;
	char imageNumberString[4];
	sprintf(imageNumberString, "%d", imageNumberInt);
	image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");		
	
	while (image.data)
	{
		imageNumberInt++;
		sprintf(imageNumberString, "%d", imageNumberInt);
		image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");
	}

	return imageNumberInt;
}

