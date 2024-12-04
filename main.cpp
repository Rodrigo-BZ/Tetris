#include "window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window main;
    main.setWindowState(Qt::WindowFullScreen);
    main.show();
    return a.exec();
}
