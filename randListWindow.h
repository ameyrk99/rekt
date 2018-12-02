#ifndef RANDLIST_H
#define RANDLIST_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <cstdlib>

namespace Ui {
class RandList;
}

class Book {
    public:
        int id;
        std::string title;
        std::string author;
        int year;
        float rating;
        std::string link;
        std::string about;
};

class Collection: public QObject
{
    Q_OBJECT
protected:
        std::vector <Book> list;

public:
        std::vector <Book> get_list();
        int already_there(int idn, std::vector <Book> lst);
        Book get_book(int n);
        void read_file();
        std::vector <Book> get_rand_list(std::vector <int> genres_indexes, float rating, int year);

public slots:
        void extra_info(int id);
        void buy_book(int idn);
};

class RandList : public QMainWindow
{
    Q_OBJECT
public:

    explicit RandList(QWidget *parent = nullptr);
    ~RandList();

private:
    Ui::RandList *ui;
};

void print_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books);

#endif
