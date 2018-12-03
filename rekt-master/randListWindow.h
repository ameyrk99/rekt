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
        std::vector <Book> list; /*contains all books*/
        std::vector <int> user_list; /*contains ints of books added by user*/

public:
        std::vector <Book> get_list();
        std::vector <int> get_user_list();
        Book get_book(int n); /*returns book from list*/

        void read_file();

        std::vector <Book> get_rand_list(std::vector <int> genres_indexes, float rating, int year); /*returns vector with books that fit user description in random order*/
        void display_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books); /*displays random list of books as buttons*/
        int already_there(int idn, std::vector <Book> lst); /*prevents duplicates from showing in random list*/

        /*User List Functions*/
        int in_user_list(int idn);
        void read_user_file(std::string filename); /*reads user file for stored books*/
        void delete_book(int idn);
        void output_file(std::string filename); /*outputs stored user list*/

        friend class ChoiceWindow;

public slots:
        void extra_info(int id); /*displays information about book selected from random list*/
        void add_book(int idn); /*adds book to user list*/
        void buy_book(int idn); /*opens link to selected book*/
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

#endif
