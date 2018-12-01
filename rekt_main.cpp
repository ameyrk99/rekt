#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "book.h"

Collection books;
UserFile userList(books);

void print_books(std::vector <Book> rand_list, std::vector <std::string> genres);

int main(int argc, char *argv[])
{
    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};
    // Collection books;

    books.read_file();

    std::cout<<"---REKT---\n\n\n";

    for(int i = 0; i < 15; i++) 
    {
        std::cout<<"["<<i<<"] "<<genres[i]<<" ";
        if(i%3 == 0 && i != 0) {
            std::cout<<"\n";
        }
    }
    std::cout<<"\n";

    std::cout<<"Enter genres you want[up to 10]: ";
    std::vector <int> genres_chosen;
    int input;
    for(int i = 0; i < 10; i++) 
    {
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
    std::cout << "\n";
    print_books(rand_gen, genres);

    // UserFile userList(books);
    if (argc > 1) {
        userList.read_file(argv[1]);
    }

    bool check = true;
    std::string line;
    int bookId;

    while (check)
    {
        std::cout << "\nWould you like to add or delete a book from the list? [a/d]" << std::endl;
        std::cin >> line;
        if (line == "exit")
        {
            check = false;
        }
        else if (line == "a")
        {
            std::cout << "Enter id of book you would like to add: " << std::endl;
            std::cin >> bookId;
            userList.add_book(bookId);          
        }
        else if (line == "d")
        {
            std::cout << "Enter id of book you would like to delete: " << std::endl;
            std::cin >> bookId;
            userList.delete_book(bookId);
        }
    }

    if (argc == 1) {
        userList.output_file("filename.txt");
    }
    else
    {
        userList.output_file(argv[1]);
    }

    return 0;
}

void print_books(std::vector <Book> rand_list, std::vector <std::string> genres) {
    for(int i = 0; i < 10; i++) {
        int genre_id = (int) rand_list[i].id/40;
        std::cout<<"# "<<rand_list[i].id<<" ["<<genres[genre_id]<<"]\n"<<"Id:\t"<<rand_list[i].id<<"\nAuthor:\t"+rand_list[i].author+
        "\nTitle:\t"+rand_list[i].title+"\n\n";
    }
}
