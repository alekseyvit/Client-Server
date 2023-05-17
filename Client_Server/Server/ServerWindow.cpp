#include "ServerWindow.h"
#include "Server.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _ui.setupUi(this);
    // old-style connect function
    auto connected = connect(_ui.displayButton, SIGNAL(clicked(bool)),
        this, SLOT(buttonDisplayImageClicked()));
    assert(connected);
}

void ServerWindow::setTextToGUI(const QString& str) {
    _ui.textEdit->setText(str);
}

void ServerWindow::appendTextToGUI(const QString& str) {
    _ui.textEdit->append(str);
}

void ServerWindow::setImageToGUI(const QPixmap& receivedPixMap) {
    this->appendTextToGUI("stored _image is changed");
    _image = receivedPixMap;
}

void ServerWindow::buttonDisplayImageClicked() {
    this->appendTextToGUI("buttonDisplayImageClicked");
    _ui.label->setPixmap(_image);
}

void ServerWindow::displayImage() {
    QPixmap imageToShow;
    if ( _image.size().height() > _ui.centralWidget->size().height() ) {
        QString str = QString::number(_image.size().height());
        this->appendTextToGUI(str);

        str = QString::number(_ui.centralWidget->size().height());
        this->appendTextToGUI(str);
        
        imageToShow = _image.scaledToHeight(_ui.centralWidget->size().height());
    }
    if ( _image.size().width() > _ui.centralWidget->size().width() ) {
        QString str = QString::number(_image.size().width());
        this->appendTextToGUI(str);

        str = QString::number(_ui.centralWidget->size().width());
        this->appendTextToGUI(str);

        imageToShow = _image.scaledToWidth(_ui.centralWidget->size().width());
    }
    _ui.label->setPixmap(imageToShow);
}