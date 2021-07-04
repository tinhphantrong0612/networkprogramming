#include "stageprepare.h"
#include "ui_stageprepare.h"

#include "stagegame.h"
#include "stagewaitingroom.h"
#include "util.h"
#include "qinputdialog.h"

#include "ui_stagegame.h"

StagePrepare::StagePrepare(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StagePrepare)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowTitle("Prepare for battle !");
}

StagePrepare::~StagePrepare()
{
    delete ui;
}

void StagePrepare::initializeStage(Socket *socket, Lobby *lobby, Player *player, User *user){
    // start receive thread
    receiveThread = new Thread_Receive(this,socket);
    connect(receiveThread, SIGNAL(send(char*)), this, SLOT(onReceive(char*)));
    receiveThread->start();

    this->roomState = UNREADY;
    this->gameStage = new StageGame();

    //Binding components
    bindUser(&clientUser,user);
    bindSocket(&gameStage->clientSocket,socket);
    bindLobby(&gameStage->currentLobby,lobby);
    bindPlayer(&gameStage->currentPlayer,player);

    //Update UI on first run
    updateUI();
}

void StagePrepare::updateUI(){
    ui->labelGreet->setText("Greeting, " + QString::fromLocal8Bit(gameStage->currentPlayer.username));
    ui->labelRoomID->setText(QString::number(gameStage->currentLobby.id));

    QString team1, team2, team3, team4;

    for ( int i = 0 ; i < gameStage->currentLobby.player_number ; i++ ){
        Player player = gameStage->currentLobby.players[i];
        QString state;
        if ( player.state == UNREADY) state = "UNREADY";
        else if ( player.state == READY ) state = "READY";

        if (player.id == gameStage->currentLobby.host) state = "HOST";

        switch (player.team_id){
            case 0:
                team1 += "  [ \"" + QString::fromLocal8Bit(player.username) + "\" , " + state + " , ID: " + QString::number(player.id) + " ]" ;
                break;
            case 1:
                team2 += "  [ \"" + QString::fromLocal8Bit(player.username) + "\" , " + state + " , ID: " + QString::number(player.id) + " ]" ;
                break;
            case 2:
                team3 += "  [ \"" + QString::fromLocal8Bit(player.username) + "\" , " + state + " , ID: " + QString::number(player.id) + " ]" ;
                break;
            case 3:
                team4 += "  [ \"" + QString::fromLocal8Bit(player.username) + "\" , " + state + " , ID: " + QString::number(player.id) + " ]" ;
                break;
             default:
                break;
        }
        if (!strcmp(player.username,gameStage->currentPlayer.username) ){
            //TODOS: show HOST / ORDINARY state
            if (player.id != gameStage->currentLobby.host) {
                ui->labelUserStatus->setText("ORDINARY");
            } else {
                ui->labelUserStatus->setText("HOST");
            }

            ui->labelUserTeam->setText(QString::number(player.team_id + 1) + " / " + QString::number(gameStage->currentLobby.team_number));
            ui->labelPlayerID->setText("Player ID : " + QString::number(player.id));
        }
    }
    ui->labelTeam1->setText(team1);
    ui->labelTeam2->setText(team2);
    ui->labelTeam3->setText(team3);
    ui->labelTeam4->setText(team4);
}

void StagePrepare::gotoPreviousStage(){
    //go back to Waiting room with current Socket, User
    // *Important: terminate current thread before go back to previous stage
    this->receiveThread->terminate();
    StageWaitingRoom *waitingRoom = new StageWaitingRoom();
    waitingRoom->initializeStage(&gameStage->clientSocket,&clientUser);
    waitingRoom->show();
    gameStage->close();
    this->close();
}

void StagePrepare::handleDisconnected(){
    QMessageBox::information(nullptr,"Network Error","Disconnected to server",0);
    this->receiveThread->terminate();
    StageLogin *login = new StageLogin(nullptr);
    login->initializeStage(&gameStage->clientSocket,1);
    login->show();
    gameStage->close();
    this->close();
}

