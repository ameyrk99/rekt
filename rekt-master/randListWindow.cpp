#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <QLabel>
#include <QFont>
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

Book Collection::get_book(int n)
{
    return this->list[n];
}

void Collection::read_file()
{
    /*Reads file*/
    std::string filename = "../rekt-master/booksData.csv";
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

/*returns vector with books (limit 9) that fit user description in random order*/
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
            if(this->list[potential_book].year >= year && this->list[potential_book].rating >= rating && duplicate) {
                rand_list.push_back(this->list[potential_book]);
                book_not_done--;
            }
        }

        book_not_done = 10/total_genres;            /*Reset value for next book*/
    }

    return rand_list;
}

/*discards duplicates given by random*/
int Collection::already_there(int idn, std::vector <Book> lst) {
    for(int i = 0; i < lst.size(); i++) {
        if(idn == lst[i].id) {
            return 0;
        }
    }
    return 1;
}

void Collection::extra_info(int id) /*displays information about book selected from random list*/
{
    //gets book info
    QWidget* window=new QWidget;
    QLabel* title=new QLabel(QString::fromStdString(get_book(id).title));
    QFont titleFont("", 16, QFont::Bold);
    title->setFont(titleFont);
    title->setWordWrap(true);
    QLabel* author=new QLabel(QString::fromStdString(get_book(id).author));
    QFont authorFont("", 14);
    author->setFont(authorFont);
    QLabel* about=new QLabel(QString::fromStdString(get_book(id).about));
    QLabel* year=new QLabel(QString::fromStdString(std::to_string(get_book(id).year)));

    std::ostringstream out;
    out.precision(2);
    out << std::fixed << get_book(id).rating;
    QLabel* rating=new QLabel(QString::fromStdString(out.str()));

    //display image
    QString num_jpg=QString::number(id);
    QPixmap image("../rekt-master/images/book_"+num_jpg+".jpg");
    QLabel* picture=new QLabel();
    picture->setPixmap(image);
    about->setWordWrap(true);

    //exit book info
    QPushButton *exit=new QPushButton("  Exit");
    QObject::connect(exit, SIGNAL(clicked()), window, SLOT(close()));

    //button for link to buy book
    QSignalMapper *mapper=new QSignalMapper();
    QPushButton *buybutton=new QPushButton("  Buy Book");
    QObject::connect(buybutton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(buybutton, id);
    QObject::connect(mapper, SIGNAL(mapped(int)), SLOT(buy_book(int)));

    //organizes widgets for window
    QVBoxLayout *all_info = new QVBoxLayout;
    QHBoxLayout *button_bar = new QHBoxLayout;
    QHBoxLayout *info_tab = new QHBoxLayout;
    QVBoxLayout *left_panel = new QVBoxLayout;
    QVBoxLayout *right_panel = new QVBoxLayout;
    QVBoxLayout* top_info=new QVBoxLayout;
    QHBoxLayout* bottom_info=new QHBoxLayout;
    top_info->addWidget(title);
    top_info->addWidget(author);
    top_info->addWidget(year);
    top_info->addWidget(rating);
    bottom_info->addWidget(about);

    left_panel->addLayout(top_info);
    left_panel->addLayout(bottom_info);

    left_panel->addSpacing(300);

    right_panel->addWidget(picture);

    info_tab->addLayout(left_panel);
    info_tab->addLayout(right_panel);

    button_bar->addWidget(buybutton);
    button_bar->addWidget(exit);

    all_info->addLayout(info_tab);
    all_info->addLayout(button_bar);

    window->setLayout(all_info);
    window->show();

}

/*User List Functions*/

void Collection::buy_book(int id) /*opens link to selected book*/
{
        QString link = QString::fromStdString(get_book(id).link);
        QDesktopServices::openUrl(QUrl(link));
}

/*displays random list of books as buttons*/
void print_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books)
{
    QWidget* window=new QWidget;
    window->setWindowTitle("RecommUi");
    QVBoxLayout* compile=new QVBoxLayout;

    QLabel* title=new QLabel("RecommUi");
    QFont titleFont("", 16);
    title->setFont(titleFont);
    compile->addWidget(title);

    /*makes button for each book in random list*/
    for(int i=0;i<rand_list.size()-1;i++)
    {
        QSignalMapper *mapper=new QSignalMapper();
        QPushButton *more_info=new QPushButton("  " + QString::fromStdString(rand_list[i].title));
        compile->addWidget(more_info);
        QObject::connect(more_info, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(more_info, rand_list[i].id);
        QObject::connect(mapper, SIGNAL(mapped(int)), books, SLOT(extra_info(int)));
    }

    QPushButton *exit=new QPushButton("  Exit");
    compile->addWidget(exit);
    QObject::connect(exit, SIGNAL(clicked()), window, SLOT(close()));

    window->setLayout(compile);
    window->show();
}
