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
    image = receivedPixMap;
}

void ServerWindow::buttonDisplayImageClicked() {
    QString str = "buttonDisplayImageClicked";
    this->appendTextEditField(str);
    ui.label->setPixmap(image);
}