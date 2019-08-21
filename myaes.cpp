#include "include\myaes.h"
#include "aes.h"
#include "qaeswrap.h"
#include <QFile>
#include <qDebug>
#include <QString>
#include <QTextCodec>
QTemporaryFile tempfile::tp1;
void EncryptFile()
{
            QAesWrap aesobj("@BankSystem;/","bks",QAesWrap::AES_256); //aes密码为【@BankSystem;/】
            QFile file("data.dat");QFile file2("data.dat");
            file.open(QIODevice::ReadOnly|QIODevice::Text);
            QByteArray buff=file.readAll();
            QTextCodec *codec = QTextCodec::codecForName("GB2312");
            QString ReadyText = codec->toUnicode(buff);
            //qDebug()<<ReadyText;
            QByteArray mdata = aesobj.encrypt(buff,QAesWrap::AES_CTR);
            //qDebug()<<mdata;
            file.close();
            file2.open(QIODevice::WriteOnly|QIODevice::Text);
            file2.write(mdata.toBase64());
            file2.close();
}
void DectyptFile()
{
    if(QAesWrap::AesJudge==1)
    {
        QAesWrap aesobj("@BankSystem;/","bks",QAesWrap::AES_256); //aes密码为【@BankSystem;/】
        QFile file2("data.dat");
        QByteArray mdata;
        QByteArray temp;
        mdata="";
        file2.open(QIODevice::ReadOnly|QIODevice::Text);
        mdata=file2.readAll();
        file2.close();
        mdata=QByteArray::fromBase64(mdata);
        aesobj.decrypt(mdata,temp,QAesWrap::AES_CTR);
        tempfile::tp1.open();
        QTextCodec *codec = QTextCodec::codecForName("GB2312");
        QString ReadyText = codec->toUnicode(temp);
        tempfile::tp1.remove();
        tempfile::tp1.open();
        tempfile::tp1.reset();
        tempfile::tp1.write(ReadyText.toLocal8Bit());
        tempfile::tp1.reset();
        QAesWrap::AesJudge=0;
    }
}
