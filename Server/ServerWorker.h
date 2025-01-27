/**
 * @file ServerWorker.h
 * @brief Header file for the ServerWorker class
 * @version 0.1
 * 
 */
#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

/**
 * @brief This class represents the server worker. It handles the communications from one client to the server.
 * 
 */
class ServerWorker : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ServerWorker)

public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName() const;
    void setUserName(const QString &userName);
    void sendJson(const QJsonObject &jsonData);

public slots:
    void disconnectFromClient();

private:
    /// @brief A pointer to the server socket object.
    QTcpSocket *m_serverSocket;
    /// @brief The user name of the client being handled by the server worker.
    QString m_userName;

private slots:
    void receiveJson();

signals:
    void jsonReceived(const QJsonObject &jsonDoc);
    void disconnectedFromClient();
    void error();
    void logMessage(const QString &msg);
};

#endif // SERVERWORKER_H
