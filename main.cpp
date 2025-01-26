#include <QApplication>
#include "GameWindow.h"
#include "MenuWindow.h"

int main(int argc, char *argv[])
{
    qputenv("Qt_QPA_PLATFORM", "windows:darkmode=2");
    QApplication a(argc, argv);

    MenuWindow menuWindow;
    GameWindow gameWindow;

    gameWindow.setObjectName("GameWindow");
    gameWindow.setStyleSheet("QWidget#GameWindow{background-color: #1e1e1e}");

    menuWindow.GetGameWindowPtr(&gameWindow);
    gameWindow.GetMenuWindowPtr(&menuWindow);
    menuWindow.show();

    return a.exec();
}
