#include "include\sign_up.h"
#include "include\myaes.h"
#include "ui_sign_up.h"
#include <QTextCodec>
#include <QDebug>
REGI::REGI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::REGI)
{
    ui->setupUi(this);
}

REGI::~REGI()
{
    delete ui;
}

void REGI::on_pushButton_clicked(bool checked)
{
    ui->label_9->setText("");
    this->usern= ui->USN->text();
    this->passw=ui->PWD->text();
    this->name=ui->NM->text();
    this->id=ui->ID->text();
    this->sex=ui->SEX->currentText();
    this->phone=ui->PHO->text();
    if(this->ui->ID->text()==""||this->ui->USN->text()==""||this->ui->PHO->text()==""||this->ui->NM->text()==""||this->ui->PWD->text()=="")
    {
        ui->label_9->setText("请填写所有字段");
        return;
    }
    if(QfileJudeg(this->usern))
    {
        ui->label_9->setText("用户已存在，注册失败");
    }
    else
    {
        DectyptFile();
        tempfile::tp1.open();tempfile::tp1.reset();
        QFile file("data.dat");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString alldata;
        QByteArray buff=tempfile::tp1.readAll();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        alldata = codec->toUnicode(buff);
        file.close();
        alldata+=usern.toUtf8()+" "+passw.toUtf8()+" "+"0.00"+" "+name.toUtf8()+" "+id.toUtf8()+" "+sex.toUtf8()+" "+phone.toUtf8()+" 0"+"\n";
        qDebug()<<alldata.toLocal8Bit();
        tempfile::tp1.remove();
        tempfile::tp1.open();
        tempfile::tp1.reset();
        tempfile::tp1.write(alldata.toLocal8Bit());
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        file.write(alldata.toLocal8Bit());
        file.close();
        EncryptFile();
        ui->label_9->setText("注册成功，请等待核审");
        ui->ID->clear();
        ui->NM->clear();
        ui->PHO->clear();
        ui->PWD->clear();
        ui->USN->clear();
    }
}
bool REGI::QfileJudeg(QString name)
{

    tempfile::tp1.open();tempfile::tp1.reset();
    QFile file("data.dat");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString temp;
    bool judge=0;
    while(!tempfile::tp1.atEnd())
    {
        QByteArray buff=tempfile::tp1.readLine();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        temp = codec->toUnicode(buff);
        if(temp.section(" ",0,0)==name)
        {
            judge=1;
            break;
        }

    }
    file.close();

    return judge;
}
