#include <QApplication>
#include "MenuWindow.h"
#include "GameWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow menuWindow;
    GameWindow gameWindow;
    menuWindow.GetGameWindowPtr(&gameWindow);
    gameWindow.GetMenuWindowPtr(&menuWindow);
    menuWindow.show();
    return a.exec();
}
