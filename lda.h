#include "stdafx.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

class LDA {

private:

	int _num_components;
	Mat _eigenvectors;
	Mat _eigenvalues;

public:

	//! initialize with 0 components and data given in rows
	LDA() :
		_num_components(0){};

	//! initialize with num_components and specify how observations are given
	LDA(int num_components) :
		_num_components(num_components) {};

	//! initialize and perform a discriminant analysis with given data in src and labels
	LDA(const Mat& src,
			const vector<int>& labels,
			int num_components = 0) :
				_num_components(num_components)
	{
		this->compute(src, labels); //! compute eigenvectors and eigenvalues
	}
	//! initialize and perform a discriminant analysis with given data in src and labels
	LDA(const vector<Mat>& src,
			const vector<int>& labels,
			int num_components = 0) :
				_num_components(num_components)
	{
		this->compute(src, labels); //! compute eigenvectors and eigenvalues
	}
	//! destructor
	~LDA() {}
	//! compute the discriminants for data in src and labels
	void compute(const Mat& src, const vector<int>& labels);
	//! compute the discriminants for data in src and labels
	void compute(const vector<Mat>& src, const vector<int>& labels);
	//! project
	Mat eigenvectors() const { return _eigenvectors; };
	//! returns the eigenvalues of this LDA
	Mat eigenvalues() const { return _eigenvalues; }
};