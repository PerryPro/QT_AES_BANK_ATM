#include "include\menu.h"
#include "ui_menu.h"
#include "include\change_pw.h"
#include "include\save_withdraw.h"
#include "include\log_in.h"
#include "include\transfer.h"
#include <QDebug>
menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}
void menu::SendData(QString data)
{
    ui->user->setText(data);
}

void menu::on_pushButton_clicked()
{
    Save_Withdraw *p1=new Save_Withdraw;
    p1->SendData(ui->user->text());
    this->close();
    p1->show();
}

void menu::on_pushButton_2_clicked()
{
    ch* p1=new ch;
    qDebug()<<1<<this->ui->user->text();
    p1->SendData(this->ui->user->text());
    this->close();
    p1->show();
}

void menu::on_pushButton_3_clicked()
{
    LOGI *p1=new LOGI;
    this->close();
    p1->show();
}

void menu::on_pushButton_4_clicked()
{
    Transfer *p=new Transfer;
    p->SendData(this->ui->user->text());
    this->close();
    p->show();
}
