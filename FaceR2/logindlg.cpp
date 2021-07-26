#include "logindlg.h"
#include "ui_logindlg.h"
#include "QMessageBox"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::Login()
{
	name = ui->userline->text();
	pwd = ui->pwdline->text();
	QSqlTableModel model;
	model.setTable("teacher");
	model.setFilter(tr("username = '%1' and pwd = '%2'").arg(name).arg(pwd));
	model.select();
	
	if (model.rowCount() == 1)
	{
		uid = model.record(0).value("tno").toString();
		tname = model.record(0).value("tname").toString();
		accept();
	}
    //if(ui->userline->text()==tr("liu")&&ui->pwdline->text()==tr("123"))
    //{
    //    accept();
    //}
	else
	{
		QMessageBox::warning(this, tr("Waring"),
			tr("username or password error!"),
			QMessageBox::Yes);

		ui->userline->clear();
		ui->pwdline->clear();
		ui->userline->setFocus();
	}
}
QString LoginDlg::GetName()
{
	return name;
}

QString LoginDlg::GetPwd()
{
	return pwd;
}

QString LoginDlg::GetUid()
{
	return uid;
}
QString LoginDlg::GetTname()
{
	return tname;
}