void StagePrepare::showGame(){
    // show Game stage, also disable Prepare stage so user cannot interactive with this stage
    gameStage->show();
    gameStage->informRule();
    gameStage->loadPlayers();

    // Only quit room works . This only works if i disable widgets one by one, leave it later
    this->ui->btnChangeTeam->setDisabled(true);
    this->ui->btnKick->setDisabled(true);
    this->ui->btnReady->setDisabled(true);
    this->ui->btnUnready->setDisabled(true);
    this->ui->btnStart->setDisabled(true);

    // this->setWindowFlags(Qt::Dialog);
    // this->setWindowTitle("Game Room");
    // this->roomState = INGAME;
    this->hide();
}

void StagePrepare::runQueue(){
    while (bufferQueue.empty() == false){
        char buffer[BUFF_SIZE];
        strcpy_s(buffer,BUFF_SIZE,bufferQueue.front());

        // Switch response to handle
        // First: Get response code
        char resultHeader[CODE_SIZE+1],resultCode[RESULT_CODE_SIZE+1];
        strncpy_s(resultHeader, buffer, CODE_SIZE);
        strncpy_s(resultCode, buffer, RESULT_CODE_SIZE);

        qDebug() << "Receive (from emit) (from server): " << buffer << " strlen: " << strlen(buffer) ;

        // UPDATE GAME / LOBBY handle below
        // Update_lobby response handle (402) : call for update_lobby_response only
        if (!strcmp(resultHeader,UPDATE_LOBBY)){
            gameStage->currentLobby.update_lobby_response(buffer);
            // Case: a player quits (40200)
            if (!strcmp(resultCode,"40200")){
                gameStage->loadPlayers();
                gameStage->ui->listGameLog->insertItem(0,"[Game] A player has quitted!");
            }

            // Case : update change teams (40202)
            if ( waitForChangeTeamResponse == true ){
                gameStage->currentPlayer.team_id = decisionTeamChange;
                qDebug() << "Changed to team " << gameStage->currentPlayer.team_id ;
                waitForChangeTeamResponse = false;
            }

            // Case: Kick somebody
            if ( waitForKickResponse == true ){
                QMessageBox::information(nullptr,"Success","Player ID [" + QString::number(decisionKickID) + "] has been kicked out !",0);
                waitForKickResponse = false;
            }
        }

        // Update_game response handle (401): Start game / load question / attack / ... response handle
        if (!strcmp(resultHeader,UPDATE_GAME)){
            // Case: the game starts ( 40100 )
            if (!strcmp(resultCode,UPDATE_GAME_START)){
                gameStage->currentLobby.start_game_response(buffer);
                gameStage->currentGame.update_game_response(buffer,gameStage->currentLobby,gameStage->currentPlayer);
                showGame();
            }
            // Case: Load Question response ( 40101 | 40102 )
            else if (!strcmp(resultCode,UPDATE_GAME_CSTQUEST) | !strcmp(resultCode,UPDATE_GAME_MINEQUEST)){
                buffer[strlen(buffer)-1] = 0; // Must have , eliminate '\n' character at the end
                gameStage->currentGame.update_game_response(buffer,gameStage->currentLobby,gameStage->currentPlayer);
            }
            // Case: Attack castle SUCCESS / FAIL ( 40103 | 40105 )
            else if (!strcmp(resultCode,UPDATE_GAME_ATK_CST_R) | !strcmp(resultCode,UPDATE_GAME_ATK_CST_W)){
                gameStage->currentGame.update_game_response(buffer,gameStage->currentLobby,gameStage->currentPlayer);
                if (!strcmp(resultCode,UPDATE_GAME_ATK_CST_R)) {
                    gameStage->ui->listGameLog->insertItem(0,"[Game]: A player successfully attack a CASTLE!");
                } else {
                    gameStage->ui->listGameLog->insertItem(0,"[Game]: A player failed to attack a CASTLE!");
                }
                gameStage->updateDynamicUI();
            }
            // Case: Attack mine SUCCESS / FAIL ( 40104 | 40106 )
            else if (!strcmp(resultCode,UPDATE_GAME_ATK_MINE_R) | !strcmp(resultCode,UPDATE_GAME_ATK_MINE_W)){
                gameStage->currentGame.update_game_response(buffer,gameStage->currentLobby,gameStage->currentPlayer);
                if (!strcmp(resultCode,UPDATE_GAME_ATK_MINE_R)) {
                    gameStage->ui->listGameLog->insertItem(0,"[Game]: A player successfully attack a MINE!");
                } else {
                    gameStage->ui->listGameLog->insertItem(0,"[Game]: A player failed to attack a MINE!");
                }
                gameStage->updateDynamicUI();
            }
            // Case: Update buy weapon ( 40107 )
            else if (!strcmp(resultCode,UPDATE_GAME_BUY_WPN)){
                gameStage->currentGame.update_game_response(buffer,gameStage->currentLobby,gameStage->currentPlayer);
                gameStage->ui->listGameLog->insertItem(0,"[Game]: A player bought a weapon!");
                gameStage->updateDynamicUI();
            }
            // Case: Update buy wall ( 40108 )
            else if (!strcmp(resultCode,UPDATE_GAME_BUY_WALL)){
                gameStage->currentGame.update_game_response(buffer,gameStage->currentLobby,gameStage->currentPlayer);
                gameStage->ui->listGameLog->insertItem(0,"[Game]: A team built a wall!");
                gameStage->updateDynamicUI();
            }
            // Case: Update Game_cheat ( 40109 )
            if (!strcmp(resultCode,UPDATE_GAME_CHEAT)){
                gameStage->currentGame.update_game_response(buffer,currentLobby,gameStage->currentPlayer);
                gameStage->ui->listGameLog->insertItem(0,"[Game]: A cheater has cheated!");
                gameStage->updateDynamicUI();
            }
            // Case: Update Timely_update ( 400 )
            if (!strcmp(resultHeader,TIMELY_UPDATE)){
                gameStage->currentGame.update_timely_response(buffer);
                gameStage->ui->listGameLog->insertItem(0,"[Day "+ QString::number(gameStage->currentGame.day++) +
                                                       "]: Game has been updated! Let's check map and inventory.");
            }
            // Case: Update Game_over ( 40110 )
            if (!strcmp(resultCode,UPDATE_GAME_OVER)){

            }
        }

        // ERROR & OTHER CASE handle below

        // Ready_E response handle (200)
        if ( !strcmp(resultHeader,READY_PLAY) ){
            gameStage->currentPlayer.ready_response(buffer);
        }
        // Unready_E response handle (201)
        if ( !strcmp(resultHeader,UNREADY_PLAY) ){
            gameStage->currentPlayer.unready_response(buffer);
        }
        // StartGame_E response handle (202)
        if ( !strcmp(resultHeader,START_GAME) ){
            gameStage->currentLobby.start_game_response(buffer);
        }
        // Quit Game response handle (203)
        if (!strcmp(resultHeader,QUIT_LOBBY)){
            //Process quit response
            int isQuitSuccess = gameStage->currentLobby.quit_lobby_response(buffer);
            if ( isQuitSuccess ){
                gotoPreviousStage();
            }
        }
        // ChangeTeam_E response handle (204)
        if (!strcmp(resultHeader,CHANGE_TEAM) ){
            waitForChangeTeamResponse = false;
            gameStage->currentPlayer.change_team_response(buffer, decisionTeamChange);
        }
        // KICK_E response handle (205 and !20500)
        if (!strcmp(resultHeader,KICK) && strcmp(resultCode,KICK_SUCCESS) ){
            waitForKickResponse = false;
            gameStage->currentLobby.kick_response(buffer,decisionKickID);
        }
        // Being Kicked out response handle (20500)
        if (!strcmp(resultCode,KICK_SUCCESS)){
            QMessageBox::information(nullptr,"Oops","You have been kicked out!",0);
            gotoPreviousStage();
        }
        // Attack_Castle_E response handle (300)
        if (!strcmp(resultHeader,ATTACK_CASTLE)){
            gameStage->currentPlayer.attack_castle_response(buffer);
        }
        // Attack_Mine_E response handle (301)
        if (!strcmp(resultHeader,ATTACK_MINE)){
            gameStage->currentPlayer.attack_mine_response(buffer);
        }
        // Buy_Weapon_E response handle (302)
        if (!strcmp(resultHeader,BUY_WEAPON)){
            gameStage->currentPlayer.buy_weapon_response(buffer);
        }
        // Buy_Wall_E response handle (303)
        if (!strcmp(resultHeader,BUY_WALL)){
            gameStage->currentPlayer.buy_wall_response(buffer);
        }
        // Cheat_E response handle (304)
        if (!strcmp(resultHeader,CHEAT)){
            gameStage->currentPlayer.cheat_response(buffer);
        }
        // * Server disconnection detected handle
        if (!strcmp(resultCode,DISCONNECTED)){
            handleDisconnected();
        }

        // *  After handle a response, pop it out of queue
        if ( bufferQueue.empty() == false) {
            bufferQueue.pop();
        }
        // * And call updateUI
        updateUI();
    }
}

