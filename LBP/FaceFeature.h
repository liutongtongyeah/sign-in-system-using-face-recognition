#include<opencv2/highgui/highgui.hpp>
#include<opencv2/contrib/contrib.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>

#include <iostream>
using namespace std;
using namespace cv;

extern "C" __declspec(dllexport) int InitFeature(CvSize faceSz);

extern "C" __declspec(dllexport) void GetFeature(CvArr *faceImg32, CvMat *ft);

extern "C" __declspec(dllexport) void ReleaseFeature();
