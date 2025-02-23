#include "BestoPOSo.h"
#include <QtWidgets/QApplication>
#include "Menu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BestoPOSo w;
    w.show();
    return a.exec();
}
