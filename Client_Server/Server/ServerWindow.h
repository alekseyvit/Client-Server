#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"

class ServerWindow : public QMainWindow
{
    Q_OBJECT
private:
    //label, displayButton, textEdit
    QPixmap _image;
    Ui::ServerClass _ui;
public:
    ServerWindow(QWidget *parent = Q_NULLPTR);
    void setTextEditField(const QString& str);
    void setTextEditField(const char* str);
    void appendTextEditField(const QString& str);
    void appendTextEditField(const char* _str);
    void setImageToServerWindow(QPixmap& pixMap);
    void displayImage();
private slots:
    void buttonDisplayImageClicked();
};
