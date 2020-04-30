#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFixedSize(1100,700);
    w.setWindowTitle("Snake");
    w.show();
    return a.exec();
}
