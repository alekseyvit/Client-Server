#pragma once

#include "ui_Server.h"

#include <QtWidgets/QMainWindow>


class ServerWindow : public QMainWindow
{
    Q_OBJECT
public:
    ServerWindow(QWidget *parent = Q_NULLPTR);

    // may use Observer Pattern instead
public slots:
    void setTextToGUI(const QString& str);
    void appendTextToGUI(const QString& str);
    void setImageToGUI(const QPixmap& pixMap);
    void displayImage();

private slots:
    void buttonDisplayImageClicked();

private:
    //label, displayButton, textEdit
    QPixmap _image;
    Ui::ServerClass _ui;
};
