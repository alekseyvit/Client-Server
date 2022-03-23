#include "Client.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.buttonDisplayImage, SIGNAL(clicked(bool)), this, SLOT(buttonDisplayImageClicked()));
    connect(ui.buttonSendImage, SIGNAL(clicked(bool)), this, SLOT(buttonSendImageClicked()));
    //ui.textEdit->setText("1.PNG");
}

Client::~Client() {
    delete socket;
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
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 1234);//localhost

    //showInTextEdit(this->bytesArray);
 
    QString pathToImage = ui.textEdit->toPlainText();
    if (image.load(pathToImage)) {
        // Loaded !
        ui.labelForImage->setPixmap(image);

        //From QPixmap TO QByteArray
        bytesArray.clear();
        QBuffer buffer(&bytesArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");//, "png", 0
        bytesArray = buffer.data();

        showInTextEdit(this->bytesArray.toBase64());

        if (socket->waitForConnected(3000)) {
            qDebug() << "Connected";

            //send
            socket->write(bytesArray);
            socket->waitForBytesWritten(10000);
            //socket->write("\r\nhello, server!\r\n");

            //socket->waitForBytesWritten();
            //socket->waitForReadyRead(3000);
            //qDebug() << "Reading: " << socket->bytesAvailable();
            //qDebug() << "readAll: ";
            //QByteArray responce = socket->readAll();
            //qDebug() << responce;
            //showInTextEdit(responce);
            //closing
            //socket->close();
        }
        else {
            // Not Connected
            showInTextEdit("Not Connected\n");
            qDebug() << "Not Connected";
        }
    }
    else {
        // Can't load file
        image = QPixmap();
        ui.labelForImage->setText("Can't open Image!");
    }
    // Preparation of our QPixmap QByteArray bArray;

    //runConnection();
}

void Client::runConnection() {
    socket->connectToHost("google.com", 80);    //87.250.250.242 - ya.ru
    
    // local computer 
    //socket->connectToHost("172.0.0.1", 4242);

    if (socket->waitForConnected(3000)) {
        qDebug() << "Connected";

        //send
        socket->write("Hello, Google!\r\n\r\n\r\n\r\n");

        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

        qDebug() << "readAll: ";
        bytesArray = socket->readAll();
        qDebug() << bytesArray;       
        
        //closing
        socket->close();

        showInTextEdit(this->bytesArray);
    }
    else {
        // Not Connected
        showInTextEdit("Not Connected\n");
        qDebug() << "Not Connected";
    }
}

void Client::showInTextEdit(QByteArray& bytesArray) {
    ui.textEdit->setTextColor(Qt::red);
    ui.textEdit->setFont(ui.textEdit->font());

    ui.textEdit->append("readed data size:");
    QString size_of_bytesArray(QString::number(bytesArray.size()));
    ui.textEdit->append(size_of_bytesArray);

    ui.textEdit->append("\nreaded data:");
    ui.textEdit->append(bytesArray);
}

void Client::showInTextEdit(QString message) {
    ui.textEdit->append(message);
}