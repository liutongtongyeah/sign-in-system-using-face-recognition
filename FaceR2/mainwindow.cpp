#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->nametext->setText(tname);
	ui->numtext->setText(userid);
	cap = NULL;
	r = FALSE;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(ReadFrame()));
	connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closecamera()));
	connect(ui->openButton, SIGNAL(clicked()), this, SLOT(opencamera()));
	connect(ui->recognizeButton, SIGNAL(clicked()), this, SLOT(recognize()));
	connect(ui->photoButton, SIGNAL(clicked()), this, SLOT(takePhoto()));
	connect(ui->stuButton, SIGNAL(clicked()), this, SLOT(student()));
}

void MainWindow::SetTname()
{
	ui->nametext->setText(tname);
}

void MainWindow::SetUserId()
{
	ui->numtext->setText(userid);
}

void MainWindow::SetCourse()
{
	QSqlTableModel model;
	QStringList course_list;
	QSqlQuery query;
	query.exec(QObject::tr("select cname from open, course where open.cno=course.cno and open.tno='%1'").arg(userid));
	while (query.next()){
		QString course_name = query.value(0).toString();
		course_list.append(course_name);
	}

	ui->comboBox->clear();
	ui->comboBox->addItems(course_list);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::opencamera()
{
	cap = cvCreateCameraCapture(0);
	if (cap==NULL){
		QMessageBox::warning(this, tr("Waring"),
			tr("camera error!"),
			QMessageBox::Yes);
	}
	else{
		timer->start(50);
		//ui->textEdit->clear();
	}
	if (face.m_lstModel.empty())
	{
		CvSize faceSz = cvSize(92, 112);
		face.m_featureSz = InitFeature(faceSz);
		char *path = "E:\\lbp_gabor\\photo\\光照归一化2\\3\\刘彤彤.jpg";
		face.SaveToModel(path, 3,"刘彤彤");
		face.SaveToModel("E:\\lbp_gabor\\photo\\光照归一化2\\2\\赖传滨.jpg", 2,"赖传滨");
		face.SaveToModel("E:\\lbp_gabor\\photo\\光照归一化2\\1\\陈佩娴.jpg", 1,"陈佩娴");
		face.SaveToModel("E:\\lbp_gabor\\photo\\光照归一化2\\4\\韩越兴.jpg", 4,"韩越兴");
	
		face.SaveToModel("E:\\lbp_gabor\\photo\\光照归一化2\\6\\童麟.jpg", 6,"童麟");
		//face.SaveToModel("D:\\photo\\光照归一化2\\7\\徐世兴.jpg", 7,"徐世兴");
		face.train();
		face.TrainResSave2Model();
	}


}

void MainWindow::ReadFrame()
{
	img = cvQueryFrame(cap);

	/**************detect and recognize**************/
	if (r){
		char *cascadeFileName = "C:\\opencv249\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
		CvHaarClassifierCascade *pHaarCascade = NULL;
		pHaarCascade = (CvHaarClassifierCascade*)cvLoad(cascadeFileName);
		//	IplImage *tempImage = cvQueryFrame(cap);
		CvSize size = cvSize(
			(int)cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_WIDTH),
			(int)cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT)
			);
		IplImage *srcImage = cvCreateImage(size, IPL_DEPTH_8U, 3);

		cvCopy(img, srcImage);

		IplImage *grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 1);
		cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
		pHaarCascade = (CvHaarClassifierCascade*)cvLoad(cascadeFileName);
		if (pHaarCascade != NULL){
			CvMemStorage *cvMstorage = cvCreateMemStorage(0);
			cvClearMemStorage(cvMstorage);
			CvSeq *cvSeqFace = cvHaarDetectObjects(grayImage, pHaarCascade, cvMstorage);
			for (int i = 0; i < cvSeqFace->total; i++){
				CvRect *r = (CvRect*)cvGetSeqElem(cvSeqFace, i);
				int x1 = r->x + r->width*0.15;
				int y1 = r->y + r->height*0.2;
				int x2 = r->x + r->width*0.85;
				int y2 = r->y + r->height;
				cvRectangle(img, Point(x1, y1), Point(x2, y2), Scalar(255, 0, 0), 2);
				/*****************改******************/
				//cvSetImageROI(srcImage, cvRect(x1, y1, r->width*0.85, r->height));

				/************************************/

				//IplImage *img1 = cvGetImage(cvGetSubRect(img, cvCreateMatHeader(112, 92, CV_8UC1),
				//	cvRect(x1, y1, 92, 112)), cvCreate
				//ImageHeader(cvSize(92, 112), 8, 1));
				//IplImage* img2 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, 1);
				//cvCvtColor(img1, img2, CV_BGR2GRAY);

				/******对上面3条语句做了修改*****/
				IplImage *img1 = cvGetImage(cvGetSubRect(grayImage, cvCreateMatHeader(x2 - x1, y2 - y1, CV_8UC1),
					cvRect(x1, y1, x2 - x1, y2 - y1)), cvCreateImageHeader(cvSize(x2 - x1, y2 - y1), 8, 1));
				IplImage *img2=cvCreateImage(cvSize(92,112),img1->depth,img1->nChannels);
				cvResize(img1,img2);
				/******************************************/


				CvMat *tfaceImg32 = cvCreateMat(112, 92, CV_32FC1);
				cvConvertScale(img2, tfaceImg32, 1.0 / 255);
				CvMat *tfeature = cvCreateMat(face.m_featureSz, 1, CV_8UC1);
				GetFeature(tfaceImg32, tfeature);
				Project(tfeature, face.tmodel);

				SMatch *info;
				info = (struct SMatch*)malloc(sizeof(struct SMatch));

				face.Recognize(face.tmodel, info);

				if (info->dist <= 0.4)
				{
					//ui->textEdit->insertPlainText(QString::fromLocal8Bit(info->picPath));
					ui->textEdit->insertPlainText(QString::fromLocal8Bit(info->name));
					ui->textEdit->insertPlainText("\n");


				}
			}
			cvReleaseMemStorage(&cvMstorage);
			//cvShowImage(srcWindowsName, srcImage);
			cvReleaseImage(&grayImage);
		}
		//cvDestroyWindow(srcWindowsName);
		cvReleaseImage(&srcImage);
	}

	/************************************************/

	QImage qimg = QImage((const uchar*)img->imageData, img->width, img->height, QImage::Format_RGB888).rgbSwapped();
	ui->cameralabel->setPixmap(QPixmap::fromImage(qimg));
}

