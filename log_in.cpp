#include "include\log_in.h"
#include "include\sign_up.h"
#include "include\myaes.h"
#include "include\administration.h"
#include "include\menu.h"
#include "ui_log_in.h"
#include <QTextCodec>
#include <QDebug>
#include "aes.h"
#include "qaeswrap.h"
LOGI::LOGI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LOGI)
{
    ui->setupUi(this);
    ui->PSW->setEchoMode(QLineEdit::Password);
    DectyptFile();
}

LOGI::~LOGI()
{
    delete ui;
}

bool LOGI::QfileJudeg(QString name)
{
    DectyptFile();
    tempfile::tp1.open();
    tempfile::tp1.reset();
    QString temp;
    bool judge=0;
    tempfile::tp1.open();
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
    return judge;
}

void LOGI::on_USN_returnPressed()
{
    on_pushButton_clicked();
}

void LOGI::on_pushButton_clicked()
{

    ui->label_5->setText(" ");
    ui->label_5->setText(" ");
    QFile file("data.dat");
    this->usern= ui->USN->text();
    this->passw=ui->PSW->text();
    if(usern=="root"&&passw=="123456") //root界面
    {
        Widget *p1=new Widget;
        this->close();
        p1->show();
        return;
    }
    if(QfileJudeg(LOGI::usern))
    {
        tempfile::tp1.open();
         tempfile::tp1.reset();
         QString temp;
         bool judge=0;
         while(!tempfile::tp1.atEnd())
         {
             QByteArray buff=tempfile::tp1.readLine();
             QTextCodec *codec = QTextCodec::codecForName("GB2312");
             temp = codec->toUnicode(buff);
             if(temp.section(" ",0,0)==this->usern)
             {
                 if(temp.section(" ",1,1)==this->passw)
                     judge=1;
                 if(temp.section(" ",7,7)=="0\n")
                 {
                      ui->label_5->setText("用户还未核审，请等待核审");
                      return;
                 }
                 if(temp.section(" ",7,7)=="-1\n")
                 {
                      ui->label_5->setText("用户核审未通过，不予登录");
                      return;
                 }
                 break;
             }
         }
         if(judge)
         {
             menu *m1=new menu;
             m1->SendData(ui->USN->text());
             this->close();
             m1->show();
         }
         else
         {
            ui->label_5->setText("密码错误");
         }
     }
     else
     {
         ui->label_5->setText("用户不存在");
     }

}

void LOGI::on_pushButton_2_clicked()
{
    REGI *r=new REGI;
    r->show();
}

void LOGI::on_PSW_returnPressed()
{
    on_pushButton_clicked();
}
