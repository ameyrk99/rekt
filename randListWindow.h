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
        std::vector <Book> user_list;

public:
        std::vector <Book> get_list();
        std::vector <Book> get_user_list();
        Book get_book(int n);
        Book get_user_list_book(int n);
        void read_file();
        std::vector <Book> get_rand_list(std::vector <int> genres_indexes, float rating, int year);
public slots:
        void extra_info(int id);
        void add_book(/*Collection l,*/ int idn);
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

class UserFile
{
    protected:
//        std::vector <Book> l;
//        std::vector <int> user_list;

    public:
        std::vector <Book> l;
        std::vector <int> user_list;
        UserFile(Collection *origList);
        virtual ~UserFile();
        void read_file(std::string filename);
        void add_book(int idn);
        void delete_book(int idn);
        void output_file(std::string filename);
};

#endif // BOOKS_H
