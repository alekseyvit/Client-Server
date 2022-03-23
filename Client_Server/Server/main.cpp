#include "ServerWindow.h"
#include "Server.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    ServerWindow w;
    w.show();

    Server server;
    server.connectWithServerWindow(&w);
    server.start(1234);

    return a.exec();
}
