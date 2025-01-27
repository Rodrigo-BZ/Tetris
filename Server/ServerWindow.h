/**
 * @file ServerWindow.h
 * @brief Header file for the ServerWindow class
 * @version 0.1
 * 
 */
#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "CentralServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWindow; }
QT_END_NAMESPACE

/**
 * @brief This class represents the ServerWindow. It acts as a server screen manager to handle interactions with UI.
 * 
 */
class ServerWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWindow)
public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    /// @brief Ui containing visual elements of the server window.
    Ui::ServerWindow *ui;
    /// @brief Pointer to the CentralServer object.
    CentralServer *m_centralServer;

private slots:
    void toggleStartServer();
    void logMessage(const QString &msg);
};

#endif // SERVERWINDOW_H
