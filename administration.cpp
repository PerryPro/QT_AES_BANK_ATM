#include <QWidget>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QHeaderView>
#include <QTableWidget>
#include <QCompleter>
#include "include\administration.h"
#include "include\log_in.h"
#include "include\myaes.h"
#include "ui_administration.h"
#include <QTextCodec>
#include <QMessageBox>
int page_num=0;
int page_flag=0;
int page_all=0;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    page_num=0;
    page_flag=0;
    page_all=0;
    ui->setupUi(this);
   DectyptFile();
    ui->Check->resize(1500,500);
    ui->Check->setRowCount(10);
    ui->Check->setColumnCount(8);
    ui->Check->setAlternatingRowColors(true);
    ui->Check->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Check->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tempfile::tp1.open();
    tempfile::tp1.reset();
    QString all_content;
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    all_content = codec->toUnicode(buff);
    QStringList strList=all_content.split("\n");
    page_all=(strList.count()-1)/10;
    if(strList.count()<=10)
    {
        page_flag=1;
    }
    on_pushREFRESH_clicked();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushOK_clicked()
{
    //审核通过
    tempfile::tp1.open();
    tempfile::tp1.reset();
    int currentRow;
    currentRow = ui->Check->currentRow()+10*page_num;
    QString all_content;
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
     all_content = codec->toUnicode(buff);
    QStringList strList=all_content.split("\n");
    all_content="";
    for(int i=0; i<strList.count(); i++)
    {
        if(i==currentRow)
        {
            if(strList.at(i)!="")
            {
                for(int j=0;j<7;j++)
                {
                    all_content+=strList.at(i).section(" ",j,j)+' ';
                }

                all_content+="1";
                qDebug()<<all_content;

            }
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
     tempfile::tp1.remove();
     tempfile::tp1.open();
     tempfile::tp1.reset();
     tempfile::tp1.write(all_content.toLocal8Bit());
     QFile file("data.dat");
     file.open(QIODevice::WriteOnly|QIODevice::Text);
     file.write(all_content.toLocal8Bit());
     file.close();
     EncryptFile();
     on_pushREFRESH_clicked();
}

void Widget::on_pushNOK_clicked()
{
    //审核不通过
    tempfile::tp1.open();
    tempfile::tp1.reset();
    int currentRow;
    currentRow = ui->Check->currentRow()+10*page_num;
    QString all_content;
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
     all_content = codec->toUnicode(buff);
    QStringList strList=all_content.split("\n");
    all_content="";
    for(int i=0; i<strList.count(); i++)
    {
        if(i==currentRow)
        {
            if(strList.at(i)!="")
            {
                for(int j=0;j<7;j++)
                {
                    all_content+=strList.at(i).section(" ",j,j)+' ';
                }
                all_content+="-1";
                qDebug()<<all_content;
            }
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
     tempfile::tp1.remove();
     tempfile::tp1.open();
     tempfile::tp1.reset();
     tempfile::tp1.write(all_content.toLocal8Bit());
     QFile file("data.dat");
     file.open(QIODevice::WriteOnly|QIODevice::Text);
     file.write(all_content.toLocal8Bit());
     file.close();
     EncryptFile();
     on_pushREFRESH_clicked();
}

void Widget::on_pushEXIT_clicked()
{
    LOGI *p1=new LOGI;
    this->close();
    p1->show();
}

void Widget::on_pushCANCEL_clicked()
{
    //注销账户
    tempfile::tp1.open();
    tempfile::tp1.reset();
    int currentRow;
    currentRow = ui->Check->currentRow()+10*page_num;
    qDebug()<<currentRow;
    QString all_content;
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
     all_content = codec->toUnicode(buff);
    QStringList strList=all_content.split("\n");
    all_content="";
    for(int i=0; i<strList.count(); i++)
    {
        if(i==currentRow)
        {
            ;
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
     tempfile::tp1.remove();tempfile::tp1.open();tempfile::tp1.reset();
     tempfile::tp1.write(all_content.toLocal8Bit());
     QFile file("data.dat");
     file.open(QIODevice::WriteOnly|QIODevice::Text);
     file.write(all_content.toLocal8Bit());
     file.close();
     EncryptFile();
     on_pushREFRESH_clicked();
}

void Widget::on_pushREFRESH_clicked()
{
    //刷新
    ui->Check->clearContents();
    tempfile::tp1.open();
    tempfile::tp1.reset();
    QString all_content;
    QByteArray buff=tempfile::tp1.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    all_content = codec->toUnicode(buff);
    if(all_content=="")return;
    QStringList strList=all_content.split("\n");
    page_all=(strList.count()-1)/10;
    QString temp;
    int table_count=0;
    for(int i=10*page_num;i<strList.count();i++)
    {
        if(table_count<10)
        {
            if(strList.at(i)==""||strList.at(i)=="\n")continue;
            ui->Check->setItem(table_count,0,new QTableWidgetItem(strList.at(i).section(" ",0,0)));
            ui->Check->setItem(table_count,1,new QTableWidgetItem(strList.at(i).section(" ",1,1)));
            ui->Check->setItem(table_count,2,new QTableWidgetItem(strList.at(i).section(" ",2,2)));
            ui->Check->setItem(table_count,3,new QTableWidgetItem(strList.at(i).section(" ",3,3)));
            ui->Check->setItem(table_count,4,new QTableWidgetItem(strList.at(i).section(" ",4,4)));
            ui->Check->setItem(table_count,5,new QTableWidgetItem(strList.at(i).section(" ",5,5)));
            ui->Check->setItem(table_count,6,new QTableWidgetItem(strList.at(i).section(" ",6,6)));
            ui->Check->setItem(table_count,7,new QTableWidgetItem(strList.at(i).section(" ",7,7)));
            table_count++;
        }
        else
        {
            break;
        }

    }

}


void Widget::on_pushButton_clicked()
{
    if(page_num==0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("已是首页");
        msgBox.exec();
        return;
    }
    else
    {
        page_num--;
        on_pushREFRESH_clicked();
    }
}

void Widget::on_pushButton_2_clicked()
{
    if(page_num==page_all)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("已是尾页");
        msgBox.exec();
        return;
    }
    else
    {
        page_num++;
        on_pushREFRESH_clicked();
    }
}
