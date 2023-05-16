#include "ServerWindow.h"
#include "Server.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _ui.setupUi(this);
    connect(_ui.displayButton, SIGNAL(clicked(bool)),
        this, SLOT(buttonDisplayImageClicked()));
}

void ServerWindow::setTextEditField(const QString& str) {
    _ui.textEdit->setText(str);
}

void ServerWindow::setTextEditField(const char* str) {
    _ui.textEdit->setText(QString(str));
}

void ServerWindow::appendTextEditField(const QString& str) {
    _ui.textEdit->append(str);
}

void ServerWindow::appendTextEditField(const char* str) {
    _ui.textEdit->append(QString(str));
}

void ServerWindow::setImageToServerWindow(QPixmap& receivedPixMap) {
    this->appendTextEditField("stored _image is changed");
    _image = receivedPixMap;
}

void ServerWindow::buttonDisplayImageClicked() {
    this->appendTextEditField("buttonDisplayImageClicked");
    _ui.label->setPixmap(_image);
}

void ServerWindow::displayImage() {
    QPixmap imageToShow;
    if ( _image.size().height() > _ui.centralWidget->size().height() ) {
        QString str = QString::number(_image.size().height());
        this->appendTextEditField(str);

        str = QString::number(_ui.centralWidget->size().height());
        this->appendTextEditField(str);
        
        imageToShow = _image.scaledToHeight(_ui.centralWidget->size().height());
    }
    if ( _image.size().width() > _ui.centralWidget->size().width() ) {
        QString str = QString::number(_image.size().width());
        this->appendTextEditField(str);

        str = QString::number(_ui.centralWidget->size().width());
        this->appendTextEditField(str);

        imageToShow = _image.scaledToWidth(_ui.centralWidget->size().width());
    }
    _ui.label->setPixmap(imageToShow);
}