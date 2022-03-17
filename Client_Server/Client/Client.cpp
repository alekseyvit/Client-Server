#include "Client.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.buttonDisplayImage, SIGNAL(clicked(bool)), this, SLOT(buttonDisplayImageClicked()));
    connect(ui.buttonSendImage, SIGNAL(clicked(bool)), this, SLOT(buttonSendImageClicked()));
    socket = new QTcpSocket(this);
}

void Client::buttonDisplayImageClicked() {
    ui.labelForImage->setText("the buttonDisplayImage has been clicked !");
    QString pathToImage = ui.textEdit->toPlainText();
    QPixmap pixMap;
    if (pixMap.load(pathToImage)) {
        // Loaded !
        ui.labelForImage->setPixmap(pixMap);
    }
    else {
        // Can't load file
        ui.labelForImage->setText("Can't open Image!");
    }
}

void Client::buttonSendImageClicked() {
    ui.labelForImage->setText("the buttonDisplayImage has been clicked !");
    runConnection();
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
    QString size_of_bytesArray(bytesArray.size());
    ui.textEdit->append(size_of_bytesArray);

    ui.textEdit->append("\nreaded data:");
    ui.textEdit->append(bytesArray);
}
void Client::showInTextEdit(QString message) {
    ui.textEdit->append(message);
}