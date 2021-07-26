#ifndef LOGINDLG_H
#define LOGINDLG_H
#include "qsqltablemodel.h"
#include "qsqlrecord.h"
#include <QDialog>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
	QString GetName();
	QString GetPwd();
	QString GetUid();
	QString GetTname();
    ~LoginDlg();
private slots:
    void Login();

private:
    Ui::LoginDlg *ui;
	QString name;
	QString pwd;
	QString uid;
	QString tname;
};

#endif // LOGINDLG_H
