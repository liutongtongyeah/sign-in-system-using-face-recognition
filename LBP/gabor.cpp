#include "Gabor.h"

#define PI CV_PI

double	kmax, f, sigma, th;
int		scaleNum, angleNum, kernelRadius;
int		*scales; 

static CvSize	g_faceSz;
static int		kernelWidth, fsz;
static CvMat	***G;
static CvMat	*tPicR, *tPicI, *tPicF0, *tPicF;

CvMat ***gface;

static void InitGaborKernel();


void Magnitude(CvArr *input, CvMat *mag)
{
	CvSize sz = cvGetSize(input);
	CvMat *re = cvCreateMat(sz.height, sz.width, CV_32FC1),
		*im = cvCreateMat(sz.height, sz.width, CV_32FC1);

	cvSplit(input, re, im, NULL, NULL);

	cvPow(re, re, 2.0);
	cvPow(im, im, 2.0);
	cvAdd(re, im, mag, NULL);
	cvPow(mag, mag, 0.5);

	cvReleaseMat(&re);
	cvReleaseMat(&im);
}


CvSize InitGabor(CvSize imgSize)
{
	kmax = PI / 2;
	f = sqrt(double(2));
	sigma = 2 * PI;
	scaleNum = 5;
	angleNum = 8;
	th = 5e-3;

	kernelRadius = (int)ceil(sqrt(-log(th*sigma*sigma / kmax / kmax) * 2 * sigma*sigma / kmax / kmax));
	scales = new int[scaleNum];
	for (int i = 0; i < scaleNum; i++)
		scales[i] = i;

	g_faceSz = imgSize;
	InitGaborKernel();
	tPicR = cvCreateMat(fsz, fsz, CV_32FC1);
	tPicI = cvCreateMat(fsz, fsz, CV_32FC1);
	tPicF0 = cvCreateMat(fsz, fsz, CV_32FC2);
	tPicF = cvCreateMat(fsz, fsz, CV_32FC2);

	gface = new CvMat **[scaleNum];
	for (int i = 0; i < scaleNum; i++)
	{
		gface[i] = new CvMat *[angleNum];
		for (int j = 0; j < angleNum; j++)
			gface[i][j] = cvCreateMat(g_faceSz.height, g_faceSz.width, CV_32FC1);
	}

	return cvSize(angleNum, scaleNum);
}

static void InitGaborKernel()
{
	fsz = cvGetOptimalDFTSize(max(g_faceSz.height, g_faceSz.width) + kernelRadius * 2);
	kernelWidth = kernelRadius * 2 + 1;

	G = new CvMat **[scaleNum];
	CvMat *re = cvCreateMat(kernelWidth, kernelWidth, CV_32FC1),
		*im = cvCreateMat(kernelWidth, kernelWidth, CV_32FC1),
		*g = cvCreateMat(kernelWidth, kernelWidth, CV_32FC2);

	for (int i = 0; i < scaleNum; i++)
	{
		G[i] = new CvMat *[angleNum];
		double k = kmax / pow(f, scales[i]),
			tmpV = k*k / sigma / sigma;

		for (int j = 0; j < angleNum; j++)
		{
			double phi = PI / angleNum*j;
			double tmpV0, tmpV1;

			for (int y = -kernelRadius; y <= kernelRadius; y++)
			{
				for (int x = -kernelRadius; x <= kernelRadius; x++)
				{
					tmpV0 = tmpV * exp(-tmpV * (x*x + y*y) / 2.0);
					tmpV1 = k*cos(phi)*x + k*sin(phi)*y;
					cvmSet(re, y + kernelRadius, x + kernelRadius, tmpV0 * cos(tmpV1));
					cvmSet(im, y + kernelRadius, x + kernelRadius, tmpV0 * sin(tmpV1));

				}
			}

			cvMerge(re, im, NULL, NULL, g);
			G[i][j] = cvCreateMat(fsz, fsz, CV_32FC2);
			cvCopyMakeBorder(g, G[i][j], cvPoint(0, 0), IPL_BORDER_CONSTANT);
			cvDFT(G[i][j], G[i][j], CV_DXT_FORWARD, kernelWidth);
			cvSet2D(G[i][j], 0, 0, cvScalar(0));
			//ShowMagnitude(G[i][j],true);
		}
	}
	cvReleaseMat(&re);
	cvReleaseMat(&im);
	cvReleaseMat(&g);
}

CvMat*** GaborConv(CvArr *faceImg32)
{
	//ShowGaborFace(faceImg32);
	CvMat sub;
	cvCopyMakeBorder(faceImg32, tPicR, cvPoint(kernelRadius, kernelRadius), IPL_BORDER_REPLICATE);
	cvZero(tPicI);
	cvMerge(tPicR, tPicI, NULL, NULL, tPicF0);
	cvDFT(tPicF0, tPicF0, CV_DXT_FORWARD, g_faceSz.height + kernelRadius * 2);

	for (int i = 0; i < scaleNum; i++)
	{
		for (int j = 0; j < angleNum; j++)
		{
			cvMulSpectrums(tPicF0, G[i][j], tPicF, NULL);
			cvDFT(tPicF, tPicF, CV_DXT_INVERSE_SCALE, g_faceSz.height + kernelRadius * 2); // filter result
			Magnitude(tPicF, tPicR);
			cvGetSubRect(tPicR, &sub, cvRect(kernelRadius * 2, kernelRadius * 2, g_faceSz.width, g_faceSz.height));
			cvCopy(&sub, gface[i][j]);
		}
	}

	return gface;
}


void ReleaseGabor()
{
	delete[scaleNum]scales;
	for (int i = 0; i < scaleNum; i++)
	{
		for (int j = 0; j < angleNum; j++)
		{
			cvReleaseMat(&G[i][j]);
			cvReleaseMat(&gface[i][j]);
		}
		delete[angleNum]G[i];
		delete[angleNum]gface[i];
	}
	delete[scaleNum]G;
	delete[scaleNum]gface;

	cvReleaseMat(&tPicR);
	cvReleaseMat(&tPicI);
	cvReleaseMat(&tPicF);
	cvReleaseMat(&tPicF0);
}
