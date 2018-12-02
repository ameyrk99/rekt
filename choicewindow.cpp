#include "ui_choicewindow.h"
#include "randListWindow.h"
#include "choicewindow.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

ChoiceWindow::ChoiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoiceWindow)
{
    ui->setupUi(this);
    connect_Signals();
    connect_rating_Signals();
    ChoiceWindow::setWindowTitle("RecommUi");
    this->books = new Collection();
    this->books->read_file();
    this->books->read_user_file("userData.dat");
    ui->spinBox_year->setValue(0);
    ui->slider_year->setValue(0);
    ui->spinBox_rating->setValue(0);
    ui->dial_rating->setValue(0);
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

void ChoiceWindow::on_genre_thriller_clicked()
{
    this->genres_chosen.push_back(10);
}

void ChoiceWindow::on_genre_humor_clicked()
{
    this->genres_chosen.push_back(11);
}

void ChoiceWindow::on_genre_suspense_clicked()
{
    this->genres_chosen.push_back(12);
}

void ChoiceWindow::on_genre_romance_clicked()
{
    this->genres_chosen.push_back(13);
}

void ChoiceWindow::on_genre_cookbook_clicked()
{
    this->genres_chosen.push_back(14);
}

void ChoiceWindow::on_button_find_clicked()
{
    this->year = ui->slider_year->value();
    this->rating = ui->dial_rating->value();

    std::vector <std::string> genres = {"crime", "fiction", "fantasy", "non-fiction", "mystery", "clàssics", "mangá", "sci-fi", "historical", "horror", "thriller", "humor", "suspense", "romance", "cookbook"};

    if(this->genres_chosen.size() == 0) {
            for(int i = 0; i < 15; i++) {
                this->genres_chosen.push_back((i));
       }
    }

    std::vector <Book> rand_gen = this->books->get_rand_list(this->genres_chosen, this->rating, this->year);

    this->books->display_books(rand_gen, genres, this->books);
}

void ChoiceWindow::on_button_refresh_clicked()
{
    this->genres_chosen.clear();
    ui->genre_crime->setChecked(false);
    ui->genre_fantasy->setChecked(false);
    ui->genre_ficiton->setChecked(false);
    ui->genre_mystery->setChecked(false);
    ui->genre_non_fiction->setChecked(false);
    ui->genre_classic->setChecked(false);
    ui->genre_historical->setChecked(false);
    ui->genre_horror->setChecked(false);
    ui->genre_manga->setChecked(false);
    ui->genre_sci_fi->setChecked(false);
    ui->genre_cookbook->setChecked(false);
    ui->genre_humor->setChecked(false);
    ui->genre_romance->setChecked(false);
    ui->genre_suspense->setChecked(false);
    ui->genre_thriller->setChecked(false);

    ui->spinBox_year->setValue(0);
    ui->slider_year->setValue(0);
    ui->spinBox_rating->setValue(0);
    ui->dial_rating->setValue(0);
}

void ChoiceWindow::on_button_exit_clicked()
{
    this->close();
}

void ChoiceWindow::on_button_userlist_clicked()
{
    books_added = books->get_list();
    id_nums = books->get_user_list();

    QWidget* window=new QWidget;
    window->resize(600, 500);
    window->setWindowTitle("RecommUi: To Read List");
    QVBoxLayout* all_info=new QVBoxLayout;
    QHBoxLayout* for_buttons=new QHBoxLayout;
    userListView = new QListView;

    model = new QStringListModel;
    QStringList list;

    QString book_chosen1;
    std::string book_chosen;

    for(int i=0;i<id_nums.size();i++)
    {
        book_chosen = books_added[id_nums[i]].title + " by " + books_added[id_nums[i]].author+" ("+std::to_string(books_added[id_nums[i]].year)+ ")";
        book_chosen1=QString::fromStdString(book_chosen);
        list << book_chosen1;
    }

    model->setStringList(list);
    userListView->setModel(model);
    userListView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

    QPushButton *delete_book=new QPushButton("  Remove Book");
    QObject::connect(delete_book, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()));

    QPushButton *button_info=new QPushButton("  Info");
    QObject::connect(button_info, SIGNAL(clicked()), this, SLOT(on_info_button_clicked()));

    QPushButton *go_back=new QPushButton("  Back ");
    QObject::connect(go_back, SIGNAL(clicked()), window, SLOT(close()));


    for_buttons->addWidget(delete_book);
    for_buttons->addWidget(button_info);
    for_buttons->addWidget(go_back);
    all_info->addWidget(userListView);
    all_info->addLayout(for_buttons);
    window->setLayout(all_info);
    window->show();
}

