#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <QTcpSocket>
#include <QString>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class PlayerClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PlayerClient)

public:
    explicit PlayerClient(QObject *parent = nullptr);

public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    void sendMessage(const QString &text);
    void disconnectFromHost();

private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);

private slots:
    void onReadyRead();

signals:
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
};

#endif // PLAYERCLIENT_H
