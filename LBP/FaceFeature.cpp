/*
Gabor + Local Binary Patterns
程序中圆形LBP算子和旋转不变LBP两个函数均可使用
*/

#include "FaceFeature.h"
#include "Gabor.h"

#define PROD(sz) ((sz).height*(sz).width)
#define SQR2_2	0.7071068	//sqrt(2)/2
typedef unsigned char	UINT8, *PUINT8;


static Size	g_faceSz, lgbpFaceSz;
static Size	blockNum, winNum;
static int	lgbpBinNum;
static Size	gKerNum;

static Mat	lgbpFace;
static Mat	tmpFt;
static Mat	tLgbpFace1, tLgbpFace2;

void GenLgbpFace(Mat & gface, Mat & lgbpFace);

void GetLgbpHist(Mat & lgbpFace, Mat & ft1);


int InitFeature(CvSize imgSize)
{
	gKerNum = InitGabor(imgSize);

	g_faceSz = imgSize;
	lgbpFaceSz = Size(imgSize.width - 2, imgSize.height - 2); // lgbpFace比原图像小 2像素
	lgbpFace.create(lgbpFaceSz.height, lgbpFaceSz.width, CV_8UC1);
	tLgbpFace1.create(lgbpFaceSz.height, lgbpFaceSz.width, CV_8UC1);
	tLgbpFace2.create(lgbpFaceSz.height, lgbpFaceSz.width, CV_32FC1);


	blockNum = Size(4, 10);
	winNum = Size(4, 1);
	lgbpBinNum = 8;

	tmpFt.create(PROD(blockNum), PROD(gKerNum) * PROD(winNum) * lgbpBinNum, CV_8UC1);

	return tmpFt.size().area();
}

void GetFeature(CvArr *faceImg32, CvMat *ft32)
{
	CvMat ***gface = GaborConv(faceImg32);
	int ftNum1 = PROD(winNum)*lgbpBinNum,
		blkCnt = PROD(blockNum);
	int idxc = 0;
	tmpFt.setTo(Scalar(0));

	int quantizeLevels = 8;
	int quantizeIntv = 256 / quantizeLevels;
	for (int gr = 0; gr < gKerNum.height; gr++)
	{
		for (int gc = 0; gc < gKerNum.width; gc++)
		{
			GenLgbpFace(Mat(gface[gr][gc]), lgbpFace);
			//cout << lgbpFace.rows << " " << lgbpFace.cols;
			//imwrite("D:\\photo\\123.jpg", lgbpFace);
			//namedWindow("lgbp face");
			//imshow("lgbp face", lgbpFace);
			//waitKey();

			//???????????
			lgbpFace = (lgbpFace - quantizeIntv / 2) / quantizeIntv; // have to minus quantizeIntv/2 first, because OpenCV rounds the division result for uchar
			//

			GetLgbpHist(lgbpFace, tmpFt.colRange(idxc*ftNum1, (idxc + 1)*ftNum1));
			idxc++;
		}
	}

	Mat ft = tmpFt.reshape(0, PROD(cvGetSize(ft32)));
	ft.copyTo(Mat(ft32));
}

