#include "ui_choicewindow.h"
#include "randListWindow.h"
#include "choicewindow.h"
#include <iostream>
#include <string>

ChoiceWindow::ChoiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoiceWindow)
{
    ui->setupUi(this);
    connect_Signals(); /*connects widgets for year*/
    connect_rating_Signals(); /*connects widgets for rating*/
    ChoiceWindow::setWindowTitle("RecommUi");
    this->books = new Collection();
    this->books->read_file();
}

ChoiceWindow::~ChoiceWindow()
{
    delete ui;
}

void ChoiceWindow::connect_Signals() /*links spin box and slider for year*/
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

void ChoiceWindow::new_Value_Changed(int newValue) /*makes the values for spinbox and slider equivalent for year*/
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

void ChoiceWindow::connect_rating_Signals() /*links spin box and dial for rating*/
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

void ChoiceWindow::new_Rating_Changed(int newRating) /*makes the values for spinbox and dial equivalent for rating*/
{
       disconnect_rating_Signals(); /*starts program off by the slider and spin box not being connected to each other*/
       ui->spinBox_rating->setValue(newRating); /*sets the value of the spin box to the user designated value*/
       ui->dial_rating->setValue(newRating); /*sets the value of the slider to the user designated value*/

       connect_rating_Signals();
}

void ChoiceWindow::on_pushButton_clicked() /*compiles user choices for generating random list of books that fit description*/
{
    this->year = ui->slider_year->value();
    this->rating = ui->dial_rating->value();

    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};

    if(this->genres_chosen.size() == 0) {
            for(int i = 0; i < 15; i++) {
                this->genres_chosen.push_back((i));
       }
    }
    /*holds the random list*/
    std::vector <Book> rand_gen = this->books->get_rand_list(this->genres_chosen, this->rating, this->year);
    /*displays random list*/
    print_books(rand_gen, genres, this->books);
}

/*signal handlers for genres*/
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

void ChoiceWindow::on_genre_fantasy_clicked()
{
    this->genres_chosen.push_back(2);
}

void ChoiceWindow::on_genre_non_fiction_clicked()
{
    this->genres_chosen.push_back(3);
}

void ChoiceWindow::on_genre_mystery_clicked()
{
    this->genres_chosen.push_back(4);
}

void ChoiceWindow::on_genre_classic_clicked()
{
    this->genres_chosen.push_back(5);
}

void ChoiceWindow::on_genre_manga_clicked()
{
    this->genres_chosen.push_back(6);
}

void ChoiceWindow::on_genre_sci_fi_clicked()
{
    this->genres_chosen.push_back(7);
}

void ChoiceWindow::on_genre_historical_clicked()
{
    this->genres_chosen.push_back(8);
}

void ChoiceWindow::on_genre_horror_clicked()
{
    this->genres_chosen.push_back(9);
}

void ChoiceWindow::on_genre_romance_clicked()
{
    this->genres_chosen.push_back(10);
}

void ChoiceWindow::on_genre_thriller_clicked()
{
    this->genres_chosen.push_back(11);
}

void ChoiceWindow::on_genre_cookbook_clicked()
{
    this->genres_chosen.push_back(12);
}

void ChoiceWindow::on_genre_suspense_clicked()
{
    this->genres_chosen.push_back(13);
}

void ChoiceWindow::on_genre_humor_clicked()
{
    this->genres_chosen.push_back(14);
}
