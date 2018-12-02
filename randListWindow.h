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
        std::vector <int> user_list;

public:
        std::vector <Book> get_list();
        std::vector <int> get_user_list();
        int in_user_list(int idn);
        int already_there(int idn, std::vector <Book> lst);
        Book get_book(int n);
//        Book get_user_list_book(int n);
        void read_file();
        std::vector <Book> get_rand_list(std::vector <int> genres_indexes, float rating, int year);
        void display_books(std::vector <Book> rand_list, std::vector <std::string> genres, Collection *books);
        friend class ChoiceWindow;

public slots:
        void extra_info(int id);

        /*User List Functions*/
        void buy_book(int idn);
        void add_book(int idn);
//        void remove_book_userlist(int idn);
        void read_user_file(std::string filename);
        void delete_book(int idn);
        void output_file(std::string filename);
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

#endif // BOOKS_H
