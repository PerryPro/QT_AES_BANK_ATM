#ifndef REGI_H
#define REGI_H

#endif // REGI_H
#include <QWidget>
#include<QFile>
#include<QString>
#include<QTextStream>

namespace Ui {
class REGI;
}

class REGI : public QWidget
{
    Q_OBJECT

public:
    explicit REGI(QWidget *parent = nullptr);
    bool QfileJudeg(QString name);
    bool isdigital(QString password);
    QString usern;
    QString passw;
    int mo;
    QString name;
    QString id;
    QString sex;
    QString phone;
    ~REGI();

private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::REGI *ui;
};
