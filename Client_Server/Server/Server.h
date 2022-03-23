#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>
#include "ui_Server.h"
#include "ServerWindow.h"

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
    QTcpSocket* socket = nullptr;
    ServerWindow* serverWindow;
    QByteArray bytesArray;
public:
    Server(QWidget* parent = Q_NULLPTR);
    ~Server();
    void connectWithServerWindow(ServerWindow* _serverWindow);
    void start(int port);

public slots:
    void serverHasIncommingConnection();
    void readDataFromConnection();
    void stoppingConnection();
    
};
