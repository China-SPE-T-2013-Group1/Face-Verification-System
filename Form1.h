#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "facerec.hpp"
#include "tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vcclr.h>

using namespace cv;

static Mat frame;
static Mat faceFrame;
static VideoCapture cap(0);
static vector<Mat> images;
static vector<String> names ;
static vector<int> labels;
static int num_components = 10;
static Eigenfaces* eigenFace;
static Fisherfaces* fisherFace;

static Mat testImage;
static Mat test1(150, 150, CV_8UC3);

static string face_cascade_name = "haarcascade_frontalface_alt2.xml";
static string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
static CascadeClassifier face_cascade;
static CascadeClassifier eyes_cascade;

#include <iostream>
#include "cv.h"
#include "highgui.h"

namespace FaceVerificationSystem
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			face_cascade.load(face_cascade_name);
			eyes_cascade.load(eyes_cascade_name);
			string name;
			vector<Mat> newPerson;
			int increment = 0;
			
			fstream file ("Training set/dataBaseNames.txt");
			while ( !file.eof() )
			{
				getline(file,name);
				newPerson = openTrainingSet(name);
				images.insert(images.end(),newPerson.begin(),newPerson.end());
				int a = noOfImages(name);
				for(int i=0;i < noOfImages(name); i++)
				{
					labels.push_back(increment);
				}
				names.push_back(name);
				increment++;
			}
			names.push_back("Not recognized");
			eigenFace = new Eigenfaces(images, labels, num_components);
			fisherFace = new Fisherfaces(images, labels, num_components);
			// testYale3(eigenFace, fisherFace);
		}
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Timer^  aquisitionTimer;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Timer^  recognitionTimer;
	private: System::Windows::Forms::TextBox^  textBox1;


	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->aquisitionTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->recognitionTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(18, 95);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 20);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Train";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// aquisitionTimer
			// 
			this->aquisitionTimer->Enabled = true;
			this->aquisitionTimer->Interval = 250;
			this->aquisitionTimer->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(163, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Eigenfaces results:";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(14, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(167, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Fisherfaces results:";
			// 
			// recognitionTimer
			// 
			this->recognitionTimer->Enabled = true;
			this->recognitionTimer->Interval = 1000;
			this->recognitionTimer->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick_1);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(130, 95);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 3;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(330, 152);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Form1";
			this->Text = L"Face verification system";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			char a[1];
			System::String^ noms = this->textBox1->Text;
			char* nomc = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(noms);
			sprintf(a, "%d", noOfImages(nomc) + 1);

			System::String^ str = "Training set/" + this->textBox1->Text + "/";
			char* str2 = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
			strcat(str2, a);
			strcat(str2, ".jpg");
			imwrite(str2, frame);
		}
		private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
		{
			cap >> frame;
			imshow("Webcam", frame);
		}
		private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e)
		{
		}
		private: System::Void timer1_Tick_1(System::Object^  sender, System::EventArgs^  e)
		{
			cap >> frame;

			faceFrame = showNormalizeFace(detectionAndDisplay(frame, face_cascade, eyes_cascade), frame);
			resize(faceFrame, faceFrame, test1.size(), 0, 0, INTER_NEAREST);

			imshow("Normalized face", faceFrame);
			
			label1->Text = "Eigenfaces results: " + gcnew System::String(names[eigenFace->predict(frame)].c_str());
			label2->Text = "Fisherfaces results: " + gcnew System::String(names[fisherFace->predict(frame)].c_str());
		 }
};
}