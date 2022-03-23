#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"

class ServerWindow : public QMainWindow
{
    Q_OBJECT
private:
    //label, displayButton, textEdit
    QPixmap image;
    Ui::ServerClass ui;
public:
    ServerWindow(QWidget *parent = Q_NULLPTR);
    void setTextEditField(QString& str);
    void appendTextEditField(QString& str);
    void setImageToServerWindow(QPixmap& pixMap);
private slots:
    void buttonDisplayImageClicked();

};
