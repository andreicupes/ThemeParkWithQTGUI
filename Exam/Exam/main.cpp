#include "gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service s;
    GUI w(s);
    return a.exec();
}
