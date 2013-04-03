#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "facerec.hpp"
using namespace cv;
#include "tools.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <fstream>

static Mat faceFrame;

static Mat test1(150, 150, CV_8UC3);
static Mat size(150, 150, CV_8UC3);

static string face_cascade_name = "haarcascade_frontalface_alt2.xml";
static string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
static CascadeClassifier face_cascade;
static CascadeClassifier eyes_cascade;

// Function to test the program using the Yale database
void testYale(Eigenfaces* eigenFace, Fisherfaces* fisherFace)
{
	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);

	FILE * file;
	file = fopen("YaleDatabaseTestResults.csv","w");
	string imageName = "Test";
	char iChar[4];
	char jChar[4];
	int predict;
	char predictChar[1];
	Mat image1;
	Mat image;
	
	string a = "Training set/Yale";
	string b = "/";
	string c = ".jpg";
	
	fputs("Original;Eigenfaces;Fisherfaces\n", file);

	for (int j = 1; j < 6; j++)
	{
		sprintf(jChar, "%d", j);
		for (int i = 1; i < 13; i++)
		{
			sprintf(iChar, "%d", i);
			
			fputs(jChar, file);
			fputs(";", file);

			image = imread(a + jChar + b + iChar + c);

			//imshow(a + jChar + b + iChar + c, image);

			faceFrame = showNormalizeFace(detectionAndDisplay(image, face_cascade, eyes_cascade), image);
			//resize(faceFrame, faceFrame, size.size(), 0, 0, INTER_NEAREST);

			predict = eigenFace->predict(faceFrame) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs(";", file);

			predict = fisherFace->predict(faceFrame) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs("\n", file);
		}
	}
	fclose(file);
}

void testYale2(Eigenfaces* eigenFace, Fisherfaces* fisherFace)
{
	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);

	FILE * file;
	file = fopen("YaleDatabaseTestResults.csv","w");
	string imageName = "Test";
	char iChar[4];
	char jChar[4];
	int predict;
	char predictChar[1];
	Mat image1;
	Mat image;
	
	string a = "Training set/Yale";
	string b = "/";
	string c = ".jpg";
	
	fputs("Original;Eigenfaces;Fisherfaces\n", file);

	for (int j = 1; j < 6; j++)
	{
		sprintf(jChar, "%d", j);
		for (int i = 12; i < 14; i++)
		{
			sprintf(iChar, "%d", i);
			
			fputs(jChar, file);
			fputs(";", file);

			image = imread(a + jChar + b + iChar + c);

			//imshow(a + jChar + b + iChar + c, image);

			faceFrame = showNormalizeFace(detectionAndDisplay(image, face_cascade, eyes_cascade), image);
			//resize(faceFrame, faceFrame, size.size(), 0, 0, INTER_NEAREST);

			predict = eigenFace->predict(faceFrame) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs(";", file);

			predict = fisherFace->predict(faceFrame) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs("\n", file);
		}
	}
	fclose(file);
}

void testYale3(Eigenfaces* eigenFace, Fisherfaces* fisherFace)
{
	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);

	FILE * file;
	file = fopen("YaleDatabaseTestResults.csv","w");
	string imageName = "Test";
	char iChar[4];
	char jChar[4];
	int predict;
	char predictChar[1];
	Mat image1;
	Mat image;
	
	string a = "Training set/Yale";
	string b = "/";
	string c = ".jpg";
	
	fputs("Original;Eigenfaces;Fisherfaces\n", file);

	for (int j = 1; j < 11; j++)
	{
		sprintf(jChar, "%d", j);
		for (int i = 7; i < 12; i++)
		{
			sprintf(iChar, "%d", i);
			
			fputs(jChar, file);
			fputs(";", file);

			image = imread(a + jChar + b + iChar + c);

			//imshow(a + jChar + b + iChar + c, image);

			faceFrame = showNormalizeFace(detectionAndDisplay(image, face_cascade, eyes_cascade), image);
			//resize(faceFrame, faceFrame, size.size(), 0, 0, INTER_NEAREST);

			predict = eigenFace->predict(faceFrame) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs(";", file);

			predict = fisherFace->predict(faceFrame) + 1;
			sprintf(predictChar, "%d", predict);
			fputs(predictChar, file);
			fputs("\n", file);
		}
	}
	fclose(file);
}