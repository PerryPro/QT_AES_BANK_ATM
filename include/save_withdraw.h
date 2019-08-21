#ifndef Save_Withdraw_H
#define Save_Withdraw_H

#include <QMainWindow>

namespace Ui {
class Save_Withdraw;
}

class Save_Withdraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit Save_Withdraw(QWidget *parent = nullptr);
    ~Save_Withdraw();
    void SendData(QString);
private slots:
    void on_Button_search_clicked();

    void on_Button_in_clicked();

    void on_Button_out_clicked();

    void on_pushButton_clicked();

private:
    Ui::Save_Withdraw *ui;
};

#endif // Save_Withdraw_H
