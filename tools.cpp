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

static string face_cascade_name = "haarcascade_frontalface_alt2.xml";
static string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
static CascadeClassifier face_cascade;
static CascadeClassifier eyes_cascade;

static Mat size(150, 150, CV_8UC3);

//Function which returns a matrix containing the imagages contained in a SINGLE folder
vector<Mat> openTrainingSet(string name)
{
	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);

	Mat image;
	Mat faceFrame;

	int imageNumberInt = 1;
	char imageNumberString[4];
	sprintf(imageNumberString, "%d", imageNumberInt);
	
	vector<Mat> out;
	image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");	
	//resize(image, image, size.size(), 0, 0, INTER_NEAREST);
	//cvtColor(image, image, CV_BGR2GRAY);

	while (image.data)
	{
		image = showNormalizeFace(detectionAndDisplay(image, face_cascade, eyes_cascade), image);
		resize(image, image, size.size(), 0, 0, INTER_NEAREST);
	//	cvtColor(image, image, CV_BGR2GRAY);
		out.push_back(image);
		//imshow(name, image);
		imageNumberInt++;
		sprintf(imageNumberString, "%d", imageNumberInt);
		
		image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");
	}

	Mat a;
	return out;
}

vector<Mat> openTrainingSet2(string name)
{
	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);

	Mat faceFrame;
	Mat image;

	int imageNumberInt = 1;
	char imageNumberString[4];
	sprintf(imageNumberString, "%d", imageNumberInt);
	
	vector<Mat> out;
	image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");		
	
	faceFrame = showNormalizeFace(detectionAndDisplay(image, face_cascade, eyes_cascade), image);
	resize(faceFrame, faceFrame, size.size(), 0, 0, INTER_NEAREST);


//	imshow(name, faceFrame);

	while (image.data)
	{
		out.push_back(faceFrame);
		imageNumberInt++;
		sprintf(imageNumberString, "%d", imageNumberInt);
		
		faceFrame = showNormalizeFace(detectionAndDisplay(image, face_cascade, eyes_cascade), image);
		resize(faceFrame, faceFrame, size.size(), 0, 0, INTER_NEAREST);

		image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");
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

std::vector<Rect> detectionAndDisplay2(Mat frame, CascadeClassifier face_cascade, CascadeClassifier eyes_cascade)
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
          /*  Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
            ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
            for( int j = 0; j < eyes.size(); j++ )
            { //-- Draw the eyes
                Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 ); 
                int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                circle( frame, center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
            }*/
        }
    }
	return faces;
}

Mat showNormalizeFace2(vector<Rect> detectedfaces, Mat frame)
{
	Mat faceROI;
	Mat frame1;

	if (detectedfaces.size() > 0)
	{
		Mat frame_gray;
		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		faceROI = frame_gray(detectedfaces[0]);
		cv::resize(faceROI, faceROI, frame.size());
		return faceROI;
	}
	cvtColor(frame, frame1, CV_BGR2GRAY);
	return frame1;
}