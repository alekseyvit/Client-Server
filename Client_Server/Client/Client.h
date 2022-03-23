#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QTcpSocket>
#include <QBuffer>
#include "ui_Client.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);
    Client::~Client();

private slots:
    void buttonSendImageClicked();
    void buttonDisplayImageClicked();

private:
    void runConnection();
    void showRequestFromServer();

    void showInTextEdit(QByteArray& bytesArray);
    void showInTextEdit(QString message);

    Ui::ClientClass ui;
    QTcpSocket* socket;
    QPixmap image;
    QByteArray bytesArray;
};
