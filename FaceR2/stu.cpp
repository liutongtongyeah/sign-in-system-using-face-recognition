#include "stu.h"
#include "ui_stu.h"

stu::stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stu)
{
    ui->setupUi(this);
}

stu::~stu()
{
    delete ui;
}
