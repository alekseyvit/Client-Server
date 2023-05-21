#include "Client.h"

std::shared_mutex Client::_staticSendImageMutex;


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

void Client::sender(QPixmap image) {
    std::lock_guard<std::shared_mutex> lock(Client::_staticSendImageMutex);

    //From QPixmap TO QByteArray
    QByteArray bytesArray;
    QBuffer buffer(&bytesArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");//, "png", 0

    bytesArray = buffer.data(); // TODO Error here

    //showAppendInTextEdit("Sending image file...");
    //showAppendInTextEdit(this->bytesArray.toBase64());

    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 1234);//localhost
    //connect(socket, SIGNAL(disconnect()), this, SLOT(deleteLater()));

    if (socket->waitForConnected(3000)) {
        // Connected 

        //send
        showAppendInTextEdit(QString("sending ") + QString::number(bytesArray.size()) + QString("bytes.."));

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
        socket->write(msg);
        // send picture
        socket->write(bytesArray);
        socket->waitForBytesWritten(10000);
    }
    else { // Not Connected
        std::cout << "Not Connected\n" << std::endl;
        showAppendInTextEdit("Not Connected\n");
    }

    socket->disconnectFromHost();
    socket->deleteLater();
    // delete socket;
    // Don't need to delete it manually
    // because parent will delete it automatically
}

void Client::buttonSendImageClicked() {
    _ui.labelForImage->setText("the buttonDisplayImage has been clicked !");

    QString pathToImage = _ui.textEdit->toPlainText();
    pathToImage = "..\\..\\Images\\" + pathToImage;
    QPixmap image;
    if (image.load(pathToImage)) {
        // Loaded !
        _ui.labelForImage->setPixmap(image);

        // std::thread t([image, this]() { this->sender(image); }); //ok
        // t.detach(); //ok
        sender(image);
    }
    else {
        // Can't load image-file
        _ui.labelForImage->clear();
        _ui.labelForImage->setText("Can't send Image!");
        //throw std::exception("Can't open Image while trying to send Image.");
    }
}

void Client::showAppendInTextEdit(const QString& message) {
    std::lock_guard<std::mutex> appendLocker(_appendLocker);
    _ui.textEdit->append(message);
}

void Client::showAppendInTextEdit(const char* str) {
    QString qStr = str;
    showAppendInTextEdit(qStr);
}
