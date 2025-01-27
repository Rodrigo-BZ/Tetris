/**
 * @file CentralServer.h
 * @brief Header file for the CentralServer class.
 * @version 0.1
 * 
 */
#ifndef CENTRALSERVER_H
#define CENTRALSERVER_H

#include <QTcpServer>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTimer>
#include "serverworker.h"

/**
 * @brief This class represents the central server unit. It manages all server workers and communications from and to clients.
 * 
 */
class CentralServer : public QTcpServer
{
    Q_OBJECT
    Q_DISABLE_COPY(CentralServer)

public:
    explicit CentralServer(QObject *parent = nullptr);

public slots:
    void stopServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    void jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &doc);
    void jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc);
    void sendJson(ServerWorker *destination, const QJsonObject &message);
    /// @brief A QVector containing server workers.
    QVector<ServerWorker *> m_clients;

private slots:
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    void jsonReceived(ServerWorker *sender, const QJsonObject &doc);
    void userDisconnected(ServerWorker *sender);
    void userError(ServerWorker *sender);

signals:
    void logMessage(const QString &msg);
};

#endif // CENTRALSERVER_H
