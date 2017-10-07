#include "CgalUiApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CgalUiApplication w;
    w.show();
    return a.exec();
}
