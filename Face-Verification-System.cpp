// Face-Verification-System.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace FaceVerificationSystem;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());

	Mat src1, src2, dst;
	double alpha = 0.5; double beta; double input;

	src1 = imread("funny.jpg");
	src2 = imread("funny2.jpg");

	if (!src1.data){printf("Error loading src1 \n"); return -1;}
	if (!src2.data){printf("Error loading src1 \n"); return -1;}

	namedWindow("Image 1", 1);
	imshow("Image 1", src1);

	namedWindow("Image 2", 1);
	imshow("Image 2", src2);

	namedWindow("Linear Blend", 1);

	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);
	imshow("Linear Blend", dst);

	waitKey(0);

	VideoCapture cap(0);
	if (!cap.isOpened()) return -1;

	Mat frame;
	namedWindow("Webcam", 1);
	for(;;)
	{
		cap >> frame;
		imshow("Webcam", frame);
		if(waitKey(30) >= 0) break;
	}

	waitKey(0);

	return 0;
}
