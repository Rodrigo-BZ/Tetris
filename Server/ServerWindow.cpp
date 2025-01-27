/**
 * @file ServerWindow.cpp
 * @brief This file implements the functions for the ServerWindow class
 * @version 0.1
 * 
 */
#include "ServerWindow.h"
#include "./ui_ServerWindow.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWindow)
    , m_centralServer(new CentralServer(this))
{
    ui->setupUi(this);
    connect(ui->startStopButton, &QPushButton::clicked, this, &ServerWindow::toggleStartServer);
    connect(m_centralServer, &CentralServer::logMessage, this, &ServerWindow::logMessage);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

/**
 * @brief This function is called the the button is pressed. It toggles the server between started and stopped states.
 * 
 */
void ServerWindow::toggleStartServer()
{
    if (m_centralServer->isListening()) {
        m_centralServer->stopServer();
        ui->startStopButton->setText(tr("Start Server"));
        logMessage(QStringLiteral("Server Stopped"));
    } else {
        if (!m_centralServer->listen(QHostAddress::Any, 7777)) {
            QMessageBox::critical(this, tr("Error"), tr("Unable to start the server"));
            return;
        }
        logMessage(QStringLiteral("Server Started"));
        ui->startStopButton->setText(tr("Stop Server"));
    }
}

/**
 * @brief This function logs a message in the server window.
 * 
 * @param msg The message being recorded.
 */
void ServerWindow::logMessage(const QString &msg)
{
    ui->logEditor->appendPlainText(msg + QLatin1Char('\n'));
}
