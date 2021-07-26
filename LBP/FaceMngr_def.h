#pragma once

#include<opencv2/highgui/highgui.hpp>
#include<opencv2/contrib/contrib.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
#include<cv.h>
#include<vector>
#include <atlstr.h>
#include <fstream>
#include <iostream>
#include "Fld.h"
using namespace std;
using namespace cv;
struct SModel
{
	int		classId;
	char	*picPath;
	char    *name;
	CvMat	*model;
};

struct SMatch
{
	int		classId;
	char	*picPath;
	char    *name;
	double	dist;
};

struct SFInfo
{
	int		classId;
	char    *picPath;
	SFInfo(int id, char *path) :classId(id), picPath(path){}
};

typedef vector<SModel>::iterator	smd_iter;
typedef vector<SFInfo>::iterator	sfi_iter;
typedef vector<SMatch>::iterator	smt_iter;