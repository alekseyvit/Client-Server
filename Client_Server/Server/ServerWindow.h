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
    void setTextEditField(const char* _str);
    void appendTextEditField(QString& str);
    void appendTextEditField(const char* _str);
    void setImageToServerWindow(QPixmap& pixMap);
    void displayImage();
private slots:
    void buttonDisplayImageClicked();
};
