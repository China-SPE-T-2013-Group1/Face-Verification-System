// Face-Verification-System.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include <string>
#include <stdlib.h>
#include "tools.h"

using namespace FaceVerificationSystem;
using namespace std;

[STAThreadAttribute]

int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	int value = 50;
	
	// Tests with images
	double alpha = 0.5; double beta; double input;

	//src1 = imread("funny.jpg");
	//src2 = imread("funny2.jpg");

	//if (!src1.data){printf("Error loading src1 \n"); return -1;}
	//if (!src2.data){printf("Error loading src1 \n"); return -1;}

	//namedWindow("Image 1", 1);
	//cvCreateTrackbar("track1", "Image 1", &value, 255, NULL);
	//imshow("Image 1", src1);

	//namedWindow("Image 2", 1);
	//imshow("Image 2", src2);

	//namedWindow("Linear Blend", 1);

	//beta = (1.0 - alpha);
	//addWeighted(src1, alpha, src2, beta, 0.0, dst);
	//imshow("Linear Blend", dst);

	// Create the main window and run it
	//Application::Run(gcnew Form1());


	// Creation of the video capture
	VideoCapture cap(0);
	if (!cap.isOpened()) return -1;

	Mat frame;
	Mat capture;
	static CvMat *eigenVec, *eigenVal;
	namedWindow("Webcam", 1);
	namedWindow("Capture", 1);
	
	//for(;;)
	{
		cap >> frame;
		imshow("Webcam", frame);
		if (waitKey(30) >= 0) 
		{
			// Here is how to get the eigenvalues of this Eigenfaces model:
//			Mat eigenvalues = frame("eigenvalues");
			// And we can do the same to display the Eigenvectors (read Eigenfaces):
		//	Mat W = model->getMat("eigenvectors");
			// Get the sample mean from the training data
	//		Mat mean = model->getMat("mean");
			capture = frame;
			imshow("Capture", capture);
			//int *a;
			//cvEigenVV(&frame, eigenVec, a, 1e-300);
		}
		//if(waitKey(30) >= 0) break;
	}

	vector<Mat> test = openTrainingSet("Alexis");
	int i = 1;
	char e[4];
	for (vector<Mat>::iterator t = test.begin(); t != test.end(); ++t)
	{
		sprintf(e, "%d", i);
		namedWindow(e, 1); // debug
		imshow(e, *t); // debug
		i++;
	}

	waitKey(0);
	return 0;

}