void StagePrepare::onReceive(char* buffer ){
    // When receive a response, add it to bufferQueue
    bufferQueue.push(buffer);
    runQueue();
}

void StagePrepare::on_actionQuit_Lobby_triggered()
{
    // On Quit Lobby Action
    QMessageBox::StandardButton isConfirm;
    QString quitQuestion = (roomState == UNREADY) ? "Quit current room?" : "Quit this game?";
    isConfirm = QMessageBox::question(this, "Confirmation", quitQuestion,QMessageBox::Yes|QMessageBox::No);
    if (isConfirm == QMessageBox::Yes) {
        //sending quit lobby request
        gameStage->currentLobby.quit_lobby_request(gameStage->clientSocket);
    }
}

void StagePrepare::on_btnStart_clicked()
{
    // Start button Clicked.
    if (roomState == UNREADY){
        QMessageBox::StandardButton isConfirm;
        isConfirm = QMessageBox::question(this, "Confirmation", "Start game?",QMessageBox::Yes|QMessageBox::No);
        if (isConfirm == QMessageBox::Yes) {
            //sending start game request
            gameStage->currentLobby.start_game_request(gameStage->clientSocket);
        }
    } else {
        gameStage->show();
    }
}

void StagePrepare::on_btnReady_clicked()
{
    // Send Ready Request
    QMessageBox::StandardButton isConfirm;
    isConfirm = QMessageBox::question(this, "Confirmation", "Ready to fight?",QMessageBox::Yes|QMessageBox::No);
    if (isConfirm == QMessageBox::Yes) {
        gameStage->currentPlayer.ready_request(this->gameStage->clientSocket);
    }
}

