#include "splashwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QStyle>
#include <QTimer>
#include <QLabel>
#include <QMovie>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Splashwindow w;

    /*Change the path below to where you keep it*/
    QMovie *movie = new QMovie("/home/mark/MEGA/Code/book.gif");
    QLabel *processLabel = new QLabel(nullptr);

    processLabel->resize(400,400);  // to make sure its large enough

    processLabel->setMovie(movie);
    processLabel->setWindowFlags(Qt::FramelessWindowHint);
    processLabel->setAlignment(Qt::AlignCenter);
    processLabel->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,processLabel->size(),qApp->desktop()->availableGeometry()));

    movie->start();
    processLabel->show();

    QTimer::singleShot(3000,processLabel,SLOT(close()));
    QTimer::singleShot(3000,&w,SLOT(show()));

    return a.exec();
}
