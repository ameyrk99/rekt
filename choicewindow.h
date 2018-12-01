#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>
#include <QStyledItemDelegate>
#include <QWidget>
#include <QtWidgets>
#include <QMetaType>
#include <QPointF>
#include <QVector>

namespace Ui {
class ChoiceWindow;
}

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChoiceWindow(QWidget *parent = nullptr);
    ~ChoiceWindow();

private:
    Ui::ChoiceWindow *ui;
    void connect_Signals(); /*connects the value of the slider to the scroll box*/
    void disconnect_Signals(); /*disconnects the value of the slider to the scroll box*/
    void connect_rating_Signals(); /*connects how many stars the user wants to find a book with to a dial widget*/
    void disconnect_rating_Signals(); /*disconnects how many stars the user wants to find a book with to a dial widget*/

private slots: /*adds a new slot that connects the two values into one slot*/
    void new_Value_Changed(int newValue);
    void new_Rating_Changed(int newRating);
};

#endif // CHOICEWINDOW_H
