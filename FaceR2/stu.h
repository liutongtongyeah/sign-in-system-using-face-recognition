#ifndef STU_H
#define STU_H

#include <QDialog>

namespace Ui {
class stu;
}

class stu : public QDialog
{
    Q_OBJECT

public:
    explicit stu(QWidget *parent = 0);
    ~stu();

private:
    Ui::stu *ui;
};

#endif // STU_H
