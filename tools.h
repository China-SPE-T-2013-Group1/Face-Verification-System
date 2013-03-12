#include "stdafx.h"

vector<Mat> openTrainingSet(string name);
Mat asRowMatrix(const vector<Mat>& src, int rtype, double alpha = 1, double beta = 0);
Mat norm_0_255(const Mat& src);
vector<int> argsort(const Mat& src, bool ascending);
void sortMatrixColumnsByIndices(const Mat& src, const vector<int>& indices, Mat& dst);
Mat sortMatrixColumnsByIndices(const Mat&  src, const vector<int>& indices);

// Removes duplicate elements in a given vector.
template<typename _Tp>
inline vector<_Tp> remove_dups(const vector<_Tp>& src)
{
    typedef typename set<_Tp>::const_iterator constSetIterator;
    typedef typename vector<_Tp>::const_iterator constVecIterator;
    set<_Tp> set_elems;
    for (constVecIterator it = src.begin(); it != src.end(); ++it)
        set_elems.insert(*it);
    vector<_Tp> elems;
    for (constSetIterator it = set_elems.begin(); it != set_elems.end(); ++it)
        elems.push_back(*it);
    return elems;
}