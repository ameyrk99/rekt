#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QDesktopServices>
#include <QUrl>

#include "randListWindow.h"
#include "ui_randlistwindow.h"

RandList::RandList(QWidget *parent) : QMainWindow(parent), ui(new Ui::RandList)
{
    ui->setupUi(this);
}

RandList::~RandList()
{
    delete ui;
}

std::vector <Book> Collection::get_list()
{
    return this->list;
}

std::vector <int> Collection::get_user_list()
{
    return this->user_list;
}

Book Collection::get_book(int n)
{
    return this->list[n];
}

void Collection::read_file()
{
    /*Reads file*/
    std::string filename = "../rekt/booksData.csv";
    std::ifstream inFile;
    inFile.open(filename);

    if(!inFile)
    {
        std::cout<<"Unable to open file.\n";
        exit(1);
    }

    std::string line;

    while(std::getline (inFile, line))
    {

        std::string delimiter = "~";
        size_t pos = 0;
        std::string token;
        Book b;

        /*Adding ID*/
        pos = line.find(delimiter);
        b.id = std::stoi(line.substr(0, pos));
        line.erase(0, pos+1);

        /*Adding title*/
        pos = line.find(delimiter);
        b.title = line.substr(0, pos);
        line.erase(0, pos+1);

        /*Adding author*/
        pos = line.find(delimiter);
        b.author = line.substr(0, pos);
        line.erase(0, pos+1);

        /*Adding year*/
        pos = line.find(delimiter);
        b.year = std::stoi(line.substr(0, pos));
        line.erase(0, pos+1);

        /*Adding rating*/
        pos = line.find(delimiter);
        b.rating = std::stof(line.substr(0, pos));
        line.erase(0, pos+1);

        /*Adding link*/
        pos = line.find(delimiter);
        b.link = line.substr(0, pos);
        line.erase(0, pos+1);

        /*Adding about*/
        b.about = line;

        this->list.push_back(b);
    }

    inFile.close();
}

std::vector <Book> Collection::get_rand_list(std::vector <int> genres_indexes, float rating, int year) {
    int total_genres = genres_indexes.size();
    std::vector <Book> rand_list;
    /*Seed for random*/
    std::srand(time(NULL));

    int book_not_done = 10/total_genres;          /*number of Books per genre*/

    for(int i = 0; i < total_genres; i++) {

        if(i == total_genres - 1) {
            /*Give the last genre all the remaining books*/
            book_not_done += 10%total_genres;
        }

        for(int j = 0; j < 20 && book_not_done; j++) {                              /*Generates random indexes in range 20 times*/
            int potential_book = (std::rand()%40)+(40*genres_indexes[i]);           /*Generate random int from 0 - 39, and scale it up for the required genre*/

            int duplicate = this->already_there(potential_book, rand_list);
            if(this->list[potential_book].year >= year && this->list[potential_book].rating >= rating &&
                    this->in_user_list((potential_book)) && duplicate) {
                rand_list.push_back(this->list[potential_book]);
                book_not_done--;
            }
        }

        book_not_done = 10/total_genres;            /*Reset value for next book*/
    }

    return rand_list;
}

int Collection::already_there(int idn, std::vector <Book> lst) {
    for(int i = 0; i < lst.size(); i++) {
        if(idn == lst[i].id) {
            return 0;
        }
    }
    return 1;
}

int Collection::in_user_list(int idn){
    for(int i = 0; i < this->user_list.size(); i++) {
        if(idn == this->user_list[i]) {
            return 0;
        }
    }
    return 1;
}

void Collection::extra_info(int id)
{
    //gets info
    QWidget* window=new QWidget;
    QLabel* title=new QLabel(QString::fromStdString(get_book(id).title));
    QLabel* author=new QLabel(QString::fromStdString(get_book(id).author));
    QLabel* about=new QLabel(QString::fromStdString(get_book(id).about));
    QLabel* year=new QLabel(QString::fromStdString(std::to_string(get_book(id).year)));
    QLabel* rating=new QLabel(QString::fromStdString(std::to_string(get_book(id).rating)));
    QString num_jpg=QString::number(id);
    QPixmap image("../rekt/images/book_"+num_jpg+".jpg");
    QLabel* picture=new QLabel();
    picture->setPixmap(image);
    about->setWordWrap(true);

    QPushButton *exit=new QPushButton("Exit");
    QObject::connect(exit, SIGNAL(clicked()), window, SLOT(close()));

    QSignalMapper *mapper=new QSignalMapper();
    QPushButton *addtolist=new QPushButton("Buy Book");
    QObject::connect(addtolist, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(addtolist, id);
    QObject::connect(mapper, SIGNAL(mapped(int)), SLOT(buy_book(int)));

    //organizes info
    QVBoxLayout* top_info=new QVBoxLayout;
    QHBoxLayout* bottom_info=new QHBoxLayout;
    QHBoxLayout* buttons=new QHBoxLayout;
    QVBoxLayout* all_info=new QVBoxLayout;
    top_info->addWidget(title);
    top_info->addWidget(author);
    top_info->addWidget(year);
    top_info->addWidget(rating);
//    top_info->addWidget(link);
    bottom_info->addWidget(about);
    bottom_info->addWidget(picture);
    buttons->addWidget(addtolist);
    buttons->addWidget(exit);
    all_info->addLayout(top_info);
    all_info->addLayout(bottom_info);
    all_info->addLayout(buttons);
    window->setLayout(all_info);
    window->show();
}

/*User List Functions*/

void Collection::buy_book(int id)
{
        QString link = QString::fromStdString(get_book(id).link);
        QDesktopServices::openUrl(QUrl(link));
}


void print_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books)
{
    QWidget* window=new QWidget;
    window->setWindowTitle("RecommUi");
    QVBoxLayout* compile=new QVBoxLayout;
    for(int i=0;i<rand_list.size()-1;i++)
    {
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
