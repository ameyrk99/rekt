#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include "randListWindow.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit UserWindow(Collection *books, QWidget *parent = nullptr);
    ~UserWindow();
    std::vector<Book> books_stored;
    std::vector<int> id_list;

private:
    Ui::UserWindow *ui;
    QStringListModel *model;

private slots:
    void on_detailsButton_clicked();
    void on_deleteButton_clicked();
};

#endif // USERWINDOW_H
