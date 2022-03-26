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
    ui.label->setPixmap(image);
}