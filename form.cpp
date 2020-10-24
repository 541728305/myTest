#include "form.h"
#include "ui_form.h"
#include <QDebug>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
     qDebug()<<"form线程号"<<this->thread();
}

Form::~Form()
{
    delete ui;
}
