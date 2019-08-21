#include "mainwindow.h"
#include <QApplication>
#include "include\log_in.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOGI w;
    w.show();

    return a.exec();
}
