#define DEBUG
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int* x = new int;
#ifdef DEBUG
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
