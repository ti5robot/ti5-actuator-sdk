#include "dialognotice.h"
#include "ui_dialognotice.h"
DialogNotice::DialogNotice(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNotice)
{
    ui->setupUi(this);
    ui->label->setText(text);
    this->setWindowTitle("提示");
}
DialogNotice::~DialogNotice()
{
    delete ui;
}
