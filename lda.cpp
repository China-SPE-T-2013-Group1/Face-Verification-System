#include "stdafx.h"
#include "lda.h"
#include "Form1.h"
#include "tools.h"
#include <iostream>
#include <map>
using namespace std;
#include <vector>
#include <set>
#include "eigenvalueDecomposition.h"


void LDA::compute(const Mat& src, const vector<int>& labels)
{
    Mat data;
    // ensure working matrix is double precision
    src.convertTo(data, CV_64FC1);
    // maps the labels, so they're ascending: [0,1,...,C]
    vector<int> mapped_labels(labels.size());
    vector<int> num2label = remove_dups(labels);
    map<int, int> label2num;
    for (int i = 0; i < num2label.size(); i++)
        label2num[num2label[i]] = i;
    for (int i = 0; i < labels.size(); i++)
        mapped_labels[i] = label2num[labels[i]];
    // get sample size, dimension
    int N = data.rows;
    int D = data.cols;
    // number of unique labels
    int C = num2label.size();
    // we can't do a LDA on one class, what do you
    // want to separate from each other then?
    if(C == 1) {
        string error_message = "At least two classes are needed to perform a LDA. Reason: Only one class was given!";
        CV_Error(CV_StsBadArg, error_message);
    }
    // throw error if less labels, than samples
    if (labels.size() != N) {
        string error_message = format("The number of samples must equal the number of labels. Given %d labels, %d samples. ",labels.size(), N);
        CV_Error(CV_StsBadArg, error_message);
    }
    // warn if within-classes scatter matrix becomes singular
    if (N < D)
        cout << "Warning: Less observations than feature dimension given!"
        << "Computation will probably fail."
        << endl;
    // clip number of components to be a valid number
    if ((_num_components <= 0) || (_num_components > (C - 1)))
        _num_components = (C - 1);
    // holds the mean over all classes
    Mat meanTotal = Mat::zeros(1, D, data.type());
    // holds the mean for each class
    vector<Mat> meanClass(C);
    vector<int> numClass(C);
    // initialize
    for (int i = 0; i < C; i++) {
        numClass[i] = 0;
        meanClass[i] = Mat::zeros(1, D, data.type()); //! Dx1 image vector
    }
    // calculate sums
    for (int i = 0; i < N; i++) {
        Mat instance = data.row(i);
        int classIdx = mapped_labels[i];
        add(meanTotal, instance, meanTotal);
        add(meanClass[classIdx], instance, meanClass[classIdx]);
        numClass[classIdx]++;
    }
    // calculate total mean
    meanTotal.convertTo(meanTotal, meanTotal.type(), 1.0 / static_cast<double> (N));
    // calculate class means
    for (int i = 0; i < C; i++) {
        meanClass[i].convertTo(meanClass[i], meanClass[i].type(), 1.0 / static_cast<double> (numClass[i]));
    }
    // subtract class means
    for (int i = 0; i < N; i++) {
        int classIdx = mapped_labels[i];
        Mat instance = data.row(i);
        subtract(instance, meanClass[classIdx], instance);
    }
    // calculate within-classes scatter
    Mat Sw = Mat::zeros(D, D, data.type());
    mulTransposed(data, Sw, true);
    // calculate between-classes scatter
    Mat Sb = Mat::zeros(D, D, data.type());
    for (int i = 0; i < C; i++) {
        Mat tmp;
        subtract(meanClass[i], meanTotal, tmp);
        mulTransposed(tmp, tmp, true);
        add(Sb, tmp, Sb);
    }
    // invert Sw
    Mat Swi = Sw.inv();
    // M = inv(Sw)*Sb
    Mat M;
    gemm(Swi, Sb, 1.0, Mat(), 0.0, M);
    EigenvalueDecomposition es(M);
    _eigenvalues = es.eigenvalues();
    _eigenvectors = es.eigenvectors();
    // reshape eigenvalues, so they are stored by column
    _eigenvalues = _eigenvalues.reshape(1, 1);
    // get sorted indices descending by their eigenvalue
    vector<int> sorted_indices = argsort(_eigenvalues, false);
    // now sort eigenvalues and eigenvectors accordingly
    _eigenvalues = sortMatrixColumnsByIndices(_eigenvalues, sorted_indices);
    _eigenvectors = sortMatrixColumnsByIndices(_eigenvectors, sorted_indices);
    // and now take only the num_components and we're out!
    _eigenvalues = Mat(_eigenvalues, Range::all(), Range(0, _num_components));
    _eigenvectors = Mat(_eigenvectors, Range::all(), Range(0, _num_components));
}