#include "include\change_pw.h"
#include "include\menu.h"
#include "include\myaes.h"
#include "ui_change_pw.h"
#include <QFile>
#include <QLineEdit>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>

ch::ch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ch)
{
    ui->setupUi(this);
    ui->newone->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->resured->setEchoMode(QLineEdit::Password);
}

ch::~ch()
{
    delete ui;
}

void ch::on_pushButton_clicked(bool checked)
{
    DectyptFile();
    tempfile::tp1.open();tempfile::tp1.reset();
    QFile file("data.dat");
    QString pw=ui->newone->text();                        //获取密码
    QString re_pw=ui->resured->text();
    qDebug()<<username;
        if(pw.isEmpty()||re_pw.isEmpty())
        {ui->reminder->setText("请输入两次密码！");}
        else
        {
               if(pw!=re_pw)
                {
                ui->reminder->setText("两次密码不一致！");
                }
                else if(pw==re_pw)//成功修改
                {
                    QString all_content;
                    file.open(QIODevice::ReadOnly|QIODevice::Text);
                    QByteArray buff=tempfile::tp1.readAll();
                    QTextCodec *codec = QTextCodec::codecForName("GB2312");
                    all_content = codec->toUnicode(buff);
                    QStringList strList=all_content.split("\n");
                    all_content="";
                    for(int i=0; i<strList.count(); i++)
                    {
                        if(strList.at(i).section(" ",0,0)==username)
                        {
                            all_content+=username+' '+pw+' '+strList.at(i).section(" ",2,7);

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
                    file.close();
                    tempfile::tp1.remove();
                    tempfile::tp1.open();
                    tempfile::tp1.reset();
                    tempfile::tp1.write(all_content.toLocal8Bit());
                    file.open(QIODevice::WriteOnly|QIODevice::Text);
                    file.write(all_content.toLocal8Bit());
                    file.close();
                    EncryptFile();
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("修改密码");
                    msgBox.setText("密码修改成功！请牢记新密码");
                    msgBox.exec();
                    on_pushButton_2_clicked();

                }
            }
       }

bool ch::Qfilejudg(QString username)                 //判断数据库中是否有相同的用户
{
    DectyptFile();
    tempfile::tp1.open();tempfile::tp1.reset();
    QFile file("data.dat");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QString temp;
    bool judge=0;
    while(!tempfile::tp1.atEnd())
    {
        QByteArray buff=tempfile::tp1.readLine();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        temp = codec->toUnicode(buff);
        if(temp.section(" ",0,0)==username)
        {
            judge=1;
            break;
        }

    }
    file.close();
    return judge;
}
void ch::SendData(QString data)
{
    this->username=data;
}
void ch::on_pushButton_2_clicked()
{
    menu *p1=new menu;
    p1->SendData(this->username);
    this->close();
    p1->show();
}
