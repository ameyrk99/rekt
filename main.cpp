#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QSignalMapper>
#include <QTextStream>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QStyle>
#include <QTimer>
#include <QMovie>

#include "randListWindow.h"
#include "choicewindow.h"

//UserFile userList(books);

void print_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Choice Window ----------------------------------------------------------------------------------------------------------------------------
     */

    ChoiceWindow w;


    /*
     * Splash Screen ----------------------------------------------------------------------------------------------------------------------------
     */

    QMovie *movie = new QMovie("book.gif");
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
