/********************************************************************************
** Form generated from reading UI file 'logindlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDLG_H
#define UI_LOGINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDlg
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *username;
    QLineEdit *userline;
    QLabel *password;
    QLineEdit *pwdline;
    QPushButton *LoginButton;
    QPushButton *ExitButton;

    void setupUi(QDialog *LoginDlg)
    {
        if (LoginDlg->objectName().isEmpty())
            LoginDlg->setObjectName(QStringLiteral("LoginDlg"));
        LoginDlg->resize(383, 173);
        layoutWidget = new QWidget(LoginDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 50, 216, 77));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        username = new QLabel(layoutWidget);
        username->setObjectName(QStringLiteral("username"));

        gridLayout->addWidget(username, 0, 0, 1, 1);

        userline = new QLineEdit(layoutWidget);
        userline->setObjectName(QStringLiteral("userline"));

        gridLayout->addWidget(userline, 0, 1, 1, 1);

        password = new QLabel(layoutWidget);
        password->setObjectName(QStringLiteral("password"));

        gridLayout->addWidget(password, 1, 0, 1, 1);

        pwdline = new QLineEdit(layoutWidget);
        pwdline->setObjectName(QStringLiteral("pwdline"));
        pwdline->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(pwdline, 1, 1, 1, 1);

        LoginButton = new QPushButton(layoutWidget);
        LoginButton->setObjectName(QStringLiteral("LoginButton"));

        gridLayout->addWidget(LoginButton, 2, 0, 1, 1);

        ExitButton = new QPushButton(layoutWidget);
        ExitButton->setObjectName(QStringLiteral("ExitButton"));

        gridLayout->addWidget(ExitButton, 2, 1, 1, 1);


        retranslateUi(LoginDlg);
        QObject::connect(ExitButton, SIGNAL(clicked()), LoginDlg, SLOT(close()));
        QObject::connect(LoginButton, SIGNAL(clicked()), LoginDlg, SLOT(Login()));

        QMetaObject::connectSlotsByName(LoginDlg);
    } // setupUi

    void retranslateUi(QDialog *LoginDlg)
    {
        LoginDlg->setWindowTitle(QApplication::translate("LoginDlg", "Dialog", Q_NULLPTR));
        username->setText(QApplication::translate("LoginDlg", "UserName", Q_NULLPTR));
        password->setText(QApplication::translate("LoginDlg", "password", Q_NULLPTR));
        LoginButton->setText(QApplication::translate("LoginDlg", "Login", Q_NULLPTR));
        ExitButton->setText(QApplication::translate("LoginDlg", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDlg: public Ui_LoginDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDLG_H
