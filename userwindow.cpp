#include "userwindow.h"
#include "ui_userwindow.h"

#include <QtCore>
#include <QStringList>
#include <QtGui>
#include <vector>
#include <iostream>
#include <string>

UserWindow::UserWindow(Collection *books, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);

    model = new QStringListModel(this);
    QStringList list;

    this->books_stored= books->get_list();
    this->id_list = books->get_user_list();
    QFont f("Avenir", 14, QFont::Cursive);

    QString book_chosen1;
    std::string book_chosen;

    for(int i = 0; i < id_list.size(); i++)
    {
        book_chosen = books_stored[id_list[i]].title + " by " + books_stored[id_list[i]].author+" ("+std::to_string(books_stored[id_list[i]].year)+ ")";
        book_chosen1=QString::fromStdString(book_chosen);
        list << book_chosen1;
        list.join("\n");
    }

    model->setStringList(list);
    ui->userlistView->setModel(model);
    ui->userlistView->setFont(f);
    ui->userlistcomboBox->setModel(model);

    ui->detailsButton->setFont(f);
    ui->deleteButton->setFont(f);
    ui->userlistcomboBox->setFont(f);

    ui->userlistView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_detailsButton_clicked()
{

}

void UserWindow::on_deleteButton_clicked()
{
    model->removeRows(ui->userlistView->currentIndex().row(), 1);
}
