/*
Fisherface/blockwise-Fisherface?
*/

#include<opencv2/highgui/highgui.hpp>
#include<opencv2/contrib/contrib.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>
#include <atlstr.h>
#include <fstream>
#include <iostream>
#include "Fld.h"
using namespace std;
using namespace cv;

extern "C" __declspec(dllexport) void WriteStringLine(ofstream &os, CString str);
extern "C" __declspec(dllexport) void ReadStringLine(ifstream &is, CString &str);
extern "C" __declspec(dllexport) void WriteIntText(ofstream &os, int n, CString name = "");
extern "C" __declspec(dllexport) void ReadIntText(ifstream &is, int &n, bool hasName = true);

extern "C" __declspec(dllexport) void WriteCvMatBin(ofstream &os, CvMat *mat, CString name = "");
extern "C" __declspec(dllexport) void ReadCvMatBin(ifstream &is, CvMat *mat, bool hasName = true);

extern "C" __declspec(dllexport) int CalcSubspace(CvMat *inputs, int *trainIds);


extern "C" __declspec(dllexport) void Project(CvMat *inputs, CvMat *results);

extern "C" __declspec(dllexport) int GetModelSize();

extern "C" __declspec(dllexport) int GetFtDim();


extern "C" __declspec(dllexport) double CalcVectorDist(CvMat *target, CvMat *query);


extern "C" __declspec(dllexport) bool WriteDataToFile(ofstream &os);


extern "C" __declspec(dllexport) bool ReadDataFromFile(ifstream &is);


extern "C" __declspec(dllexport) void ReleaseSubspace();
