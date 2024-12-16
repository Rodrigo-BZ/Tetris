#include <QApplication>
#include "GameGrid.cpp"
#include "GameWindow.cpp"
#include "MenuWindow.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow menuWindow;
    GameWindow gameWindow;
    menuWindow.GetGameWindowPtr(&gameWindow);
    gameWindow.GetMenuWindowPtr(&menuWindow);
    //menuWindow.setWindowState(Qt::WindowFullScreen);
    //gameWindow.setWindowState(Qt::WindowFullScreen);
    menuWindow.show();
    return a.exec();
}