void StagePrepare::on_btnUnready_clicked()
{
    // Send Unready Request
    QMessageBox::StandardButton isConfirm;
    isConfirm = QMessageBox::question(this, "Confirmation", "Are you sure unready?",QMessageBox::Yes|QMessageBox::No);
    if (isConfirm == QMessageBox::Yes) {
        gameStage->currentPlayer.unready_request(this->gameStage->clientSocket);
    }
}

void StagePrepare::on_btnChangeTeam_clicked()
{
    // Send Change Team Request
    bool isConfirmed;
    decisionTeamChange = QInputDialog::getInt(this,0,"What team do you wanna join?",gameStage->currentLobby.team_number,1,gameStage->currentLobby.team_number,1,&isConfirmed,Qt::Popup) - 1;

    if (isConfirmed) {
        // Send change team request
        gameStage->currentPlayer.change_team_request(gameStage->clientSocket,decisionTeamChange);
        waitForChangeTeamResponse = true;
    }
}

void StagePrepare::on_btnKick_clicked()
{
    // Choose player to kick
    bool isConfirmed;
    decisionKickID = QInputDialog::getInt(this,0,"What player (ID) do you wanna kick?",0,0,gameStage->currentLobby.team_number*3,1,&isConfirmed,Qt::Popup);

    if (isConfirmed) {
        // Send Kick request
        gameStage->currentLobby.kick_request(gameStage->clientSocket,decisionKickID);
        waitForKickResponse = true;
    }
}

