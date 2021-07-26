#include<opencv2/highgui/highgui.hpp>
#include<opencv2/contrib/contrib.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>

#include <iostream>
using namespace std;
using namespace cv;

//extern int ex_blockCnt; // for Subspace_BlkFLD.cpp to use, seems unreachable
/*
faceSz is the same with the faceSz returned by InitAlign
Feature length is returned for initializing feature vectors.
If error occurs, 0 is returned.
*/
extern "C" __declspec(dllexport) int InitFeature(CvSize faceSz);


/*
ft32 is a column vector with type CV_FT_FC1
*/
extern "C" __declspec(dllexport) void GetFeature(CvArr *faceImg32, CvMat *ft);


/*
should be called before unloading the dll
*/
extern "C" __declspec(dllexport) void ReleaseFeature();
