/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_2;
    QPushButton *courseButton;
    QPushButton *stuButton;
    QGroupBox *groupBox_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *numtext;
    QLabel *nametext;
    QLabel *label_3;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QPushButton *closeButton;
    QPushButton *openButton;
    QPushButton *photoButton;
    QPushButton *recognizeButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTextEdit *textEdit;
    QGroupBox *groupBox_4;
    QLabel *cameralabel;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(720, 587);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 390, 151, 111));
        courseButton = new QPushButton(groupBox_2);
        courseButton->setObjectName(QStringLiteral("courseButton"));
        courseButton->setGeometry(QRect(20, 30, 111, 23));
        stuButton = new QPushButton(groupBox_2);
        stuButton->setObjectName(QStringLiteral("stuButton"));
        stuButton->setGeometry(QRect(20, 70, 111, 23));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 40, 151, 161));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 31, 16));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 31, 16));
        numtext = new QLabel(groupBox_3);
        numtext->setObjectName(QStringLiteral("numtext"));
        numtext->setGeometry(QRect(70, 30, 54, 12));
        nametext = new QLabel(groupBox_3);
        nametext->setObjectName(QStringLiteral("nametext"));
        nametext->setGeometry(QRect(70, 50, 54, 12));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 54, 12));
        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(20, 110, 111, 22));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 220, 151, 151));
        closeButton = new QPushButton(groupBox);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(20, 110, 111, 23));
        closeButton->setStyleSheet(QStringLiteral(""));
        openButton = new QPushButton(groupBox);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(20, 20, 111, 23));
        openButton->setStyleSheet(QStringLiteral(""));
        photoButton = new QPushButton(groupBox);
        photoButton->setObjectName(QStringLiteral("photoButton"));
        photoButton->setGeometry(QRect(20, 50, 111, 23));
        photoButton->setStyleSheet(QStringLiteral(""));
        recognizeButton = new QPushButton(groupBox);
        recognizeButton->setObjectName(QStringLiteral("recognizeButton"));
        recognizeButton->setGeometry(QRect(20, 80, 111, 23));
        recognizeButton->setStyleSheet(QStringLiteral(""));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(210, 400, 481, 101));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 479, 99));
        textEdit = new QTextEdit(scrollAreaWidgetContents);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 481, 101));
        scrollArea->setWidget(scrollAreaWidgetContents);
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(210, 40, 481, 331));
        cameralabel = new QLabel(groupBox_4);
        cameralabel->setObjectName(QStringLiteral("cameralabel"));
        cameralabel->setGeometry(QRect(0, 10, 481, 321));
        cameralabel->setTextFormat(Qt::AutoText);
        cameralabel->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\344\277\241\346\201\257\346\237\245\350\257\242", Q_NULLPTR));
        courseButton->setText(QApplication::translate("MainWindow", "\347\255\276\345\210\260\344\277\241\346\201\257", Q_NULLPTR));
        stuButton->setText(QApplication::translate("MainWindow", "\345\255\246\347\224\237\344\277\241\346\201\257", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\344\270\252\344\272\272\344\277\241\346\201\257", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\267\245\345\217\267\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\247\223\345\220\215\357\274\232", Q_NULLPTR));
        numtext->setText(QApplication::translate("MainWindow", "num", Q_NULLPTR));
        nametext->setText(QApplication::translate("MainWindow", "name", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\257\276\347\250\213", Q_NULLPTR));
        groupBox->setStyleSheet(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\347\255\276\345\210\260", Q_NULLPTR));
        closeButton->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        openButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        photoButton->setText(QApplication::translate("MainWindow", "\346\213\215\346\221\204\347\205\247\347\211\207", Q_NULLPTR));
        recognizeButton->setText(QApplication::translate("MainWindow", "\350\257\206\345\210\253", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "camera", Q_NULLPTR));
        cameralabel->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\344\272\272\350\204\270\350\257\206\345\210\253\347\255\276\345\210\260\347\263\273\347\273\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
