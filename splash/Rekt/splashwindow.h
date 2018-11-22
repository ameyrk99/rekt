#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

#include <QMainWindow>

namespace Ui {
class Splashwindow;
}

class Splashwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Splashwindow(QWidget *parent = nullptr);
    ~Splashwindow();

private:
    Ui::Splashwindow *ui;
};

#endif // SPLASHWINDOW_H
