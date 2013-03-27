/*#include "stdafx.h"
#include "tests.h"
#include "facerec.hpp"
#include "tools.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
using namespace cv;*/



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