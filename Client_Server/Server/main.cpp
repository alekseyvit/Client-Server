#include "ServerWindow.h"
#include "Server.h"

#include <QtWidgets/QApplication>

void connectServerAndGUI(Server& server, ServerWindow& gui);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    ServerWindow gui;
    gui.show();

    Server server;
    connectServerAndGUI(server, gui);
    server.start(1234);

    return a.exec();
}

void connectServerAndGUI(Server& server, ServerWindow& gui) {
    auto connected = QObject::connect(&server, &Server::setTextSignal,
        &gui, &ServerWindow::setTextToGUI);
    assert(connected);

    connected = QObject::connect(&server, &Server::appendTextSignal,
        &gui, &ServerWindow::appendTextToGUI);
    assert(connected);

    connected = QObject::connect(&server, &Server::displayImageSignal,
        &gui, &ServerWindow::displayImage);
    assert(connected);

    connected = QObject::connect(&server, &Server::setImageSignal,
        &gui, &ServerWindow::setImageToGUI);
    assert(connected);
}