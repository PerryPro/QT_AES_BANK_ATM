#ifndef CH_H
#define CH_H

#include <QString>
#include <QWidget>
#include<QTextStream>
namespace Ui {
class ch;
}

class ch : public QWidget
{
    Q_OBJECT

public:
    explicit ch(QWidget *parent = nullptr);
    bool Qfilejudg(QString username);
    QString username;
    QString newpas;
    QString resure;
    ~ch();
    void SendData(QString);
private slots:
    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked();

private:
    Ui::ch *ui;
};

#endif // CH_H
