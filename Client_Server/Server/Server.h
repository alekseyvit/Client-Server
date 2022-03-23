#pragma once

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
