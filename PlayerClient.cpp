/**
 * @file PlayerClient.cpp
 * @brief This file implements the functions for the PlayerClient class
 * @version 0.1
 * 
 */
#include "PlayerClient.h"

/**
 * @brief Construct a new Player Client:: Player Client object and Connect signals to socket.
 * 
 * @param parent Object that contains this client.
 */
PlayerClient::PlayerClient(QObject *parent): QObject(parent), m_clientSocket(std::make_unique<QTcpSocket>(this)), m_loggedIn(false)
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket.get(), &QTcpSocket::connected, this, &PlayerClient::connected);
    connect(m_clientSocket.get(), &QTcpSocket::disconnected, this, &PlayerClient::disconnected);

    // Connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket.get(), &QTcpSocket::readyRead, this, &PlayerClient::onReadyRead);

    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    connect(m_clientSocket.get(), &QAbstractSocket::errorOccurred, this, &PlayerClient::error);

    // Reset the m_loggedIn variable when we disconnect. Since the operation is trivial we use a lambda instead of creating another slot
    connect(m_clientSocket.get(), &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}

/**
 * @brief This function attempts to log in the client with a given username.
 * 
 * @param userName The client's desired username.
 */
void PlayerClient::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState) { // If the client is connected
        // Create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket.get());

        // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_6_8);

        // Create the JSON we want to send
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("login");
        message["username"] = userName;

        // Send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}

/**
 * @brief This function attempts to send a message from the user to the server. 
 * 
 * @param text The message's content.
 */
void PlayerClient::sendMessage(const QString &text)
{
    if (text.isEmpty())
        return; // Don't send empty messages

    // Create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket.get());

    // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_6_8);

    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("message");
    message[QStringLiteral("text")] = text;

    // send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}

/**
 * @brief This function disconnects the client from the server.
 * 
 */
void PlayerClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}

/**
 * @brief This function connects the clien to the server.
 * 
 * @param address Address o attempted connection.
 * @param port Port of attemped connection.
 */
void PlayerClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address, port);
}

/**
 * @brief This function is acvtivated when the user receives a Json from the server.
 * 
 * @param docObj The Json object received.
 */
void PlayerClient::jsonReceived(const QJsonObject &docObj)
{
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message
        if (m_loggedIn)
            return; // if we are already logged in we ignore
        // the success field will contain the result of our attempt to login
        const QJsonValue resultVal = docObj.value(QLatin1String("success"));
        if (resultVal.isNull() || !resultVal.isBool())
            return; // the message had no success field so we ignore
        const bool loginSuccess = resultVal.toBool();
        if (loginSuccess) {
            // we logged in succesfully and we notify it via the loggedIn signal
            emit loggedIn();
            return;
        }
        // the login attempt failed, we extract the reason of the failure from the JSON
        // and notify it via the loginError signal
        const QJsonValue reasonVal = docObj.value(QLatin1String("reason"));
        emit loginError(reasonVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("message"), Qt::CaseInsensitive) == 0) { //It's a chat message
        // we extract the text field containing the chat text
        const QJsonValue textVal = docObj.value(QLatin1String("text"));
        // we extract the sender field containing the username of the sender
        const QJsonValue senderVal = docObj.value(QLatin1String("sender"));
        if (textVal.isNull() || !textVal.isString())
            return; // the text field was invalid so we ignore
        if (senderVal.isNull() || !senderVal.isString())
            return; // the sender field was invalid so we ignore
        // we notify a new message was received via the messageReceived signal
        emit messageReceived(senderVal.toString(), textVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0) { // A user joined the chat
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the new user via the userJoined signal
        emit userJoined(usernameVal.toString());
    } else if (typeVal.toString().compare(QLatin1String("userdisconnected"), Qt::CaseInsensitive) == 0) { // A user left the chat
        // we extract the username of the new user
        const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
        if (usernameVal.isNull() || !usernameVal.isString())
            return; // the username was invalid so we ignore
        // we notify of the user disconnection the userLeft signal
        emit userLeft(usernameVal.toString());
    }
}

/**
 * @brief This function is called when client is available to receive a new Json. It attempts to read a new received Json.
 * 
 */
void PlayerClient::onReadyRead()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket.get());
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // start an infinite loop
    for (;;) {
        // we start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
        socketStream.startTransaction();
        // we try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction()) {
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonDoc.isObject()) // and is a JSON object
                    jsonReceived(jsonDoc.object()); // parse the JSON
            }
            // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }
    }
}
