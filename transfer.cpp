#include "include\transfer.h"
#include "ui_transfer.h"
#include "include\menu.h"
#include "include\myaes.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
Transfer::Transfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transfer)
{
    ui->setupUi(this);
}

Transfer::~Transfer()
{
    delete ui;
}

void Transfer::SendData(QString data)
{
    ui->label_2->setText(data);
}

void Transfer::on_pushButton_clicked()
{
    tempfile::tp1.open();
    tempfile::tp1.reset();
    QString origin_user=ui->label_2->text();
    QString des_user=ui->lineEdit->text();
    QString trans_money1=ui->lineEdit_2->text();
    if(trans_money1=="")
    {
        ui->label_6->setText("错误！请输入转账金额");
        return;
    }
    double origin_money=0;
    double des_money=0;
    double trans_money=trans_money1.toDouble();
    int des_flag=0;
    int origin_flag=0;
    QString all_content;
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    all_content = codec->toUnicode(buff);
    QString all_content_backup=all_content;
    QStringList strList=all_content.split("\n");
    all_content="";
    for(int i=0; i<strList.count(); i++)
    {
        if(strList.at(i).section(" ",0,0)==des_user)
        {
            des_flag=1;
            des_money=strList.at(i).section(" ",2,2).trimmed().toDouble();
            des_money+=trans_money;
            all_content+=strList.at(i).section(" ",0,1)+" "+QString::number(des_money,'f',2)+" "+strList.at(i).section(" ",3,7);
        }
        else if(strList.at(i).section(" ",0,0)==origin_user)
        {
            QString temp=strList.at(i).section(" ",2,2);
            temp=temp.trimmed();
            origin_money=temp.toDouble();
            if(origin_money<trans_money)
            {
                ui->label_6->setText("错误！源账户余额不足");
                return;
            }
            origin_flag=1;
            origin_money-=trans_money;
            all_content+=strList.at(i).section(" ",0,1)+" "+QString::number(origin_money,'f',2)+" "+strList.at(i).section(" ",3,7);
        }

        else
        {
            all_content+=strList.at(i);
        }
        if(i!=strList.count()-1)
        {
            all_content+="\n";
        }

    }
    if(des_flag==0)
    {
        ui->label_6->setText("错误！目标账户不存在");
        return;
    }
    else if(des_flag==1&&origin_flag==1)
    {
        QFile file("data.dat");
        tempfile::tp1.remove();
        tempfile::tp1.open();
        tempfile::tp1.reset();
        tempfile::tp1.write(all_content.toLocal8Bit());
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        file.write(all_content.toLocal8Bit());
        file.close();
        EncryptFile();
        ui->label_6->setText("转账成功！");
        return;
    }
}

void Transfer::on_pushButton_2_clicked()
{
    menu *p1=new menu;
    p1->SendData(ui->label_2->text());
    this->close();
    p1->show();
}
