/********************************************************************************
** Form generated from reading UI file 'splashwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLASHWINDOW_H
#define UI_SPLASHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Splashwindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Splashwindow)
    {
        if (Splashwindow->objectName().isEmpty())
            Splashwindow->setObjectName(QStringLiteral("Splashwindow"));
        Splashwindow->resize(400, 300);
        centralWidget = new QWidget(Splashwindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 40, 231, 161));
        Splashwindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Splashwindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        Splashwindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Splashwindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Splashwindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Splashwindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Splashwindow->setStatusBar(statusBar);

        retranslateUi(Splashwindow);

        QMetaObject::connectSlotsByName(Splashwindow);
    } // setupUi

    void retranslateUi(QMainWindow *Splashwindow)
    {
        Splashwindow->setWindowTitle(QApplication::translate("Splashwindow", "Splashwindow", nullptr));
        pushButton->setText(QApplication::translate("Splashwindow", "Rekt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Splashwindow: public Ui_Splashwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLASHWINDOW_H
