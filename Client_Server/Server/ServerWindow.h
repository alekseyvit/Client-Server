#pragma once

#include "ui_Server.h"

#include <QtWidgets/QMainWindow>


class ServerWindow : public QMainWindow
{
    Q_OBJECT
private:
    //label, displayButton, textEdit
    QPixmap _image;
    Ui::ServerClass _ui;
public:
    ServerWindow(QWidget *parent = Q_NULLPTR);

    // may use Observer Pattern instead
public slots:
    void setTextToGUI(const QString& str);
    //void setTextToGUI(const char* str);
    void appendTextToGUI(const QString& str);
    //void appendTextToGUI(const char* _str);
    void setImageToGUI(const QPixmap& pixMap);
    void displayImage();

private slots:
    void buttonDisplayImageClicked();
};