void MainWindow::closecamera()
{
	timer->stop();
	//ui->camera->clear();
	r = FALSE;
	//ui->textEdit->clear();
	cvReleaseCapture(&cap);
}


void MainWindow::takePhoto(){
	if (cap == NULL)
	{
		QMessageBox::warning(this, tr("Waring"),
			tr("The camera is not open!"),
			QMessageBox::Yes);
	}
	else if (r == true)
	{
		QMessageBox::warning(this, tr("Waring"),
			tr("Face recognition is in progress!"),
			QMessageBox::Yes);
	}

	else{
		img = cvQueryFrame(cap);
		cvSaveImage("D:\\photo\\temp\\temp.jpg", img);

		QMessageBox::warning(this, tr("Waring"),
			tr("Done!"),
			QMessageBox::Yes);

	}
}
void MainWindow::recognize()
{
	if (face.m_lstModel.empty())
	{
		QMessageBox::warning(this, tr("Waring"),
			tr("The training sample is empty!"),
			QMessageBox::Yes);
	}
	else if (cap == NULL)
	{
		QMessageBox::warning(this, tr("Waring"),
			tr("The camera is not open!"),
			QMessageBox::Yes);
	}
	else{
		r = TRUE;

	}

}

void MainWindow::student()
{
	QSqlTableModel *model = new QSqlTableModel;
	model->setTable("student");
	model->setSort(1, Qt::AscendingOrder);
	model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("学号"));
	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("姓名"));
	model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("性别"));
	model->select();
	model->removeColumn(3);
	QTableView *view = new QTableView;
	view->setModel(model);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->setSelectionBehavior(QAbstractItemView::SelectRows);
	view->resizeColumnsToContents();
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QHeaderView *header = view->horizontalHeader();
	header->setStretchLastSection(true);
	view->show();
}