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
    std::string filename = "booksData.csv";
    std::ifstream inFile;
    inFile.open(filename);

    if(!inFile)
    {
        std::cout<<"Unable to open file booksData.csv.\n";
        exit(1);
    }

    std::string line;

    while(std::getline (inFile, line))
    {
        /* Fill the Book vector with data */

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
    /* Generates a vector of random books with the parameters by the user */
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
    /*discards duplicates given by random*/
    for(int i = 0; i < lst.size(); i++) {
        if(idn == lst[i].id) {
            return 0;
        }
    }
    return 1;
}

int Collection::in_user_list(int idn) {
    /*discards books for random list that are already in user list*/
    for(int i = 0; i < this->user_list.size(); i++) {
        if(idn == this->user_list[i]) {
            return 0;
        }
    }
    return 1;
}

void Collection::display_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books)
{
    /*displays random list of books as buttons*/

    QWidget *display_window =new QWidget;
    display_window->setWindowTitle("Try These");
    QVBoxLayout* compile=new QVBoxLayout;

    /*makes button for each book in random list*/
    for(int i=0;i<rand_list.size()-1;i++)
    {
        QSignalMapper *mapper=new QSignalMapper();
        QPushButton *more_info=new QPushButton(QString::fromStdString(rand_list[i].title));
        compile->addWidget(more_info);
        QObject::connect(more_info, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(more_info, rand_list[i].id);
        QObject::connect(mapper, SIGNAL(mapped(int)), books, SLOT(extra_info(int)));
    }

    QPushButton *exit=new QPushButton("  Back ");
    compile->addWidget(exit);
    QObject::connect(exit, SIGNAL(clicked()), display_window, SLOT(close()));

    display_window->setLayout(compile);
    display_window->show();
}

void Collection::extra_info(int id)
{
    /*displays information about book selected from random list*/

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
    QString num_jpg=QString::number(id);
    QPixmap image("images/book_"+num_jpg+".jpg");
    QLabel* picture=new QLabel();
    picture->setPixmap(image);
    about->setWordWrap(true);

    /* Buttons to operate window */
    QPushButton *exit=new QPushButton("  Exit");
    QObject::connect(exit, SIGNAL(clicked()), window, SLOT(close()));

    QSignalMapper *mapper1 = new QSignalMapper();
    QPushButton *to_read = new QPushButton("  Add to Read List");
    QObject::connect(to_read, SIGNAL(clicked()), mapper1, SLOT(map()));
    mapper1->setMapping(to_read, id);
    QObject::connect(mapper1, SIGNAL(mapped(int)), SLOT(add_book(int)));

    QSignalMapper *mapper2=new QSignalMapper();
    QPushButton *buybutton=new QPushButton("  Buy Book");
    QObject::connect(buybutton, SIGNAL(clicked()), mapper2, SLOT(map()));
    mapper2->setMapping(buybutton, id);
    QObject::connect(mapper2, SIGNAL(mapped(int)), SLOT(buy_book(int)));


    //organizes info
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

    button_bar->addWidget(to_read);
    button_bar->addWidget(buybutton);
    button_bar->addWidget(exit);

    all_info->addLayout(info_tab);
    all_info->addLayout(button_bar);

    window->setLayout(all_info);
    window->show();
}

/*User List Functions*/

void Collection::buy_book(int idn)
{
    /*opens link to selected book*/

    QString link = QString::fromStdString(get_book(idn).link);
    QDesktopServices::openUrl(QUrl(link));
}

void Collection::add_book(int idn)
{
    /*adds book to user list*/

    this->user_list.push_back(idn);
    QWidget* window=new QWidget;
    QLabel *label=new QLabel("Book has been added to your list!");
    QPushButton *okay=new QPushButton("OK");
    QObject::connect(okay, SIGNAL(clicked()), window, SLOT(close()));
    QVBoxLayout *notify=new QVBoxLayout;
    notify->addWidget(label);
    notify->addWidget(okay);
    window->setLayout(notify);
    window->show();
   this->output_file("userData.dat");
}

void Collection::delete_book(int idn)
{
    /*removes book from user list*/

    this->output_file("userData.dat");
    return;
}

void Collection::read_user_file(std::string filename)
{
    /*reads user file for previously stored books*/

    std::ifstream inFile;
    inFile.open(filename);

    if(!inFile)
    {
        std::cout<<"Unable to open file userData.dat.\n";
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
        this->user_list.push_back(test);
//        line.erase(0, pos+1);
    }
}

void Collection::output_file(std::string filename)
{
    /*outputs stored user list*/
    
    std::ofstream outFile;
    outFile.open(filename);
    int i = 0;

    while (i < (this->user_list.size()))
    {
        outFile<<this->user_list[i]<< std::endl;
        i++;
    }
    outFile.close();
}
