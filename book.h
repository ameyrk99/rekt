#include <string>
#include <vector>
#include <cstdlib>

#ifndef BOOK_H
#define BOOK_H

class Book 
{
    public:
        int id;
        std::string title;
        std::string author;
        int year;
        float rating;
        std::string link;
        std::string about;
};

class Collection 
{
    protected:
        std::vector <Book> list;

    public:
        std::vector <Book> get_list();
        void read_file();
        std::vector <Book> get_rand_list(std::vector <int> genres_indexes, float rating, int year);
};

class UserFile
{
    protected:
        std::vector <Book> l;
        std::vector <int> user_list;

    public:
        UserFile(Collection origList);
        virtual ~UserFile();
        void read_file(std::string filename);
        void add_book(int idn);
        void delete_book(int idn);
        void output_file(std::string filename);
};

#endif
