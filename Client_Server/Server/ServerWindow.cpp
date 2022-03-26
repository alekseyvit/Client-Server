#include "ServerWindow.h"
#include "Server.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.displayButton, SIGNAL(clicked(bool)),
        this, SLOT(buttonDisplayImageClicked()));
}

void ServerWindow::setTextEditField(QString& str) {
    ui.textEdit->setText(str);
}

void ServerWindow::setTextEditField(const char* _str) {
    QString str = _str;
    ui.textEdit->setText(str);
}

void ServerWindow::appendTextEditField(QString& str) {
    ui.textEdit->append(str);
}

void ServerWindow::appendTextEditField(const char* _str) {
    QString str = _str;
    ui.textEdit->append(str);
}

void ServerWindow::setImageToServerWindow(QPixmap& receivedPixMap) {
    this->appendTextEditField("stored image is changed");
    image = receivedPixMap;
}

void ServerWindow::buttonDisplayImageClicked() {
    this->appendTextEditField("buttonDisplayImageClicked");
    ui.label->setPixmap(image);
}

void ServerWindow::displayImage() {
    QPixmap imageToShow;
    if ( image.size().height() > ui.centralWidget->size().height() ) {
        QString str = QString::number(image.size().height());
        this->appendTextEditField(str);

        str = QString::number(ui.centralWidget->size().height());
        this->appendTextEditField(str);
        
        imageToShow = image.scaledToHeight(ui.centralWidget->size().height());
    }
    if ( image.size().width() > ui.centralWidget->size().width() ) {
        QString str = QString::number(image.size().width());
        this->appendTextEditField(str);

        str = QString::number(ui.centralWidget->size().width());
        this->appendTextEditField(str);

        imageToShow = image.scaledToWidth(ui.centralWidget->size().width());
    }
    ui.label->setPixmap(imageToShow);
}