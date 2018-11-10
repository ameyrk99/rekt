#include <string>
#include <vector>
#include <cstdlib>

#ifndef BOOK_H
#define BOOK_H

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

class Collection {
    protected:
        std::vector <Book> list;

    public:
        std::vector <Book> get_list();
        void read_file();
        std::vector <Book> get_rand_list(std::vector <int> genres_indexes, float rating, int year);
};

#endif
