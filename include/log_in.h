#ifndef LOGI_H
#define LOGI_H

#include <QWidget>
#include<QFile>
#include<QString>
#include<QTextStream>
namespace Ui {
class LOGI;
}

class LOGI : public QWidget
{
    Q_OBJECT

public:
    explicit LOGI(QWidget *parent = nullptr);
    bool QfileJudeg(QString name);
    bool isdigital(QString password);
    void ToRegi();
    QString usern;
    QString passw;
    ~LOGI();

private slots:

    void on_USN_returnPressed();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_PSW_returnPressed();

private:
    Ui::LOGI *ui;
};

#endif // LOGI_H
