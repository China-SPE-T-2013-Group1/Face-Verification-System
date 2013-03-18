// Face-Verification-System.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include <string>
#include <stdlib.h>
#include "tools.h"
#include "fisherfaces.h"

using namespace FaceVerificationSystem;
using namespace std;

//Mat frame;
//Mat capture;
//VideoCapture cap(0);

[STAThreadAttribute]

int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());

	return 0;
}