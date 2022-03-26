#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>
#include "ui_Server.h"
#include "ServerWindow.h"

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
    QTcpSocket* socket = nullptr;
    unsigned int bytesInMessage = 0;
    ServerWindow* serverWindow = nullptr;
    QByteArray bytesArray;
public:
    Server(QWidget* parent = Q_NULLPTR);
    ~Server();
    void connectWithServerWindow(ServerWindow* _serverWindow);
    void start(int port);

public slots:
    void handleWithIncommingConnection();
    void readDataFromConnection();
    void stoppingConnection();
};
