//#ifndef LIGHTPREP_H
//#define LIGHTPREP_H
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/contrib/contrib.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>

#include <iostream>
using namespace std;
using namespace cv;

extern "C" __declspec(dllexport) void InitLight(CvSize faceSz);

extern "C" __declspec(dllexport) void GenFilterKernel(CvMat *h, int filterType, /*bool bHighpass,*/ double d0, int order = 1);

extern "C" __declspec(dllexport) void RunLightPrep(CvMat *faceImg8);

extern "C" __declspec(dllexport) void ReleaseLight();
