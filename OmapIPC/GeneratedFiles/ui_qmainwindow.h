/********************************************************************************
** Form generated from reading UI file 'qmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMAINWINDOW_H
#define UI_QMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMainWindowClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QMainWindowClass)
    {
        if (QMainWindowClass->objectName().isEmpty())
            QMainWindowClass->setObjectName(QStringLiteral("QMainWindowClass"));
        QMainWindowClass->resize(600, 400);
        centralWidget = new QWidget(QMainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton1 = new QPushButton(centralWidget);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        pushButton1->setGeometry(QRect(10, 0, 161, 81));
        pushButton1->setCheckable(false);
        pushButton1->setAutoDefault(false);
        pushButton2 = new QPushButton(centralWidget);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        pushButton2->setGeometry(QRect(390, 10, 121, 81));
        pushButton3 = new QPushButton(centralWidget);
        pushButton3->setObjectName(QStringLiteral("pushButton3"));
        pushButton3->setGeometry(QRect(390, 110, 121, 81));
        QMainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QMainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        QMainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QMainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QMainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QMainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QMainWindowClass->setStatusBar(statusBar);

        retranslateUi(QMainWindowClass);
        QObject::connect(pushButton1, SIGNAL(clicked()), QMainWindowClass, SLOT(on_pushButton_clicked()));
        QObject::connect(pushButton2, SIGNAL(clicked()), QMainWindowClass, SLOT(on_SetTmpSign_clicked()));
        QObject::connect(pushButton3, SIGNAL(clicked()), QMainWindowClass, SLOT(on_GetLatLig_clicked()));

        QMetaObject::connectSlotsByName(QMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *QMainWindowClass)
    {
        QMainWindowClass->setWindowTitle(QApplication::translate("QMainWindowClass", "OMapApiTest", Q_NULLPTR));
        pushButton1->setText(QApplication::translate("QMainWindowClass", "\345\220\257\345\212\250OMap", Q_NULLPTR));
        pushButton2->setText(QApplication::translate("QMainWindowClass", "\350\256\276\347\275\256\344\270\264\346\227\266\345\234\260\347\202\271\346\240\207\347\255\276", Q_NULLPTR));
        pushButton3->setText(QApplication::translate("QMainWindowClass", "\344\273\216Omap\345\217\226\347\273\217\347\272\254\345\272\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QMainWindowClass: public Ui_QMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMAINWINDOW_H
