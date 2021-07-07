#ifndef STAGEPREPARE_H
#define STAGEPREPARE_H

#include <QMainWindow>
#include "stream.h"
#include "lobby.h"
#include "auth.h"
#include "game.h"
#include "stagegame.h"
#include "stagelogin.h"
#include "thread_receive.h"
#include "queue"
#include "qmessagebox.h"
#include "uitextconst.h"

namespace Ui {
class StagePrepare;
}

class StagePrepare : public QMainWindow
{
    Q_OBJECT

public:
    explicit StagePrepare(QWidget *parent = nullptr);
    ~StagePrepare();

    StageGame *gameStage;
    Thread_Receive *receiveThread;
    User clientUser;
    Lobby currentLobby; // current Lobby of prepare Stage
    int readyRequest, unreadyRequest, decisionTeamChange, decisionKickID, roomState;
    bool waitForKickResponse = false, waitForChangeTeamResponse = false;
    std::queue<char*> bufferQueue;

    void initializeStage(Socket* ,Lobby* ,Player*, User* );
    void updateUI();
    void handleDisconnected();
    void gotoPreviousStage();
    void showGame();
    void endGame();
    void runQueue();

private slots:
    void on_btnStart_clicked();
    void on_btnReady_clicked();
    void on_btnUnready_clicked();
    void on_btnChangeTeam_clicked();
    void on_actionQuit_Lobby_triggered();
    void on_btnKick_clicked();

public slots:
    void onReceive(char*);

private:
    Ui::StagePrepare *ui;
};

#endif // STAGEPREPARE_H
