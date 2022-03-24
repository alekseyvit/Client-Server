#include "Server.h"
#include "ServerWindow.h"

Server::Server(QWidget* parent) : QTcpServer(parent)
{
    qDebug() << "Server construction: ";

    connect(this, SIGNAL(newConnection()),
        this, SLOT(handleWithIncommingConnection()));
}

Server::~Server() {
    // socket will be deleted by deleteLater method
    // serverWindow is allocated in heap in main.cpp
}

void Server::connectWithServerWindow(ServerWindow* _serverWindow) {
    serverWindow = _serverWindow;
}

/*Start listenning for connections*/
void Server::start(int port) {
    if (this->listen(QHostAddress::Any, port)) {
        QString str = "Server started.\nListening: ";
        str.append((this->isListening()) ? "true" : "false");
        serverWindow->setTextEditField(str);
    }
    else {
        serverWindow->setTextEditField("Server didn't start");
    }
}

/*Executes on readyRead signal from socket*/
void Server::readDataFromConnection() {
    int bytesAvailable = 0;
    while ((bytesAvailable = this->socket->bytesAvailable()) > 0)
    {
        QString readProcess = "reading " + QString::number(bytesAvailable);
        readProcess += " bytes...";
        serverWindow->appendTextEditField(readProcess);
        
        //read
        bytesArray.append(socket->read(bytesAvailable));
 
        // Calculate amount bytes in Message (Picture)
        if (bytesInMessage == 0) {
            union
            {
                unsigned int number;
                char arr[4];
            } msgLength;

            for (int i = 0; i < sizeof(unsigned int); ++i) {
                msgLength.arr[i] = bytesArray.at(i);
            }
            bytesInMessage = msgLength.number;
        }

        /*QString curr = bytesArray.toBase64(); //for debugging:
        serverWindow->appendTextEditField(curr);*/
    }
}

/*Stops connection for socket*/
void Server::stoppingConnection() {
    serverWindow->appendTextEditField("stoppingConnectionProcess\n");

    bytesArray.remove(0, sizeof(unsigned int)); // Removes first 4 bytes of ByteArrayData,
                                                // leaving data unchanged

    QPixmap image;
    if (image.loadFromData(bytesArray, "PNG"))
    {
        serverWindow->setImageToServerWindow(image);
    }
    socket->disconnectFromHost();
    socket->deleteLater();
}

/*Read data from incommin connection*/
void Server::handleWithIncommingConnection() {
    socket = this->nextPendingConnection();
    bytesArray.clear();

    connect(socket, SIGNAL(readyRead()),
        this, SLOT(readDataFromConnection())
    );

    socket->write("hello client\r\n");
    socket->flush();
    socket->waitForBytesWritten(1000);

    // I want disconnect from client if no data is readyRead for 3 sec
    while (bytesInMessage + sizeof(unsigned int) > bytesArray.size()) {
        if(socket->waitForReadyRead(1000)) {
            serverWindow->appendTextEditField("Reading...");
        }
    }
    stoppingConnection();
}
