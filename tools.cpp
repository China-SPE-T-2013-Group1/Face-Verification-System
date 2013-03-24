#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "facerec.hpp"
using namespace cv;
#include "tools.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <fstream>

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

// Function to count the number of images in a folder
int noOfImages(string name) {
	
	int imageNumberInt = 1;
	Mat image;
	char imageNumberString[4];
	sprintf(imageNumberString, "%d", imageNumberInt);
	image = imread("Training set/" + name + "/" + imageNumberString + ".jpg", CV_LOAD_IMAGE_GRAYSCALE);		
	
	while (image.data)
	{
		imageNumberInt++;
		sprintf(imageNumberString, "%d", imageNumberInt);
		image = imread("Training set/" + name + "/" + imageNumberString + ".jpg", CV_LOAD_IMAGE_GRAYSCALE);
	}

	return (imageNumberInt - 1);
}

// Function to test the program using the Yale database
void testYale(Eigenfaces* eigenFace, Fisherfaces* fisherFace)
{
	FILE * file;
	file = fopen("YaleDatabaseTestResults.csv","w");
	string imageName = "Test";
	char iChar[4];
	char jChar[4];
	int predict;
	char predictChar[1];
	Mat image;
	
	string a = "Training set/Yale";
	string b = "/";
	string c = ".jpg";
	
	fputs("Original;Eigenfaces;Fisherfaces\n", file);

	for (int j = 1; j < 16; j++)
	{
		sprintf(jChar, "%d", j);
		for (int i = 1; i < 12; i++)
		{
			sprintf(iChar, "%d", i);
			
			fputs(jChar, file);
			fputs(";", file);

			image = imread(a + jChar + b + iChar + c, CV_LOAD_IMAGE_GRAYSCALE);		
			
			predict = eigenFace->predict(image) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs(";", file);

			predict = fisherFace->predict(image) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs("\n", file);
		}
	}
	fclose(file);
}