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

Collection *books=new Collection();
//UserFile userList(books);

void print_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books)
{
    QWidget* window=new QWidget;
    QVBoxLayout* compile=new QVBoxLayout;
    for(int i=0;i<rand_list.size()-1;i++)
    {
        //int genre_id = rand_list[i].id/40; //for the genre
        //std::cout<<"# "<<rand_list[i].id<<" ["<<genres[genre_id]<<"]\n"<<"Id:\t"<<rand_list[i].id<<"\nAuthor:\t"<<rand_list[i].author<<"\nTitle:\t"<<rand_list[i].title<<"\n\n"<<std::endl;

        QSignalMapper *mapper=new QSignalMapper();
        QPushButton *more_info=new QPushButton(QString::fromStdString(rand_list[i].title));
        compile->addWidget(more_info);
        QObject::connect(more_info, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(more_info, rand_list[i].id);
        QObject::connect(mapper, SIGNAL(mapped(int)), books, SLOT(extra_info(int)));
    }
    QPushButton *exit=new QPushButton("Exit");
    compile->addWidget(exit);
    QObject::connect(exit, SIGNAL(clicked()), window, SLOT(close()));
    window->setLayout(compile);
    window->show();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};
//    Collection *books=new Collection();
    books->read_file();

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

    /*
     * Random List Display ----------------------------------------------------------------------------------------------------------------------------
     */

    //sample input
    std::vector <int> genres_chosen= {3, 6, 4};
    float rating=4;
    int year=2000;

    std::vector <Book> rand_gen = books->get_rand_list(genres_chosen, rating, year);


    print_books(rand_gen, genres, books);

    UserFile userList(books);
//    std::cout<<userList.l.size()<<std::endl;
    userList.read_file("userData.txt");
    userList.user_list = {100, 23, 20, 4};
    userList.output_file("userData.txt");

    return a.exec();
}
