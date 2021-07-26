#include<opencv2/highgui/highgui.hpp>
#include<opencv2/contrib/contrib.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>

#include <iostream>
using namespace std;
using namespace cv;

#define PI	CV_PI

extern "C" __declspec(dllexport) void Magnitude(CvArr *input, CvMat *mag);

CvSize InitGabor(CvSize imgSize);


CvMat*** GaborConv(CvArr *faceImg32);


void ReleaseGabor();


void ShowGaborFace(CvArr *faceImg32);