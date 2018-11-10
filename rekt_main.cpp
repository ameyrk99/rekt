#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "book.h"

void print_books(std::vector <Book> rand_list, std::vector <std::string> genres);

int main()
{
    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};
    Collection books;

    books.read_file();

    std::cout<<"---REKT---\n\n\n";

    for(int i = 0; i < 15; i++) {
        std::cout<<"["<<i<<"] "<<genres[i]<<" ";
        if(i%3 == 0 && i != 0) {
            std::cout<<"\n";
        }
    }
    std::cout<<"\n";

    std::cout<<"Enter genres you want[up to 10]: ";
    std::vector <int> genres_chosen;
    int input;
    for(int i = 0; i < 10; i++) {
        std::cin>>input;
        if(input == 999) {break;}

        genres_chosen.push_back(input);
    }

    std::cout<<"Enter minimum rating you desire you want[0 - 5]: ";
    float rating;
    std::cin>>rating;

    std::cout<<"Enter minimum year you desire you want: ";
    int year;
    std::cin>>year;

    std::vector <Book> rand_gen = books.get_rand_list(genres_chosen, rating, year);

    std::cout<<"\n";
    print_books(rand_gen, genres);
    return 0;
}

void print_books(std::vector <Book> rand_list, std::vector <std::string> genres) {
    for(int i = 0; i < 10; i++) {
        int genre_id = (int) rand_list[i].id/40;
        std::cout<<"# "<<rand_list[i].id<<" ["<<genres[genre_id]<<"]\n"<<"Id:\t"<<rand_list[i].id<<"\nAuthor:\t"+rand_list[i].author+
        "\nTitle:\t"+rand_list[i].title+"\n\n";
    }
}