//旋转不变LBP
//void GenLgbpFace(Mat & gface, Mat & lgbpFace)
//{
//	int H = g_faceSz.height, W = g_faceSz.width;
//	Mat C = gface(Range(1, H - 1), Range(1, W - 1));
//	Mat R = gface(Range(1, H - 1), Range(2, W)),
//		U = gface(Range(0, H - 2), Range(1, W - 1)),
//		L = gface(Range(1, H - 1), Range(0, W - 2)),
//		D = gface(Range(2, H), Range(1, W - 1)),
//		UR = gface(Range(0, H - 2), Range(2, W)),
//		UL = gface(Range(0, H - 2), Range(0, W - 2)),
//		DL = gface(Range(2, H), Range(0, W - 2)),
//		DR = gface(Range(2, H), Range(2, W));
//
//	bitwise_and(R - C>0, Scalar(0x01), lgbpFace);
//
//	tLgbpFace2 = SQR2_2*SQR2_2*UR + SQR2_2*(1 - SQR2_2)*(U + R) + (1 - SQR2_2)*(1 - SQR2_2)*C;
//	bitwise_and(tLgbpFace2 - C>0, Scalar(0x02), tLgbpFace1);
//	lgbpFace += tLgbpFace1;
//
//	bitwise_and(U - C>0, Scalar(0x04), tLgbpFace1);
//	lgbpFace += tLgbpFace1;
//
//	tLgbpFace2 = SQR2_2*SQR2_2*UL + SQR2_2*(1 - SQR2_2)*(U + L) + (1 - SQR2_2)*(1 - SQR2_2)*C;
//	bitwise_and(tLgbpFace2 - C>0, Scalar(0x08), tLgbpFace1);
//	lgbpFace += tLgbpFace1;
//
//	bitwise_and(L - C>0, Scalar(0x10), tLgbpFace1);
//	lgbpFace += tLgbpFace1;
//
//	tLgbpFace2 = SQR2_2*SQR2_2*DL + SQR2_2*(1 - SQR2_2)*(D + L) + (1 - SQR2_2)*(1 - SQR2_2)*C;
//	bitwise_and(tLgbpFace2 - C>0, Scalar(0x20), tLgbpFace1);
//	lgbpFace += tLgbpFace1;
//
//	bitwise_and(D - C>0, Scalar(0x40), tLgbpFace1);
//	lgbpFace += tLgbpFace1;
//
//
//	tLgbpFace2 = SQR2_2*SQR2_2*DR + SQR2_2*(1 - SQR2_2)*(D + R) + (1 - SQR2_2)*(1 - SQR2_2)*C;
//	bitwise_and(tLgbpFace2 - C>0, Scalar(0x80), tLgbpFace1);
//	lgbpFace += tLgbpFace1;
//}

//圆形LBP算子
void GenLgbpFace(Mat & src, Mat & dst)
{
	int radius = 1;
	int neighbors = 8;
	dst.setTo(0);
	for (int k = 0; k<neighbors; k++)
	{
		float rx = static_cast<float>(radius * cos(2.0 * CV_PI * k / neighbors));
		float ry = -static_cast<float>(radius * sin(2.0 * CV_PI * k / neighbors));
		int x1 = static_cast<int>(floor(rx));
		int x2 = static_cast<int>(ceil(rx));
		int y1 = static_cast<int>(floor(ry));
		int y2 = static_cast<int>(ceil(ry));
		float tx = rx - x1;
		float ty = ry - y1;
		float w1 = (1 - tx) * (1 - ty);
		float w2 = tx  * (1 - ty);
		float w3 = (1 - tx) *    ty;
		float w4 = tx  *    ty;
		for (int i = radius; i<src.rows - radius; i++)
		{
			for (int j = radius; j<src.cols - radius; j++)
			{
				float center = src.at<float>(i, j);
				float neighbor = src.at<float>(i + x1, j + y1) * w1 + src.at<float>(i + x1, j + y2) *w2 \
					+ src.at<float>(i + x2, j + y1) * w3 + src.at<float>(i + x2, j + y2) *w4;
				dst.at<uchar>(i - radius, j - radius) |= (neighbor>center) << (neighbors - k - 1);
			}
		}
	}
}

void GetLgbpHist(Mat & lgbpFace, Mat & ft1)
{
	Size blkSz(lgbpFaceSz.width / blockNum.width,
		lgbpFaceSz.height / blockNum.height);
	Size winSz(blkSz.width / winNum.width,
		blkSz.height / winNum.height);

	UINT8 val;
	UINT8 *pSrc = lgbpFace.data;
	UINT8 *pDst = (UINT8*)(ft1.data);
	int bidx = 0, widx;

	for (int br = 0; br < blockNum.height; br++)
	{
		for (int bc = 0; bc < blockNum.width; bc++)
		{
			widx = 0;
			for (int wr = 0; wr < winNum.height; wr++)
			{
				for (int wc = 0; wc < winNum.width; wc++)
				{
					for (int r = 0; r < winSz.height; r++)
					{
						for (int c = 0; c < winSz.width; c++)
						{
							int a = lgbpFace.step[0];
							val = *(pSrc +
								(br*blkSz.height + wr*winSz.height + r) * lgbpFace.step[0] +
								(bc*blkSz.width + wc*winSz.width + c));
							(*(pDst + bidx * ft1.step[0] / sizeof(UINT8) + lgbpBinNum*widx + val))++;
						}
					}
					widx++;
				}
			}
			bidx++;
		}
	}
}

void ReleaseFeature()
{
	ReleaseGabor();
}