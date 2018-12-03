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
    Collection *books; /*creates an a Collection object*/
    std::vector <int> genres_chosen; /*holds all the genres wanted by the user*/
    std::vector <Book> books_added; /*holds all the books wanted by the user*/
    std::vector <int> id_nums; /*stores a vector of all the books the user wants to read*/
    int year; /*holds the year designated by the user*/
    int rating; /*holds the rating designated by the user*/
    QListView *userListView; /*creates a QListView layout*/
    QStringListModel *model; /*holds the list that will be displayed by the QListView layout*/

private:
    Ui::ChoiceWindow *ui;
    void connect_Signals(); /*connects the value of the slider to the scroll box*/
    void disconnect_Signals(); /*disconnects the value of the slider to the scroll box*/
    void connect_rating_Signals(); /*connects how many stars the user wants to find a book with to a dial widget*/
    void disconnect_rating_Signals(); /*disconnects how many stars the user wants to find a book with to a dial widget*/
    void read_list(); /*stores a list of all things the user wants to read*/

public slots:
    void on_deleteButton_clicked(); /*deletes a book from the user list*/
    void on_info_button_clicked(); /*shows the info about a random book*/
    void user_list_buy_book(int idn); /*connects to the GoodReads website where the user can buy the book*/

private slots: /*adds a new slot that connects the two values into one slot*/
    void new_Value_Changed(int newValue); /*connects the values of the spinbox and slider for the year chosen by the user*/
    void new_Rating_Changed(int newRating); /*connects the values of the spinbox and dial for the rating chosen by the user*/

    /*checks what genres were checked by the user in the check box*/
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

    void on_button_userlist_clicked(); /*opens a new window of a list all the books the user wants to read*/
    void on_button_find_clicked(); /*opens a new window on any browser to a link where the user can buy a specific book*/
    void on_button_exit_clicked(); /*exits out of the main window*/
    void on_button_refresh_clicked(); /*refreshes all the value back to their default state*/
};

#endif