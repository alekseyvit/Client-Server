#pragma once

#include "ui_Server.h"
#include "ServerWindow.h"

#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>
#include <QString>


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
public:
    Server(QWidget* parent = Q_NULLPTR);
    ~Server();
    void start(int port);

public slots:
    void handleWithIncommingConnection();
    void readDataFromConnection();
    void stoppingConnection();

signals:
    void setTextSignal(const QString& msg);
signals:
    void appendTextSignal(const QString& msg);
signals:
    void displayImageSignal();
signals:
    void setImageSignal(const QPixmap& image);

private:
    QTcpSocket* _socket = nullptr;
    unsigned int _bytesInMessage = 0;
    QByteArray _bytesArray;
};
