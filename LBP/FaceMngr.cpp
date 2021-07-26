#include "FaceMngr.h"
#include "FaceFeature.h"
#include "Subspace.h"
//vector<SModel> m_lstModel;
//CvMat	 *tmodel;
//int		m_featureSz, m_modelSz;

void CFaceMngr::SaveToModel(char *path, int classId, char *name)
{
	//char *path = "D:\\photo\\光照归一化2\\刘彤彤.jpg";
	IplImage *pic = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);
	CvMat *tfaceImg32 = cvCreateMat(112, 92, CV_32FC1);
	
	cvConvertScale(pic, tfaceImg32, 1.0 / 255);
	CvMat *ft = cvCreateMat(m_featureSz, 1, CV_8UC1);
	GetFeature(tfaceImg32, ft);
	SModel sm;
	sm.model = ft;
	sm.classId = classId;
	sm.picPath = path;
	sm.name = name;
	m_lstModel.push_back(sm);
	cvReleaseImage(&pic);
	//cvReleaseImage(&tfaceImg32);
}

void CFaceMngr::FormTrainMat(CvMat *inputs, int *trainIds)
{
	smd_iter	iter = m_lstModel.begin();
	CvMat	sub, *src;
	int i = 0;
	int m_trainclsNum = 0;

	for (; iter != m_lstModel.end(); iter++)
	{
		src = iter->model;
		cvGetCol(inputs, &sub, i);
		cvCopy(src, &sub);

		bool flag = false;
		for (int j = 0; j < i; j++)
		{
			if (trainIds[j] == iter->classId)
			{
				flag = true;
				break;
			}
		}
		if (!flag) m_trainclsNum++;
		trainIds[i++] = iter->classId;
	}
}

void CFaceMngr::train()
{
	int trainNum = m_lstModel.size();
	CvMat *inputs = cvCreateMat(m_featureSz, trainNum, CV_8UC1);
	int *trainIds = new int[trainNum];
	FormTrainMat(inputs, trainIds);
	m_modelSz = CalcSubspace(inputs, trainIds);
	delete []trainIds;
	cvReleaseMat(&inputs);
	tmodel = cvCreateMat(m_modelSz, 1, CV_32FC1);
}

void CFaceMngr::TrainResSave2Model()
{
	int		mdSz = GetModelSize();
	smd_iter	iter = m_lstModel.begin();
	for (; iter != m_lstModel.end(); iter++)
	{
		CvMat *model = cvCreateMat(mdSz, 1, CV_32FC1);
		Project(iter->model, model);
		cvReleaseMat(&(iter->model));
		iter->model = model;
	}
}

void CFaceMngr::Recognize(CvMat *model, SMatch *info)
{

	smd_iter	iter = m_lstModel.begin();
	SModel	*minpm = &(*iter);
	double	minDist = 1e9, curVal; //0~1
	for (; iter != m_lstModel.end(); iter++)
	{
		curVal = CalcVectorDist(iter->model, model);
		if (curVal < minDist)
		{
			minDist = curVal;
			minpm = &(*iter);
		}
	}

	info->classId = minpm->classId;
	info->dist = minDist;
	info->picPath = minpm->picPath;
	info->name = minpm->name;
	//cout << "classId:" << info->classId << "   " << "dist: " << info->dist << endl;
	//cout << info->picPath << endl;

}

