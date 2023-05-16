#pragma once

#include "ui_Server.h"
#include "ServerWindow.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>


/*�������� ���������� ������;

    ��������� ���������� ���������� ������(IP - ����� � ����, �� ������� ��������� �����������);

    ������� ���������� ������ � ����� ������������ �������� ����������;

    ��� ������� ��������� ���������� : �������� ��������� ����� ��� ������ � ���� ���������� �����������;

    �������� / ��������� ����������;

    �� ��������� ������ � �������� : ������ ���������� � ������������ ������, ������������ � ����� �������;

    �� ��������� ������ ������� : ������������ ���������� ������.
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
