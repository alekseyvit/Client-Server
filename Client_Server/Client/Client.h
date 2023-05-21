#pragma once

#include "ui_Client.h"

#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QTcpSocket>
#include <QBuffer>


class Client : public QMainWindow
{
    Q_OBJECT
public:
    Client(QWidget *parent = Q_NULLPTR);
    Client::~Client();
    static std::shared_mutex _staticSendImageMutex;

private slots:
    void buttonSendImageClicked();
    void buttonDisplayImageClicked();

private:
    void showAppendInTextEdit(const QString& message);
    void showAppendInTextEdit(const char* str);
    void sender(QPixmap image);

    Ui::ClientClass _ui;
    std::mutex _appendLocker;
};
