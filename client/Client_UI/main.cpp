#include "stagelogin.h"
#include "stream.h"
#include "constant.h"
#include <QApplication>

#include "stagegame.h"

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        WSACleanup();
        return 1;
    }

    QApplication a(argc, argv);

    //Initialize first Entry of Application: Login UI
    Socket socket = Socket(DEFAULT_PORT,(char*)DEFAULT_IP);
    StageLogin *firstScene = new StageLogin(nullptr);
    firstScene->initializeStage(&socket,0);
    firstScene->show();

    return a.exec();
}
