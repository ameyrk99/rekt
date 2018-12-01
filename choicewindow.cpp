#include "userwindow.h"
#include "ui_choicewindow.h"
#include "randListWindow.h"
<<<<<<< HEAD
#include "userwindow.h"
=======
#include "choicewindow.h"
>>>>>>> 27d234868f38afa613bcf74c3f4f8428d367279c
#include <iostream>
#include <string>

ChoiceWindow::ChoiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoiceWindow)
{
    ui->setupUi(this);
    connect_Signals();
    connect_rating_Signals();
<<<<<<< HEAD

    this->books=new Collection();
//    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};
    books->read_file();
    books->read_user_file("userData.dat");
=======
    this->books = new Collection();
>>>>>>> 27d234868f38afa613bcf74c3f4f8428d367279c
}

ChoiceWindow::~ChoiceWindow()
{
    delete ui;
}

void ChoiceWindow::connect_Signals()
{
    connect(ui->spinBox_year,       /*connects the spin box value to the user designated value*/
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ChoiceWindow::new_Value_Changed);
    connect(ui->slider_year,        /*connects the slider box value to the user designated value*/
            &QSlider::valueChanged,this,
            &ChoiceWindow::new_Value_Changed);
}

void ChoiceWindow::disconnect_Signals()
{
    disconnect(ui->spinBox_year,       /*connects the spin box value to the user designated value*/
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ChoiceWindow::new_Value_Changed);
    disconnect(ui->slider_year,        /*connects the slider value to the user designated value*/
            &QSlider::valueChanged,this,
               &ChoiceWindow::new_Value_Changed);
}

void ChoiceWindow::new_Value_Changed(int newValue)
{
       disconnect_Signals(); /*starts program off by the slider and spin box not being connected to each other*/
       ui->spinBox_year->setValue(newValue); /*sets the value of the spin box to the user designated value*/
       ui->slider_year->setValue(newValue); /*sets the value of the slider to the user designated value*/

       if(newValue < 0) /*checks if the year chosen is in the BCE era*/
       {
           ui->spinBox_year->setValue(newValue*-1);
           ui->spinBox_year->setSuffix(" BCE");
       }

       else /*checks if the year chosen is in the CE era*/
       {
           ui->spinBox_year->setSuffix("");
       }

       connect_Signals();
}

void ChoiceWindow::connect_rating_Signals()
{
    connect(ui->spinBox_rating,       /*connects the spin box value to the user designated value*/
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ChoiceWindow::new_Rating_Changed);
    connect(ui->dial_rating,        /*connects the slider box value to the user designated value*/
            &QDial::valueChanged,this,
            &ChoiceWindow::new_Rating_Changed);
}

void ChoiceWindow::disconnect_rating_Signals()
{
    disconnect(ui->spinBox_rating,       /*connects the spin box value to the user designated value*/
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ChoiceWindow::new_Rating_Changed);
    disconnect(ui->dial_rating,        /*connects the slider box value to the user designated value*/
            &QDial::valueChanged,this,
            &ChoiceWindow::new_Rating_Changed);
}

void ChoiceWindow::new_Rating_Changed(int newRating)
{
       disconnect_rating_Signals(); /*starts program off by the slider and spin box not being connected to each other*/
       ui->spinBox_rating->setValue(newRating); /*sets the value of the spin box to the user designated value*/
       ui->dial_rating->setValue(newRating); /*sets the value of the slider to the user designated value*/

       connect_rating_Signals();
}

void ChoiceWindow::on_pushButton_clicked()
{
    this->year = ui->slider_year->value();
    this->rating = ui->dial_rating->value();

//    Collection *books=new Collection();
    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};
    this->books->read_file();
    this->books->read_user_file("userData.dat");

    std::vector <Book> rand_gen = this->books->get_rand_list(this->genres_chosen, this->rating, this->year);

    print_books(rand_gen, genres, this->books);

    this->books->output_file("userData.dat");
}

void ChoiceWindow::on_pushButton_3_clicked()
{
    UserWindow u(books, this);
    u.show();
}

void ChoiceWindow::on_pushButton_2_clicked()
{
    this->close();
}

void ChoiceWindow::on_genre_crime_clicked()
{
    this->genres_chosen.push_back(0);
}

void ChoiceWindow::on_genre_ficiton_clicked()
{
    this->genres_chosen.push_back(1);
}

void ChoiceWindow::on_genre_non_fiction_clicked()
{
    this->genres_chosen.push_back(2);
}

void ChoiceWindow::on_genre_mystery_clicked()
{
    this->genres_chosen.push_back(3);
}

void ChoiceWindow::on_genre_classic_clicked()
{
    this->genres_chosen.push_back(4);
}

void ChoiceWindow::on_genre_manga_clicked()
{
    this->genres_chosen.push_back(5);
}

void ChoiceWindow::on_genre_sci_fi_clicked()
{
    this->genres_chosen.push_back(6);
}

void ChoiceWindow::on_genre_historical_clicked()
{
    this->genres_chosen.push_back(7);
}

void ChoiceWindow::on_genre_horror_clicked()
{
    this->genres_chosen.push_back(8);
}

void ChoiceWindow::on_genre_romance_clicked()
{
    this->genres_chosen.push_back(9);
}

void ChoiceWindow::on_genre_thriller_clicked()
{
    this->genres_chosen.push_back(10);
}

void ChoiceWindow::on_genre_cookbook_clicked()
{
    this->genres_chosen.push_back(11);
}

void ChoiceWindow::on_genre_suspense_clicked()
{
    this->genres_chosen.push_back(12);
}

void ChoiceWindow::on_genre_humor_clicked()
{
    this->genres_chosen.push_back(13);
}
<<<<<<< HEAD

void ChoiceWindow::on_pushButton_clicked()
{
    if(this->genres_chosen.size() == 0) {
        for(int i = 0; i < 14; i++) {
            this->genres_chosen.push_back((i));
        }
    }

    this->year = ui->slider_year->value();
    this->rating = ui->dial_rating->value();

    Collection *books=new Collection();
    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};
    books->read_file();
    books->read_user_file("userData.dat");

    std::vector <Book> rand_gen = books->get_rand_list(this->genres_chosen, this->rating, this->year);

    print_books(rand_gen, genres, books);

    books->output_file("userData.dat");
}

void ChoiceWindow::on_pushButton_3_clicked()
{
    UserWindow u(books, this);
    u.show();
}

void ChoiceWindow::on_pushButton_2_clicked()
{
    this->close();
}
=======
>>>>>>> 27d234868f38afa613bcf74c3f4f8428d367279c
