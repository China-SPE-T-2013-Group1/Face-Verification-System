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

static string window_name2 = "Normalized Face";

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

void testYale2(Eigenfaces* eigenFace, Fisherfaces* fisherFace)
{
	FILE * file;
	file = fopen("YaleDatabaseTestResults2.csv","w");
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
		for (int i = 12; i < 13; i++)
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

void testYale3(Eigenfaces* eigenFace, Fisherfaces* fisherFace)
{
	FILE * file;
	file = fopen("YaleDatabaseTestResults3.csv","w");
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
		for (int i = 8; i < 13; i++)
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

std::vector<Rect> detectionAndDisplay(Mat frame, CascadeClassifier face_cascade, CascadeClassifier eyes_cascade)
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0, Size(80, 80));

    for (int i = 0; i < faces.size(); i++)
    {
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        if( eyes.size() == 2)
        {
            //-- Draw the face
            Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
            ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
            for( int j = 0; j < eyes.size(); j++ )
            { //-- Draw the eyes
                Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 ); 
                int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                circle( frame, center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
            }
         }
    } 
	return faces;
}

Mat showNormalizeFace(vector<Rect> detectedfaces, Mat frame)
{
	Mat faceROI;
	if (detectedfaces.size() > 0)
	{
		Mat frame_gray;
		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		faceROI = frame_gray(detectedfaces[0]);
		cv::resize(faceROI, faceROI, frame.size());
		return faceROI;
	}
	return frame;
}