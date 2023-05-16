#include "Client.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
    _ui.setupUi(this);
    connect(_ui.buttonDisplayImage, SIGNAL(clicked(bool)), this, SLOT(buttonDisplayImageClicked()));
    connect(_ui.buttonSendImage, SIGNAL(clicked(bool)), this, SLOT(buttonSendImageClicked()));
    
    _ui.textEdit->setText("3.png");
}

Client::~Client() {
    //delete _socket;
}

void Client::buttonDisplayImageClicked() {
    _ui.labelForImage->setText("the buttonDisplayImage has been clicked !");
    QString pathToImage = _ui.textEdit->toPlainText();
    pathToImage = "..\\..\\Images\\" + pathToImage;
    //_ui.labelForImage->setText(pathToImage);
    if (_image.load(pathToImage)) {
        // Loaded !
        _ui.labelForImage->setPixmap(_image);
    }
    else {
        // Can't load file
        _image = QPixmap();
        _ui.labelForImage->setText("Can't open Image!");
    }
}

void Client::buttonSendImageClicked() {
    _ui.labelForImage->setText("the buttonDisplayImage has been clicked !");

    QString pathToImage = _ui.textEdit->toPlainText();
    pathToImage = "..\\..\\Images\\" + pathToImage;
    if (_image.load(pathToImage)) {
        // Loaded !
        _ui.labelForImage->setPixmap(_image);

        _socket = new QTcpSocket(this);
        _socket->connectToHost("127.0.0.1", 1234);//localhost
        //connect(_socket, SIGNAL(disconnect()), this, SLOT(deleteLater()));

        //From QPixmap TO QByteArray
        _bytesArray.clear();
        QBuffer buffer(&_bytesArray);
        buffer.open(QIODevice::WriteOnly);
        _image.save(&buffer, "PNG");//, "png", 0
        _bytesArray = buffer.data();

        showAppendInTextEdit("Sending _image file...");
        //showAppendInTextEdit(this->_bytesArray.toBase64());

        if (_socket->waitForConnected(3000)) {
            // Connected 

            //send
            showAppendInTextEdit(QString::number(_bytesArray.size()));

            int len = _bytesArray.size();
            //_bytesArray.insert(0, (const char*)len, sizeof(int));
            
            // prepare length of picture in bytes for sending to client
            union
            {
                unsigned int number;
                char arr[4];
            } msgLength;
            msgLength.number = _bytesArray.size();

            QByteArray msg;
            msg.clear();
            msg.append(msgLength.arr, sizeof(msgLength.number));
            //QString msgLen = msgLength.arr;
            //showAppendInTextEdit(msgLen);

            //send pixture lingth in bytes
            _socket->write(msg);
            // send picture
            _socket->write(_bytesArray);
            _socket->waitForBytesWritten(10000);

            //_socket->disconnect();
        }
        else { // Not Connected
            showAppendInTextEdit("Not Connected\n");
        }

        _socket->disconnect();
        _socket->disconnectFromHost();
        _socket->deleteLater();
        // delete _socket;
        // Don't need to delete it manually
        // because parent will delete it automatically
        _socket = nullptr;
    }
    else {
        // Can't load file
        _image = QPixmap();
        _ui.labelForImage->setText("Can't open Image!");
        throw std::exception("Can't open Image while trying to send Image.");
    }
}

void Client::showAppendInTextEdit(const QString& message) {
    _ui.textEdit->append(message);
}

void Client::showAppendInTextEdit(const char* str) {
    QString qStr = str;
    showAppendInTextEdit(qStr);
}