#pragma once

#include "ui_Server.h"
#include "ServerWindow.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>


/*создание серверного сокета;

    установка параметров серверного сокета(IP - адрес и порт, на которые ожидаются подключения);

    перевод серверного сокета в режим отслеживания входящих соединений;

    при наличии входящего соединения : получить отдельный сокет для работы с этим конкретным соединением;

    отправка / получение информации;

    по окончании работы с клиентом : разрыв соединения и освобождение сокета, привязанного к этому клиенту;

    по окончании работы сервера : освобождение серверного сокета.
*/
class Server : public QTcpServer
{
    Q_OBJECT
private:
    QTcpSocket* _socket = nullptr;
    unsigned int _bytesInMessage = 0;
    ServerWindow* _serverWindow = nullptr;
    QByteArray _bytesArray;
public:
    Server(QWidget* parent = Q_NULLPTR);
    ~Server();
    void connectWithServerWindow(ServerWindow* serverWindow);
    void start(int port);

public slots:
    void handleWithIncommingConnection();
    void readDataFromConnection();
    void stoppingConnection();
};
