#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QTcpSocket>
#include "ui_Client.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);

private slots:
    void buttonSendImageClicked();

public slots:
    void buttonDisplayImageClicked();

private:
    void runConnection();
    void showRequestFromServer();

    void Client::showInTextEdit(QByteArray& bytesArray);
    void Client::showInTextEdit(QString message);

    Ui::ClientClass ui;
    QTcpSocket* socket;
    QByteArray bytesArray;
};
