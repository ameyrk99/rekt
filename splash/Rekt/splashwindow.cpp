#include "splashwindow.h"
#include "ui_splashwindow.h"

Splashwindow::Splashwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Splashwindow)
{
    ui->setupUi(this);
}

Splashwindow::~Splashwindow()
{
    delete ui;
}
