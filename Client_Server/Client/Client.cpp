#include "Client.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
    _ui.setupUi(this);
    auto connected = connect(_ui.buttonDisplayImage, SIGNAL(clicked(bool)), this, SLOT(buttonDisplayImageClicked()));
    assert(connected);
    connected = connect(_ui.buttonSendImage, SIGNAL(clicked(bool)), this, SLOT(buttonSendImageClicked()));
    assert(connected);
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
    QPixmap image;
    if (image.load(pathToImage)) {
        // Loaded !
        _ui.labelForImage->setPixmap(image);
    }
    else {
        // Can't load file
        _ui.textEdit->append("Can't open Image!");
        _ui.labelForImage->clear();
        _ui.labelForImage->setText("Can't open Image!");
        //throw std::exception("Can't load image! buttonDisplayImageClicked");
    }
}

void Client::buttonSendImageClicked() {
    _ui.labelForImage->setText("the buttonDisplayImage has been clicked !");

    QString pathToImage = _ui.textEdit->toPlainText();
    pathToImage = "..\\..\\Images\\" + pathToImage;
    QPixmap image;
    if (image.load(pathToImage)) {
        // Loaded !
        _ui.labelForImage->setPixmap(image);

        _socket = new QTcpSocket(this);
        _socket->connectToHost("127.0.0.1", 1234);//localhost
        //connect(_socket, SIGNAL(disconnect()), this, SLOT(deleteLater()));

        //From QPixmap TO QByteArray
        QByteArray bytesArray;
        QBuffer buffer(&bytesArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");//, "png", 0
        
        bytesArray = buffer.data();

        showAppendInTextEdit("Sending image file...");
        //showAppendInTextEdit(this->bytesArray.toBase64());

        if (_socket->waitForConnected(3000)) {
            // Connected 

            //send
            showAppendInTextEdit(QString::number(bytesArray.size()));

            int len = bytesArray.size();
            //bytesArray.insert(0, (const char*)len, sizeof(int));
            
            // prepare length of picture in bytes for sending to client
            union
            {
                unsigned int number;
                char arr[4];
            } msgLength;
            msgLength.number = bytesArray.size();

            QByteArray msg;
            msg.clear();
            msg.append(msgLength.arr, sizeof(msgLength.number));
            //QString msgLen = msgLength.arr;
            //showAppendInTextEdit(msgLen);

            //send pixture lingth in bytes
            _socket->write(msg);
            // send picture
            _socket->write(bytesArray);
            _socket->waitForBytesWritten(10000);
        }
        else { // Not Connected
            showAppendInTextEdit("Not Connected\n");
        }

        _socket->disconnectFromHost();
        _socket->deleteLater();
        // delete _socket;
        // Don't need to delete it manually
        // because parent will delete it automatically
        _socket = nullptr;
    }
    else {
        // Can't load image-file
        _ui.labelForImage->clear();
        _ui.labelForImage->setText("Can't send Image!");
        //throw std::exception("Can't open Image while trying to send Image.");
    }
}

void Client::showAppendInTextEdit(const QString& message) {
    _ui.textEdit->append(message);
}

void Client::showAppendInTextEdit(const char* str) {
    QString qStr = str;
    showAppendInTextEdit(qStr);
}
