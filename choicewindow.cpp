#include "choicewindow.h"
#include "ui_choicewindow.h"
#include <iostream>
#include <string>

ChoiceWindow::ChoiceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoiceWindow)
{
    ui->setupUi(this);
    connect_Signals();
    connect_rating_Signals();
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
