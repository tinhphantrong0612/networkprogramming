#ifndef STAGEWAITINGROOM_H
#define STAGEWAITINGROOM_H

#include <QMainWindow>
#include "stream.h"
#include "auth.h"
#include "lobby.h"

namespace Ui {
class StageWaitingRoom;
}

class StageWaitingRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit StageWaitingRoom(QWidget *parent = nullptr);
    ~StageWaitingRoom();

    Socket clientSocket;
    User clientUser;
    Lobby myLobby;
    Lobby listLobby[MAX_LOBBY];
    int lobbySize;

    void initializeStage(Socket* ,User* );

private slots:
    void on_btnCreate_clicked();
    void on_btnJoin_clicked();
    void on_btnRefresh_clicked();

    void on_actionLogout_triggered();

private:
    Ui::StageWaitingRoom *ui;

};

#endif // STAGEWAITINGROOM_H
