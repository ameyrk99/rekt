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
    std::vector <int> genres_chosen;
    int year;
    int rating;

private:
    Ui::ChoiceWindow *ui;
    void connect_Signals(); /*connects the value of the slider to the scroll box*/
    void disconnect_Signals(); /*disconnects the value of the slider to the scroll box*/
    void connect_rating_Signals(); /*connects how many stars the user wants to find a book with to a dial widget*/
    void disconnect_rating_Signals(); /*disconnects how many stars the user wants to find a book with to a dial widget*/

private slots: /*adds a new slot that connects the two values into one slot*/
    void new_Value_Changed(int newValue);
    void new_Rating_Changed(int newRating);
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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_genre_fantasy_clicked();
};

#endif // CHOICEWINDOW_H
