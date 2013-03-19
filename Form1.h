#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "facerec.hpp"
#include "tools.h"
using namespace cv;

static Mat frame;
static VideoCapture cap(0);
static vector<Mat> images = openTrainingSet("Test");
static int v[26] = {0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,4};
static vector<int> labels(begin(v), end(v));
static int num_components = 3;
static Eigenfaces eigenFace(images, labels, num_components);
static Fisherfaces fisherFace(images, labels, num_components);

namespace FaceVerificationSystem
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	//int a;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
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
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(202, 95);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(110, 38);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Train";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// aquisitionTimer
			// 
			this->aquisitionTimer->Enabled = true;
			this->aquisitionTimer->Interval = 200;
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
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(330, 152);
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
			imwrite( "Gray_Image.jpg", frame );
		}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
					cap >> frame;
					imshow("Webcam", frame);
					if (waitKey(30) >= 0) 
					{
						imshow("Capture", frame);
					}
			 }
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void timer1_Tick_1(System::Object^  sender, System::EventArgs^  e)
		 {
			cap >> frame;
			
			Mat testImage;
			cv::cvtColor(frame, testImage, CV_RGB2GRAY);
			
			label1->Text = "Eigenfaces results: " + Convert::ToString(eigenFace.predict(testImage));
			label2->Text = "Fisherfaces results: " + Convert::ToString(fisherFace.predict(testImage));
		 }
};
}