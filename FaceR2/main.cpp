#include "mainwindow.h"
#include "logindlg.h"
#include "QtSql"
#include "QMessageBox"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	LoginDlg dlg;
    MainWindow w;

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("sign_in");
	db.setUserName("root");
	db.setPassword("123456");
	if (!db.open()){
		QMessageBox::critical(0, qApp->tr("Cannot open database!"),
			qApp->tr("Unable to establish a database connection\n"),
			QMessageBox::Cancel);
		return false;
	}

    if(dlg.exec()==QDialog::Accepted)
    {
		MainWindow w;
		w.tname = dlg.GetTname();
		w.userid = dlg.GetUid();
		w.SetTname();
		w.SetUserId();
		w.SetCourse();
        w.show();
        return a.exec();
    }

	db.close();
    return 0;
	//Camera c;
	//c.show();
	//return a.exec();
	//
}
