#include "Client.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.buttonDisplayImage, SIGNAL(clicked(bool)), this, SLOT(buttonDisplayImageClicked()));
    connect(ui.buttonSendImage, SIGNAL(clicked(bool)), this, SLOT(buttonSendImageClicked()));
    
    ui.textEdit->setText("3.jpg");
}

Client::~Client() {
    //delete socket;
}

void Client::buttonDisplayImageClicked() {
    ui.labelForImage->setText("the buttonDisplayImage has been clicked !");
    QString pathToImage = ui.textEdit->toPlainText();
    //ui.labelForImage->setText(pathToImage);
    if (image.load(pathToImage)) {
        // Loaded !
        ui.labelForImage->setPixmap(image);
    }
    else {
        // Can't load file
        image = QPixmap();
        ui.labelForImage->setText("Can't open Image!");
    }
}

void Client::buttonSendImageClicked() {
    ui.labelForImage->setText("the buttonDisplayImage has been clicked !");

    QString pathToImage = ui.textEdit->toPlainText();
    if (image.load(pathToImage)) {
        // Loaded !
        ui.labelForImage->setPixmap(image);

        socket = new QTcpSocket(this);
        socket->connectToHost("127.0.0.1", 1234);//localhost
        connect(socket, SIGNAL(disconnect()), this, SLOT(deleteLater()));

        //From QPixmap TO QByteArray
        bytesArray.clear();
        QBuffer buffer(&bytesArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");//, "png", 0
        bytesArray = buffer.data();

        showAppendInTextEdit("Sending image file...");
        //showAppendInTextEdit(this->bytesArray.toBase64());

        if (socket->waitForConnected(3000)) {
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
            socket->write(msg);
            // send picture
            socket->write(bytesArray);
            socket->waitForBytesWritten(10000);
        }
        else { // Not Connected
            showAppendInTextEdit("Not Connected\n");
        }
    }
    else {
        // Can't load file
        image = QPixmap();
        ui.labelForImage->setText("Can't open Image!");
    }
}

void Client::showAppendInTextEdit(QString message) {
    ui.textEdit->append(message);
}

void Client::showAppendInTextEdit(const char* str) {
    QString qStr = str;
    showAppendInTextEdit(qStr);
}