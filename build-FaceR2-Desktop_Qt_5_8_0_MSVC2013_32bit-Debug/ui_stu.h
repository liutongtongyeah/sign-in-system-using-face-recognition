/********************************************************************************
** Form generated from reading UI file 'stu.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STU_H
#define UI_STU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_stu
{
public:

    void setupUi(QDialog *stu)
    {
        if (stu->objectName().isEmpty())
            stu->setObjectName(QStringLiteral("stu"));
        stu->resize(430, 349);

        retranslateUi(stu);

        QMetaObject::connectSlotsByName(stu);
    } // setupUi

    void retranslateUi(QDialog *stu)
    {
        stu->setWindowTitle(QApplication::translate("stu", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class stu: public Ui_stu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STU_H
