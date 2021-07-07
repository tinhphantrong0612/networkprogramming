#include "stagewaitingroom.h"
#include "ui_stagewaitingroom.h"

#include "stageprepare.h"
#include "stagelogin.h"
#include "qmessagebox.h"
#include "qinputdialog.h"

#include "util.h"

StageWaitingRoom::StageWaitingRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StageWaitingRoom)
{
    //UI initialize
    ui->setupUi(this);
    this->setWindowTitle("Waiting room");
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    statusBar()->setVisible(false);
}

StageWaitingRoom::~StageWaitingRoom()
{
    delete ui;
}

void StageWaitingRoom::initializeStage(Socket* socket,User* user){
    // binding Waiting Room's attributes
    bindSocket(&clientSocket,socket);
    bindUser(&clientUser,user);

    //Set initalize state for data inside StageWaitingRoom
    char myUsername[USERNAME_LEN];
    strcpy_s(myUsername,USERNAME_LEN,this->clientUser.username);
    ui->labelWelcome->setText("Hello, " + QString(myUsername));

    //Update list room on first run
    on_btnRefresh_clicked();
}

void StageWaitingRoom::on_btnCreate_clicked()
{
    // Button "create" clicked handle
    // Popup stage "Create Room".
    bool isConfirmed = false;
    int teams = QInputDialog::getInt(this,"Team number select","Input number of teams in the game:",4,1,4,1,&isConfirmed,Qt::Popup);

    if (isConfirmed){
        Player currentPlayer;
        // Sending create game message
        myLobby.create_lobby_request(clientSocket,teams);

        char buff[BUFF_SIZE];
        // Wait to receive response from server
        //        Get game ID for binding later
        if (clientSocket.Receive(buff)) {
            currentPlayer = myLobby.create_lobby_response(buff,clientUser.username);
            if ((myLobby.id != 0) && (strcmp(currentPlayer.username,""))){
                 myLobby.team_number = teams;
                 //Bind game ID to Stage "Prepare" and initialize
                 StagePrepare *prepareStage = new StagePrepare();
                 prepareStage->initializeStage(&clientSocket,&myLobby,&currentPlayer,&clientUser);
                 prepareStage->updateUI();
                 prepareStage->show();
                 this->close();
            }
        }
    }
}

void StageWaitingRoom::on_btnJoin_clicked()
{
    // Button "join" clicked handle
    // Sending request join a room. If a room is full, qmessage and do nothing

    long long gameIDSelected ;
    int teamAmountSelected ;
    char *next_token;

    if ( ui->listLobby->currentItem() == nullptr ){
        QMessageBox::information(this,"Wrong decision","Please choose a game inside list lobbys",0);
    }
    else {
        QByteArray infoByte =  ui->listLobby->currentItem()->text().toLocal8Bit();
        char *lobbyInfo = infoByte.data();
        char *token = strtok_s(lobbyInfo, DELIM_REQ_RES, &next_token);
        // get selected ROOM ID
        token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
        gameIDSelected = _atoi64(token);
        // get selected TEAM NUMBER
        token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
        token = strtok_s(NULL, DELIM_REQ_RES, &next_token);
        teamAmountSelected = atoi(token);

        // Ask player what team to join
        bool isConfirmed = false;
        int decisionTeam = QInputDialog::getInt(this,0,"What team do you wanna join?",teamAmountSelected,1,teamAmountSelected,1,&isConfirmed,Qt::Popup) - 1 ;
        if ( isConfirmed ) {
            //send join_lobby request
            myLobby.join_lobby_request(clientSocket,gameIDSelected,decisionTeam);
            //Wait for response
            char buff[BUFF_SIZE], updateLobbyBuff[BUFF_SIZE];
            if ( clientSocket.Receive(buff) ){
                Player player = myLobby.join_lobby_response(buff,clientUser.username,decisionTeam,teamAmountSelected);
                if ( strcmp(player.username,"") ){
                    // If id of player != 0 that's mean he joined sucessfully
                    myLobby.id = gameIDSelected;
                    myLobby.team_number = teamAmountSelected;

                    //Receive update lobby response ( 40201 ) after joined ( 10500# )
                    if ( clientSocket.Receive(updateLobbyBuff) ){
                        myLobby.update_lobby_response(updateLobbyBuff);
                    }
                    //Bind game ID to Stage "Prepare" and initialize
                    StagePrepare *prepareStage = new StagePrepare();
                    prepareStage->initializeStage(&clientSocket,&myLobby,&player,&clientUser);
                    prepareStage->show();
                    this->close();
                }
            }
        }
    }
}

void StageWaitingRoom::on_btnRefresh_clicked()
{
    // Button refresh clicked:
    // Sending request to refresh room list
    myLobby.get_lobby_request(clientSocket);

    //Waiting to receive response
    char buff[BUFF_SIZE];
    bool isUpdate = 0 ;
    if ( this->clientSocket.Receive(buff) ){
        isUpdate = 1;
        myLobby.get_lobby_response(buff,this->listLobby,lobbySize);
    }
    if ( isUpdate ){
        ui->listLobby->clear();
        for ( int i = 0 ; i < lobbySize ; i++) {
            int count = 0;
            for ( int j = 0 ; j < MAX_PLAYER_OF_TEAM * listLobby[i].team_number ; j++ ){
                if ( listLobby[i].team_players[j] != -1 ) count++;
            }
            ui->listLobby->addItem("Room ID: #" + QString::number(listLobby[i].id)
            + "# | Teams: #" + QString::number(listLobby[i].team_number) + "#" +
            " | Current: " + QString::number(count) + " player");
        }
    }
}

void StageWaitingRoom::on_actionLogout_triggered()
{
    //Go back to previous screen with this Socket only

    clientUser.logout_request(clientSocket);
    char buff[BUFF_SIZE];
    if ( clientSocket.Receive(buff) ){
        clientUser.logout_response(buff);
    }

    if (clientUser.state == USER_NONAUTH){
        StageLogin *w = new StageLogin(nullptr);
        w->initializeStage(&clientSocket,1);
        w->show();
        this->close();
    }
}

