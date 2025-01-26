#include <QApplication>
#include "GameWindow.h"
#include "MenuWindow.h"

int main(int argc, char *argv[])
{
    qputenv("Qt_QPA_PLATFORM", "windows:darkmode=2");
    QApplication a(argc, argv);
    a.setStyle("modern");

    MenuWindow menuWindow;
    GameWindow gameWindow;
    menuWindow.GetGameWindowPtr(&gameWindow);
    gameWindow.GetMenuWindowPtr(&menuWindow);
    menuWindow.show();

    return a.exec();
}