void ChoiceWindow::on_deleteButton_clicked()
{
    int row = userListView->currentIndex().row();
    model->removeRows(row, 1);
    Book b = books->get_book(books->user_list[row]);
    this->books->user_list.erase(this->books->user_list.begin() + row);
    this->books->output_file("userData.dat");
}

void::ChoiceWindow::on_info_button_clicked() {
    Book b = books->get_book(books->user_list[userListView->currentIndex().row()]);
    int id = b.id;

    QWidget* window=new QWidget;
    QLabel* title=new QLabel(QString::fromStdString(books->get_book(id).title));
    QFont titleFont("", 16, QFont::Bold);
    title->setFont(titleFont);
    title->setWordWrap(true);
    QLabel* author=new QLabel(QString::fromStdString(books->get_book(id).author));
    QFont authorFont("", 14);
    author->setFont(authorFont);
    QLabel* about=new QLabel(QString::fromStdString(books->get_book(id).about));
    QLabel* year=new QLabel(QString::fromStdString(std::to_string(books->get_book(id).year)));

    std::ostringstream out;
    out.precision(2);
    out << std::fixed << books->get_book(id).rating;
    QLabel* rating=new QLabel(QString::fromStdString(out.str()));
    QString num_jpg=QString::number(id);
    QPixmap image("images/book_"+num_jpg+".jpg");
    QLabel* picture=new QLabel();
    picture->setPixmap(image);
    about->setWordWrap(true);

    QPushButton *exit=new QPushButton("  Exit");
    QObject::connect(exit, SIGNAL(clicked()), window, SLOT(close()));

    QSignalMapper *mapper2=new QSignalMapper();
    QPushButton *buybutton=new QPushButton("  Buy Book");
    QObject::connect(buybutton, SIGNAL(clicked()), mapper2, SLOT(map()));
    mapper2->setMapping(buybutton, id);
    QObject::connect(mapper2, SIGNAL(mapped(int)), SLOT(user_list_buy_book(int)));


    //organizes info
    QVBoxLayout *all_info = new QVBoxLayout;
    QHBoxLayout *button_bar = new QHBoxLayout;
    QHBoxLayout *info_tab = new QHBoxLayout;
    QVBoxLayout *left_panel = new QVBoxLayout;
    QVBoxLayout *right_panel = new QVBoxLayout;
    QVBoxLayout* top_info=new QVBoxLayout;
    QHBoxLayout* bottom_info=new QHBoxLayout;
    top_info->addWidget(title);
    top_info->addWidget(author);
    top_info->addWidget(year);
    top_info->addWidget(rating);
    bottom_info->addWidget(about);

    left_panel->addLayout(top_info);
    left_panel->addLayout(bottom_info);

    left_panel->addSpacing(300);

    right_panel->addWidget(picture);

    info_tab->addLayout(left_panel);
    info_tab->addLayout(right_panel);

    button_bar->addWidget(buybutton);
    button_bar->addWidget(exit);

    all_info->addLayout(info_tab);
    all_info->addLayout(button_bar);

    window->setLayout(all_info);
    window->show();
}

void ChoiceWindow::user_list_buy_book(int idn) {
    QString link = QString::fromStdString(this->books->get_book(idn).link);
    QDesktopServices::openUrl(QUrl(link));
}
