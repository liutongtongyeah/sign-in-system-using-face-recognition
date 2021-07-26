#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qsqltablemodel.h"
#include "qsqlquery.h"
#include "qsqlrecord.h"
#include "qcompleter.h"
#include "qdebug.h"
#include "qtableview.h"

#include "qtimer.h"
#include "qimage.h"
#include "../LBP/FaceMngr.h"
#include "../LBP/Subspace.h"
#include "../LBP/FaceFeature.h"
//#include "../LBP/LightPrep.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	QString tname;
	QString userid;
	QString userpwd;
	void SetTname();
	void SetUserId();
	void SetCourse();

private slots:
	void opencamera();
	void closecamera();
	void ReadFrame();
	void takePhoto();
	void recognize();
    void student();

private:
    Ui::MainWindow *ui;
	CvCapture *cap;
	QTimer *timer;
	IplImage *img;
	CFaceMngr face;
	bool r;

};

#endif