//int main()
//{
//	CvSize faceSz = cvSize(92, 112);
//	m_featureSz = InitFeature(faceSz);
//	char *path = "D:\\photo\\光照归一化2\\3\\刘彤彤.jpg";
//	SaveToModel(path,3);
//	SaveToModel("D:\\photo\\光照归一化2\\2\\赖传滨.jpg", 2);
//	SaveToModel("D:\\photo\\光照归一化2\\1\\陈佩娴.jpg", 1);
//	SaveToModel("D:\\photo\\光照归一化2\\4\\韩越兴.jpg", 4);
//
//	//SaveToModel("D:\\photo\\光照归一化2\\6\\童麟.jpg", 6);
//	SaveToModel("D:\\photo\\光照归一化2\\5\\陶婧琳.jpg", 5);
//	SaveToModel("D:\\photo\\光照归一化2\\7\\徐世兴.jpg", 7);
//
//	train();
//	TrainResSave2Model();
//
//	//IplImage *ceshi = cvLoadImage("D:\\photo\\test1\\宿舍\\b.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//	//CvMat *tfaceImg32 = cvCreateMat(112, 92, CV_32FC1);
//	//cvConvertScale(ceshi, tfaceImg32, 1.0 / 255);
//	//CvMat *tfeature = cvCreateMat(m_featureSz, 1, CV_8UC1);
//	//GetFeature(tfaceImg32, tfeature);
//	//Project(tfeature, tmodel);
//
//	//SMatch *info;
//	//info = (struct SMatch*)malloc(sizeof(struct SMatch));
//
//	//Recognize(tmodel, info);
//	//cout << "classId:" << info->classId << "   " << "dist: " << info->dist << endl;
//	//cout << info->picPath << endl;
//
//
//	const char *cascadeFileName = "C:\\opencv249\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
//	CvHaarClassifierCascade *pHaarCascade = NULL;
//	CvCapture *cap = cvCreateCameraCapture(0);
//	if (!cap){
//		cerr << "error!" << endl;
//		exit(-1);
//	}
//	IplImage *tempImage = cvQueryFrame(cap);
//	CvSize size = cvSize(
//		(int)cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_WIDTH),
//		(int)cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT)
//		);
//	const char *srcWindowsName = "人脸识别";
//	IplImage *srcImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
//	cvNamedWindow(srcWindowsName, CV_WINDOW_AUTOSIZE);
//	while (1){      //tempImage = cvQueryFrame(cap) != NULL
//		tempImage = cvQueryFrame(cap);
//		cvCopy(tempImage, srcImage);
//		//if (srcImage->origin == IPL_ORIGIN_TL){
//		//	cvFlip(srcImage, srcImage);
//		//}
//		IplImage *grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 1);
//		cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
//		pHaarCascade = (CvHaarClassifierCascade*)cvLoad(cascadeFileName);
//		if (pHaarCascade != NULL){
//			CvScalar faceCircleColors[] = {
//				{ { 0, 0, 255 } }, { { 0, 128, 255 } }, { { 0, 255, 0 } }, { {255,0,255} }
//			};
//			CvMemStorage *cvMstorage = cvCreateMemStorage(0);
//			cvClearMemStorage(cvMstorage);
//			CvSeq *cvSeqFace = cvHaarDetectObjects(grayImage, pHaarCascade, cvMstorage);
//			for (int i = 0; i < cvSeqFace->total; i++){
//				CvRect *r = (CvRect*)cvGetSeqElem(cvSeqFace, i);
//				int x1 = r->x + r->width*0.15;
//				int y1 = r->y + r->height*0.2;
//				int x2 = r->x + r->width*0.85;
//				int y2 = r->y + r->height;
//				cvRectangle(srcImage, Point(x1, y1), Point(x2, y2), faceCircleColors[i % 4], 2);
//
//				IplImage *img1 = cvGetImage(cvGetSubRect(srcImage, cvCreateMatHeader(112, 92, CV_8UC1), 
//					cvRect(x1, y1, 92, 112)), cvCreateImageHeader(cvSize(92, 112), 8, 1));
//				IplImage* img = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
//				cvCvtColor(img1, img, CV_BGR2GRAY);
//				CvMat *tfaceImg32 = cvCreateMat(112, 92, CV_32FC1);
//				cvConvertScale(img, tfaceImg32, 1.0 / 255);
//				CvMat *tfeature = cvCreateMat(m_featureSz, 1, CV_8UC1);
//				GetFeature(tfaceImg32, tfeature);
//				Project(tfeature, tmodel);
//
//				SMatch *info;
//				info = (struct SMatch*)malloc(sizeof(struct SMatch));
//
//				Recognize(tmodel, info);
//				cout << "classId:" << info->classId << "   " << "dist: " << info->dist << endl;
//				cout << info->picPath << endl;
//
//
//			}
//			cvReleaseMemStorage(&cvMstorage);
//		}
//		cvShowImage(srcWindowsName, srcImage);
//		cvReleaseImage(&grayImage);
//		char c = cvWaitKey(22);
//		if (c == 27)break;
//	}
//	cvDestroyWindow(srcWindowsName);
//	cvReleaseImage(&srcImage);
//
//	
//	return 0;
//}

void CFaceMngr::detect()
{
	/*const char *cascadeFileName = "C:\\opencv249\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade *pHaarCascade = NULL;
	IplImage *grayImage = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCvtColor(img, grayImage, CV_BGR2GRAY);
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(cascadeFileName);
	if (pHaarCascade != NULL){
		CvScalar faceCircleColors[] = {
			{ { 0, 0, 255 } }, { { 0, 128, 255 } }, { { 0, 255, 0 } }, { { 255, 0, 255 } }
		};
		CvMemStorage *cvMstorage = cvCreateMemStorage(0);
		cvClearMemStorage(cvMstorage);
		CvSeq *cvSeqFace = cvHaarDetectObjects(grayImage, pHaarCascade, cvMstorage);
		for (int i = 0; i < cvSeqFace->total; i++){
			CvRect *r = (CvRect*)cvGetSeqElem(cvSeqFace, i);
			int x1 = r->x + r->width*0.15;
			int y1 = r->y + r->height*0.2;
			int x2 = r->x + r->width*0.85;
			int y2 = r->y + r->height;
			cvRectangle(img, Point(x1, y1), Point(x2, y2), faceCircleColors[i % 4], 2);
		}
	}*/

}

void CFaceMngr::openc()
{
	CvCapture *cap = cvCreateCameraCapture(0);
	if (!cap){
		cout << "error" << endl;
	}
}
