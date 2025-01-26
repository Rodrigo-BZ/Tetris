#include "CentralServer.h"

CentralServer::CentralServer(QObject *parent) : QTcpServer(parent) {}

void CentralServer::incomingConnection(qintptr socketDescriptor)
{
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    ServerWorker *worker = new ServerWorker(this);
    // we attempt to bind the worker to the client
    if (!worker->setSocketDescriptor(socketDescriptor)) {
        // if we fail we clean up
        worker->deleteLater();
        return;
    }
    // connect the signals coming from the object that will take care of the
    // communication with this client to the slots in the central server
    connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&CentralServer::userDisconnected, this, worker));
    connect(worker, &ServerWorker::error, this, std::bind(&CentralServer::userError, this, worker));
    connect(worker, &ServerWorker::jsonReceived, this, std::bind(&CentralServer::jsonReceived, this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage, this, &CentralServer::logMessage);
    // we append the new worker to a list of all the objects that communicate to a single client
    m_clients.append(worker);
    // we log the event
    emit logMessage(QStringLiteral("New client Connected"));
}

void CentralServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination); // make sure destination is not null
    destination->sendJson(message); // call directly the worker method
}

void CentralServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    // iterate over all the workers that interact with the clients
    for (ServerWorker *worker : m_clients) {
        if (worker == exclude)
            continue; // skip the worker that should be excluded
        sendJson(worker, message); //send the message to the worker
    }
}

void CentralServer::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(doc).toJson()));
    if (sender->userName().isEmpty())
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}

void CentralServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    const QString userName = sender->userName();
    if (!userName.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userdisconnected");
        disconnectedMessage[QStringLiteral("username")] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + QLatin1String(" disconnected"));
    }
    sender->deleteLater();
}

void CentralServer::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + sender->userName());
}

void CentralServer::stopServer()
{
    for (ServerWorker *worker : m_clients) {
        worker->disconnectFromClient();
    }
    close();
}

void CentralServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    if (usernameVal.isNull() || !usernameVal.isString())
        return;
    const QString newUserName = usernameVal.toString().simplified();
    if (newUserName.isEmpty())
        return;
    for (ServerWorker *worker : std::as_const(m_clients)) {
        if (worker == sender)
            continue;
        if (worker->userName().compare(newUserName, Qt::CaseInsensitive) == 0) {
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("login");
            message[QStringLiteral("success")] = false;
            message[QStringLiteral("reason")] = QStringLiteral("duplicate username");
            sendJson(sender, message);
            return;
        }
    }
    sender->setUserName(newUserName);
    QJsonObject successMessage;
    successMessage[QStringLiteral("type")] = QStringLiteral("login");
    successMessage[QStringLiteral("success")] = true;
    sendJson(sender, successMessage);
    QJsonObject connectedMessage;
    connectedMessage[QStringLiteral("type")] = QStringLiteral("newuser");
    connectedMessage[QStringLiteral("username")] = newUserName;
    broadcast(connectedMessage, sender);
}

void CentralServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue textVal = docObj.value(QLatin1String("text"));
    if (textVal.isNull() || !textVal.isString())
        return;
    const QString text = textVal.toString().trimmed();
    if (text.isEmpty())
        return;
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("text")] = text;
    message[QStringLiteral("sender")] = sender->userName();
    broadcast(message, sender);
}
