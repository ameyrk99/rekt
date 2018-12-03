#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>
#include <QStyledItemDelegate>
#include <QWidget>
#include <QtWidgets>
#include <QMetaType>
#include <QPointF>
#include <QVector>

#include "randListWindow.h"

namespace Ui {
class ChoiceWindow;
}

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChoiceWindow(QWidget *parent = nullptr);
    ~ChoiceWindow();
    Collection *books;
    std::vector <int> genres_chosen; /*holds the number(s) corresponding to the genre(s) selected*/
    std::vector <Book> books_added; /*holds all books*/
    std::vector <int> id_nums; /*stores a vector of all the books the user wants to read*/
    int year;
    int rating;
    QListView *userListView;
    QStringListModel *model;

private:
    Ui::ChoiceWindow *ui;
    void connect_Signals(); /*connects the value of the slider to the scroll box*/
    void disconnect_Signals(); /*disconnects the value of the slider to the scroll box*/
    void connect_rating_Signals(); /*connects how many stars the user wants to find a book with to a dial widget*/
    void disconnect_rating_Signals(); /*disconnects how many stars the user wants to find a book with to a dial widget*/
    void read_list(); /*stores a list of all things the user wants to read*/

public slots:
    void on_deleteButton_clicked(); /*deletes a book from the user list*/
    void on_info_button_clicked(); /*displays information about book selected*/
    void user_list_buy_book(int idn); /*opens link to book*/

private slots: /*adds a new slot that connects the two values into one slot*/
    void new_Value_Changed(int newValue); /*changes value for year based on user input*/
    void new_Rating_Changed(int newRating); /*changes value for rating based on user input*/

    /*signal handler for each genre*/
    void on_genre_crime_clicked();
    void on_genre_ficiton_clicked();
    void on_genre_non_fiction_clicked();
    void on_genre_mystery_clicked();
    void on_genre_classic_clicked();
    void on_genre_manga_clicked();
    void on_genre_sci_fi_clicked();
    void on_genre_historical_clicked();
    void on_genre_horror_clicked();
    void on_genre_thriller_clicked();
    void on_genre_romance_clicked();
    void on_genre_cookbook_clicked();
    void on_genre_suspense_clicked();
    void on_genre_humor_clicked();
    void on_genre_fantasy_clicked();

    void on_button_userlist_clicked(); /*displays user list and options*/
    void on_button_find_clicked(); /*compiles user choices for generating random list of books that fit description*/
    void on_button_exit_clicked();
    void on_button_refresh_clicked(); /*resets user values*/
};

#endif
