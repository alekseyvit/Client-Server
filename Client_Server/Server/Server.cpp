#include "Server.h"
#include "ServerWindow.h"

Server::Server(QWidget* parent) : QTcpServer(parent)
{
    qDebug() << "Server construction: ";

    connect(this, SIGNAL(newConnection()),
        this, SLOT(serverHasIncommingConnection()));
}

Server::~Server() {
    // socket will be deleted by deleteLater method
    // serverWindow is allocated in heap in main.cpp
}

void Server::connectWithServerWindow(ServerWindow* _serverWindow) {
    serverWindow = _serverWindow;
}

void Server::start(int port) {
    if (this->listen(QHostAddress::Any, port)) {
        //qDebug() << "Listening: " << this->isListening(); //qDebug() << "Server started";
        QString str = "Server started.\nListening: ";
        str.append((this->isListening()) ? "true" : "false");
        serverWindow->setTextEditField(str);
    }
    else {
        //qDebug() << this->isListening(); //qDebug() << "Error?";
        QString str = "Server didn't start";
        serverWindow->setTextEditField(str);
    }
}

void Server::readDataFromConnection() {
    int bytesAvailable = 0;
    while ((bytesAvailable = this->socket->bytesAvailable()) > 0)
    {
        QString readProcess = "reading " + QString::number(bytesAvailable);
        readProcess += " bytes...";
        serverWindow->appendTextEditField(readProcess);
        
        bytesArray.append(socket->read(bytesAvailable));
        //bytesArray.append(socket->readAll());
    }
}

void Server::stoppingConnection() {
    QString stoppingConnectionProcess = "stoppingConnectionProcess\n";
    serverWindow->appendTextEditField(stoppingConnectionProcess);

    QPixmap image;
    if (image.loadFromData(bytesArray, "PNG"))
    {
        serverWindow->setImageToServerWindow(image);
    }

    socket->deleteLater();
}

void Server::serverHasIncommingConnection() {
    socket = this->nextPendingConnection();
    /*if(socket->isOpen())
        socket = this->nextPendingConnection();
    else {
        QString error = "ERROR. Can't use this->socket\n";
        serverWindow->appendTextEditField(error);
    }*/
    connect(socket, SIGNAL(disconnected()),
        this, SLOT(stoppingConnection())//mush free dynamic memory
    );
    bytesArray.clear();
    connect(socket, SIGNAL(readyRead()),
        this, SLOT(readDataFromConnection())
    );

    socket->write("hello client\r\n");
    socket->flush();
    socket->waitForBytesWritten(1000);

    // I want disconnect from client if no data is readyRead
    // Not sure that this if is correct
    // Doesn't work with big files which comes in several parths (when several readyRead emited)
    //if (socket->waitForReadyRead()) {
    //    QString YES = "YES";
    //    serverWindow->appendTextEditField(YES);

    //    //QString str = bytesArray.toBase64();
    //    //serverWindow->appendTextEditField(str);

    //    QPixmap image;
    //    if (image.loadFromData(bytesArray, "PNG"))
    //    {
    //        serverWindow->setImageToServerWindow(image);
    //    }
    //}
    //else {
    //    QString NO = "NO";
    //    serverWindow->appendTextEditField(NO);

    //    QString str = bytesArray.toBase64();
    //    serverWindow->appendTextEditField(str);
    //}
}
