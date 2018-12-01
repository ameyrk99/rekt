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

std::vector <Book> Collection::get_user_list()
{
    return this->user_list;
}

Book Collection::get_book(int n)
{
    return this->list[n];
}

Book Collection::get_user_list_book(int n)
{
    return this->user_list[n];
}

void Collection::read_file()
{
    /*Reads file*/
    std::string filename = "booksData.csv";
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

            if(this->list[potential_book].year >= year && this->list[potential_book].rating >= rating) {
                /*Check if requirements are satisfied*/
                rand_list.push_back(this->list[potential_book]);
                book_not_done--;
            }
        }

        book_not_done = 10/total_genres;            /*Reset value for next book*/
    }

    return rand_list;
}

void Collection::extra_info(int id)
{
    //gets info
    QWidget* window=new QWidget;
    QLabel* title=new QLabel(QString::fromStdString(get_book(id).title));
    QLabel* author=new QLabel(QString::fromStdString(get_book(id).author));
    QLabel* about=new QLabel(QString::fromStdString(get_book(id).about));
    QString num_jpg=QString::number(id);
    QPixmap image("images/book_"+num_jpg+".jpg");
    QLabel* picture=new QLabel();
    picture->setPixmap(image);
    about->setWordWrap(true);

    QPushButton *exit=new QPushButton("Exit");
    QObject::connect(exit, SIGNAL(clicked()), window, SLOT(close()));

    QSignalMapper *mapper=new QSignalMapper();
    QPushButton *addtolist=new QPushButton("Add book to user list");
    QObject::connect(addtolist, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(addtolist, id);
    QObject::connect(mapper, SIGNAL(mapped(int)), SLOT(add_book(int)));

    //organizes info
    QVBoxLayout* top_info=new QVBoxLayout;
    QHBoxLayout* bottom_info=new QHBoxLayout;
    QHBoxLayout* buttons=new QHBoxLayout;
    QVBoxLayout* all_info=new QVBoxLayout;
    top_info->addWidget(title);
    top_info->addWidget(author);
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

void Collection::add_book(int id)
{
    //adds book
    //bool duplicate=false;
    Book b1=get_book(id);
    //checks for duplicates
    /*for(int i=0;i<book_lists.size()&&!duplicate;i++)
    {
        std::cout<<"test"<<std::endl;
        Book b2=get_user_list_book(i);

        if(b1.id==b2.id)
        {
            duplicate=true;
            QWidget* window=new QWidget;
            QLabel *youdumby=new QLabel("Book is already in your list!");
            QPushButton *okay=new QPushButton("OK");
            QObject::connect(okay, SIGNAL(clicked()), window, SLOT(close()));
            QVBoxLayout *notify=new QVBoxLayout;
            notify->addWidget(youdumby);
            notify->addWidget(okay);
            window->setLayout(notify);
            window->show();
        }
    }*/

    //displays accomodating message
   //if(duplicate==false)
   //{
       get_user_list().push_back(b1);
       QWidget* window=new QWidget;
       QLabel *label=new QLabel("Book has been added to your list!");
       QPushButton *okay=new QPushButton("OK");
       QObject::connect(okay, SIGNAL(clicked()), window, SLOT(close()));
       QVBoxLayout *notify=new QVBoxLayout;
       notify->addWidget(label);
       notify->addWidget(okay);
       window->setLayout(notify);
       window->show();
   //}
}


UserFile::UserFile(Collection *origList)
{
    l = origList->get_list();
}

void UserFile::read_file(std::string filename)
{
    /*Reads file*/
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

        std::string delimiter = "\n";
        size_t pos = 0;
        std::string token;
        int test = 0;

        pos = line.find(delimiter);
        test = std::stoi(line.substr(0, pos));
        user_list.push_back(test);
//        line.erase(0, pos+1);
    }
}

void UserFile::add_book(int idn)
{
    Book temp = l[idn];
    int toAdd = temp.id;
    int i = 0;
    while (i < (user_list.size()))      // Checks for duplicates
    {
        if (toAdd == user_list[i])
        {
            return;
        }
        i++;
    }
    user_list.push_back(toAdd);
}

void UserFile::delete_book(int idn)
{
    Book temp = l[idn];
    int toAdd = temp.id;
    int i = 0;
    while (i < (user_list.size()))
    {
        if (toAdd == user_list[i])
        {
            user_list.erase(user_list.begin() + i);
            break;
        }
        i++;
    }
}

void UserFile::output_file(std::string filename)
{
    std::ofstream outFile;
    outFile.open(filename);
    int i = 0;

    while (i < (user_list.size()))
    {
        Book temp = l[user_list[i]];
        outFile << temp.id << std::endl;
//        outFile << temp.id << "~" << temp.title << "~" << temp.author << "~" << temp.link << std::endl;
        i++;
    }
}

UserFile::~UserFile()
{}









