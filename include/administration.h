#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QFile>
#include<QString>
#include<QTextStream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();

private slots:
    void on_pushOK_clicked();

    void on_pushNOK_clicked();

    void on_pushEXIT_clicked();

    void on_pushCANCEL_clicked();

    void on_pushREFRESH_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
