//
//#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/contrib/contrib.hpp>
////#include<opencv2/imgproc/imgproc.hpp>
////#include<opencv2/objdetect/objdetect.hpp>
//
//#include<iostream>
////#include<io.h>
//#include<fstream>
//#include<sstream>
//
//#include<cstring>
//#include<set>
//
//using namespace std;
//using namespace cv;
//
//int _grid_x = 8;
//int _grid_y = 8;
//int _radius = 1;
//int _neighbors = 8;
//double _threshold = DBL_MAX;
//vector<Mat> _histograms;
//Mat _labels;
//
//struct SFace
//{
//	int classId;
//	String picPath;
//	CvMat *face;
//};
//struct SMatch
//{
//	int classId;
//	String picPath;
//	double dist;
//};
//struct SFInfo
//{
//	int classId;
//	String picPath;
//
//};
//
//static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
//	std::ifstream file(filename.c_str(), ifstream::in);
//	if (!file) {
//		string error_message = "No valid input file was given, please check the given filename.";
//		CV_Error(CV_StsBadArg, error_message);
//	}
//	string line, path, classlabel;
//	while (getline(file, line)) {
//		stringstream liness(line);
//		getline(liness, path, separator);
//		getline(liness, classlabel);
//		if (!path.empty() && !classlabel.empty()) {
//			images.push_back(imread(path, 0));
//			labels.push_back(atoi(classlabel.c_str()));
//		}
//	}
//}
//
//static Mat spatial_histogram(InputArray _src, int numPatterns,
//	int grid_x, int grid_y, bool /*normed*/)
//{
//	Mat src = _src.getMat();
//	// calculate LBP patch size
//	int width = src.cols / grid_x;
//	int height = src.rows / grid_y;
//	// allocate memory for the spatial histogram
//	Mat result = Mat::zeros(grid_x * grid_y, numPatterns, CV_32FC1);
//	// return matrix with zeros if no data was given
//	if (src.empty())
//		return result.reshape(1, 1);
//	// initial result_row
//	int resultRowIdx = 0;
//	// iterate through grid
//	for (int i = 0; i < grid_y; i++) {
//		for (int j = 0; j < grid_x; j++) {
//			Mat src_cell = Mat(src, Range(i*height, (i + 1)*height), Range(j*width, (j + 1)*width));
//			Mat cell_hist = histc(src_cell, 0, (numPatterns - 1), true);
//			//string path = format("D:\\photo\\histogram\\%d.jpg", i*grid_x + j);
//			//imwrite(path, cell_hist);
//
//
//			// copy to the result matrix
//			Mat result_row = result.row(resultRowIdx);
//			cell_hist.reshape(1, 1).convertTo(result_row, CV_32FC1);
//			// increase row count in result matrix
//			resultRowIdx++;
//
//		}
//	}
//	// return result as reshaped feature vector
//	return result.reshape(1, 1);
//}
//
//void train(InputArrayOfArrays _in_src1, InputArray _in_src2, InputArray _in_labels)
//{
//	vector<Mat> src;
//	_in_src1.getMatVector(src);
//	Mat labels = _in_labels.getMat();
//	bool preserveData = false;
//	if (!preserveData){
//		_labels.release();
//		_histograms.clear();
//	}
//	for (size_t labelIdx = 0; labelIdx < labels.total(); labelIdx++){
//		_labels.push_back(labels.at<int>((int)labelIdx));
//	}
//	for (size_t sampleIdx = 0; sampleIdx < src.size(); sampleIdx++){
//		Mat image = src[sampleIdx];
//		Mat p = spatial_histogram(
//			image,
//			static_cast<int>(std::pow(2.0, static_cast<double>(_neighbors))),
//			_grid_x,
//			_grid_y,
//			true);
//		_histograms.push_back(p);
//	}
//
//}
/*
int main()
{
	string fn_csv = "D:\\photo\\csv\\gabor.csv";
	string lbp_csv = "D:\\photo\\csv\\lbp_gabor.csv";
	string test_csv = "D:\\photo\\csv\\lbp_gabor.csv";
	vector<Mat> images1;
	vector<int> labels1;
	vector<Mat> images2;
	vector<int> labels2;
	vector<Mat> testImages;
	vector<int> testLables;

	try {
		read_csv(fn_csv, images1, labels1);
	}
	catch (cv::Exception& e) {
		cerr << "error opening file \"" << fn_csv << "\".reason: " << e.msg << endl;
		exit(1);
	}
	try {
		read_csv(fn_csv, images2, labels2);
	}
	catch (cv::Exception& e) {
		cerr << "error opening file \"" << fn_csv << "\".reason: " << e.msg << endl;
		exit(1);
	}
	return 0;
}
*/
//#include "FaceMngr.h"
//#include "FaceFeature.h"
//#include "Subspace.h"
//
//int main()
//{
//	CFaceMngr w;
//	CvSize faceSz = cvSize(92, 112);
//	w.m_featureSz = InitFeature(faceSz);
//	char *path = "D:\\photo\\光照归一化2\\3\\刘彤彤.jpg";
//	w.SaveToModel(path,3);
//	w.SaveToModel("D:\\photo\\光照归一化2\\2\\赖传滨.jpg", 2);
//	w.SaveToModel("D:\\photo\\光照归一化2\\1\\陈佩娴.jpg", 1);
//	w.SaveToModel("D:\\photo\\光照归一化2\\4\\韩越兴.jpg", 4);
//
//	//SaveToModel("D:\\photo\\光照归一化2\\6\\童麟.jpg", 6);
//	w.SaveToModel("D:\\photo\\光照归一化2\\5\\陶婧琳.jpg", 5);
//	w.SaveToModel("D:\\photo\\光照归一化2\\7\\徐世兴.jpg", 7);
//
//	w.train();
//	w.TrainResSave2Model();
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
//				CvMat *tfeature = cvCreateMat(w.m_featureSz, 1, CV_8UC1);
//				GetFeature(tfaceImg32, tfeature);
//				Project(tfeature, w.tmodel);
//
//				SMatch *info;
//				info = (struct SMatch*)malloc(sizeof(struct SMatch));
//
//				w.Recognize(w.tmodel, info);
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