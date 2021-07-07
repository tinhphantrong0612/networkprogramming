#ifndef STAGEGAME_H
#define STAGEGAME_H

#include <QMainWindow>
#include <thread_receive.h>
#include "lobby.h"

namespace Ui {
class StageGame;
}

class StageGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit StageGame(QWidget *parent = nullptr);
    ~StageGame();
    Ui::StageGame *ui;
    Socket clientSocket;
    Game currentGame;
    Player currentPlayer;
    Lobby currentLobby;

    // Override
    void loadStaticUI();
    void loadPlayers();
    void updateDynamicUI();
    void informRule();

private slots:
    void on_buttonBuyItem_clicked();
    void on_actionRules_triggered();
    void on_buttonAttack_clicked();
    void on_buttonCheat_clicked();
    void on_actionQuit_Game_triggered();
    void on_btnContinue_clicked();
};

#endif // STAGEGAME_H
