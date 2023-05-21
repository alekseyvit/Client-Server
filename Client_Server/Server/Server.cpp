#include "Server.h"
#include "ServerWindow.h"

Server::Server(QWidget* parent) : QTcpServer(parent)
{
    qDebug() << "Server construction: ";

    auto connected = connect(this, SIGNAL(newConnection()),
        this, SLOT(handleWithIncommingConnection()));
    assert(connected);
}

Server::~Server() {
    // _socket will be deleted by deleteLater method
}

//void Server::connectWithServerWindow(ServerWindow* serverWindow) {
//    _serverWindow = serverWindow;
//}

/*Start listenning for connections*/
void Server::start(int port) {
    if (this->listen(QHostAddress::Any, port)) {
        QString str = "Server started.\nListening: ";
        str.append((this->isListening()) ? "true" : "false");
        emit setTextSignal(str);
    }
    else {
        //_serverWindow->setTextToGUI("Server didn't start");
        emit setTextSignal(QString("Server didn't start"));
        throw std::exception("Server didn't start");
    }
}

/*Executes on readyRead signal from _socket*/
void Server::readDataFromConnection() {
    size_t bytesAvailable = 0;
    while ((bytesAvailable = this->_socket->bytesAvailable()) > 0)
    {
        QString readProcess = "reading " + QString::number(bytesAvailable);
        readProcess += " bytes...";
        //_serverWindow->appendTextToGUI(readProcess);
        emit appendTextSignal(readProcess);
        
        //read
        _bytesArray.append(_socket->read(bytesAvailable));
 
        // Calculate amount bytes in Message (Picture)
        if (_bytesInMessage == 0) {
            union
            {
                unsigned int number;
                char arr[4];
            } msgLength;

            for (int i = 0; i < sizeof(unsigned int); ++i) {
                msgLength.arr[i] = _bytesArray.at(i);
            }
            _bytesInMessage = msgLength.number;
        }

        /*QString curr = _bytesArray.toBase64(); //for debugging:
        _serverWindow->appendTextToGUI(curr);*/
    }
}

/*Stops connection for _socket*/
void Server::stoppingConnection() {
    //_serverWindow->appendTextToGUI("stoppingConnectionProcess\n");
    emit appendTextSignal(QString("stoppingConnectionProcess\n"));

    _bytesArray.remove(0, sizeof(unsigned int)); // Removes first 4 bytes of ByteArrayData,
                                                // leaving data unchanged

    QPixmap image;
    if (image.loadFromData(_bytesArray, "PNG"))
    {
        //_serverWindow->setImageToGUI(image);
        emit setImageSignal(image);
    }
    else {
        QString errorString = "_bytesArray.size() = " + QString::number(_bytesArray.size());
        //_serverWindow->appendTextToGUI(errorString);
        emit appendTextSignal(errorString);
        //_serverWindow->appendTextToGUI("\n\nError: received data can't be transformed to QPixmap!\n\n");
        emit appendTextSignal(QString("\n\nError: received data can't be transformed to QPixmap!\n\n"));
        image.fill(Qt::black);
    }

    _socket->disconnectFromHost();
    /*_socket->close();*/
    _socket->deleteLater();
    _socket = nullptr;
    _bytesInMessage = 0;//Change this for next connection
    _bytesArray.clear();
    //_serverWindow->displayImage();// added due to tecnical task
    emit displayImageSignal();// added due to tecnical task
}

/*Read data from incommin connection*/
void Server::handleWithIncommingConnection() {
    appendTextSignal(QString("handleWithIncommingConnection..."));
    _socket = this->nextPendingConnection();
    _bytesArray.clear();

    auto connected = connect(_socket, SIGNAL(readyRead()),
        this, SLOT(readDataFromConnection())
    );
    assert(connected);

    //_socket->write("hello client\r\n");
    //_socket->flush();
    //_socket->waitForBytesWritten(1000);

    // I want disconnect from client if we received all the Image-data
    while (sizeof(unsigned int) + _bytesInMessage > _bytesArray.size()) {
        int msecs = 1000;
        if(_socket->waitForReadyRead(msecs)) {
            //_serverWindow->appendTextToGUI("Reading...");
            emit appendTextSignal(QString("Reading..."));
        }
    }
    
    stoppingConnection();
}
