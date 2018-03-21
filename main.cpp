#include "mainparserwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainParserWindow w;
    w.show();

    return a.exec();
}
