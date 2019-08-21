#include "include\save_withdraw.h"
#include "ui_save_withdraw.h"
#include "include\menu.h"
#include "include\myaes.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
Save_Withdraw::Save_Withdraw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Save_Withdraw)
{
    ui->setupUi(this);
}

Save_Withdraw::~Save_Withdraw()
{
    delete ui;
}


void Save_Withdraw::on_Button_search_clicked()//查询余额
{
    DectyptFile();
    QString a = ui->user->text();//读入用户名
    tempfile::tp1.open();tempfile::tp1.reset();
    QFile file("data.dat");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(a == "")
    {
        ui->label_output->setText("未查询到账号信息");
        return;
    }
    QString temp;
    while(!tempfile::tp1.atEnd())
    {
        QByteArray buff=tempfile::tp1.readLine();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        temp = codec->toUnicode(buff);
        if(temp.section(" ",0,0) == a)
        {
            QString t1 = temp.section(" ",2,2);
            t1 = t1.trimmed(); //去除空字符
            ui->label_output->setText(t1);

            return;
        }
    }
}


void Save_Withdraw::on_Button_in_clicked()//存款
{
    DectyptFile();
    tempfile::tp1.open();tempfile::tp1.reset();
    QString money = ui->textEdit->toPlainText().toUtf8();//读取数额
    QString a = ui->user->text();//读入用户名
    if(money == "")
    {
        ui->feedback->setText("请输入金额！");
        return;
    }
    QFile file("data.dat");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp;
    QString user;
    double origin_money = 0;
    while(!tempfile::tp1.atEnd())
    {
        QByteArray buff=tempfile::tp1.readLine();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        temp = codec->toUnicode(buff);
        if(temp.section(" ",0,0)==a)
        {
            user = temp;
            QString t1 = temp.section(" ",2,2);
            t1 = t1.trimmed();
            origin_money=t1.toDouble();
        }
    }
    double moneynum = money.toDouble();
    origin_money += moneynum;
    file.close();
    user=user.section(" ",0,1)+" "+QString::number(origin_money,'f',2)+" "+user.section(" ",3,7); //修改之前保存的源账户那行内容(末尾含回车)
    qDebug()<<user;
    QString all_content;
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    tempfile::tp1.open();tempfile::tp1.reset();
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
     all_content = codec->toUnicode(buff);
    QStringList strList=all_content.split("\n");
    all_content="";
    for(int i=0; i<strList.count(); i++)
    {
        if(strList.at(i).section(" ",0,0)==user.section(" ",0,0))
        {
            all_content+=user;
        }
        else
        {
            all_content+=strList.at(i);
            if(i!=strList.count()-1)
             {
                 all_content+="\n";
             }
        }


    }
    file.close();
    tempfile::tp1.remove();
    tempfile::tp1.open();
    tempfile::tp1.reset();
    tempfile::tp1.write(all_content.toLocal8Bit()); //写回文件
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    file.write(all_content.toLocal8Bit());
    file.close();
    EncryptFile();
    ui->feedback->setText("存款成功！");
    ui->textEdit->setText("");
}


void Save_Withdraw::on_Button_out_clicked()//取款
{
    DectyptFile();
    tempfile::tp1.open();tempfile::tp1.reset();
    QString money = ui->textEdit->toPlainText().toUtf8();
    QString a = ui->user->text();
    if(money == "")
    {
        ui->feedback->setText("请输入金额！");
        return;
    }
    QFile file("data.dat");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp;
    QString user;
    double origin_money = 0;
    while(!tempfile::tp1.atEnd())
    {
        QByteArray buff=tempfile::tp1.readLine();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        temp = codec->toUnicode(buff);
        if(temp.section(" ",0,0)==a)
        {
            user = temp;
            QString t1 = temp.section(" ",2,2);
            t1 = t1.trimmed();
            origin_money=t1.toDouble();
        }
    }
    double moneynum = money.toDouble();
    if(moneynum > origin_money)
    {
        ui->feedback->setText("余额不足！");
        ui->textEdit->setText("");
        return;
    }
    else origin_money -= moneynum;
    file.close();
    user=user.section(" ",0,1)+" "+QString::number(origin_money,'f',2)+" "+user.section(" ",3,7);
    QString all_content;
    tempfile::tp1.open();tempfile::tp1.reset();
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
     all_content = codec->toUnicode(buff);
    QStringList strList=all_content.split("\n");
    all_content="";
    for(int i=0; i<strList.count(); i++)
    {
        if(strList.at(i).section(" ",0,0)==user.section(" ",0,0))
        {
            all_content+=user;
        }
        else
        {
            all_content+=strList.at(i);
            if(i!=strList.count()-1)
             {
                 all_content+="\n";
             }
        }

    }
    file.close();
    tempfile::tp1.remove();
    tempfile::tp1.open();
    tempfile::tp1.reset();
    tempfile::tp1.write(all_content.toLocal8Bit());
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    file.write(all_content.toLocal8Bit());
    file.close();
    EncryptFile();
    ui->feedback->setText("取款成功！");
    ui->textEdit->setText("");
}
void Save_Withdraw::SendData(QString data)
{
    ui->user->setText(data);
}

void Save_Withdraw::on_pushButton_clicked()
{
    menu *p1=new menu;
    p1->SendData(ui->user->text());
    this->close();
    p1->show();
}
