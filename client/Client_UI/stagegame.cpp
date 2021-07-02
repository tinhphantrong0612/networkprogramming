#include "stagegame.h"
#include "ui_stagegame.h"
#include "util.h"
#include "qpixmap.h"
#include "qinputdialog.h"
#include "uitextconst.h"
#include "uitranslate.h"
#include "QTimer"

StageGame::StageGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StageGame)
{
    ui->setupUi(this);
    this->setWindowTitle("Game");
    setWindowFlags( Qt::MSWindowsFixedSizeDialogHint | Qt::Widget);
    statusBar()->setVisible(false);
    loadStaticUI();
}

StageGame::~StageGame()
{
    delete ui;
}

void StageGame::loadStaticUI(){
    // Load image assets one-time-only
    QPixmap imageCastle1(":/image/castle.png");
    QPixmap imageCastle2(":/image/castle1.png");
    QPixmap imageCastle3(":/image/castle2.png");
    QPixmap imageMine1(":/image/wagon1.png");
    QPixmap imageMine2(":/image/wagon2.png");
    QPixmap imageMine3(":/image/wagon3.png");
    QPixmap imageWood(":/image/wood.png");
    QPixmap imageStone(":/image/coal.png");
    QPixmap imageIron(":/image/iron.png");
    QPixmap imageFence(":/image/fence.png");
    QPixmap imageWoodWall(":/image/woodwall.png");
    QPixmap imageStoneWall(":/image/stonewall.png");
    QPixmap imageLegendWall(":/image/legendwall.png");
    QPixmap imageBallista(":/image/ballista.png");
    QPixmap imageCatapult(":/image/catapult.png");
    QPixmap imageCannon(":/image/cannon.png");
    QPixmap imageNothing(":/image/nothing.png");
    QPixmap imageGold(":/image/gold.png");

    ui->castle1->setPixmap(imageCastle1.scaled(128,128,Qt::KeepAspectRatio));
    ui->castle2->setPixmap(imageCastle2.scaled(128,128,Qt::KeepAspectRatio));
    ui->castle3->setPixmap(imageCastle3.scaled(128,128,Qt::KeepAspectRatio));
    ui->mine1->setPixmap(imageMine1.scaled(80,80,Qt::KeepAspectRatio));
    ui->mine2->setPixmap(imageMine3.scaled(80,80,Qt::KeepAspectRatio));
    ui->mine3->setPixmap(imageMine2.scaled(80,80,Qt::KeepAspectRatio));
    ui->mine4->setPixmap(imageMine2.scaled(80,80,Qt::KeepAspectRatio));
    ui->mine5->setPixmap(imageMine3.scaled(80,80,Qt::KeepAspectRatio));
    ui->mine6->setPixmap(imageMine1.scaled(80,80,Qt::KeepAspectRatio));
    ui->imgWood->setPixmap(imageWood.scaled(64,64,Qt::KeepAspectRatio));
    ui->imgStone->setPixmap(imageStone.scaled(64,64,Qt::KeepAspectRatio));
    ui->imgIron->setPixmap(imageIron.scaled(64,64,Qt::KeepAspectRatio));
    ui->imgGold->setPixmap(imageGold.scaled(80,80,Qt::KeepAspectRatio));
    ui->imageShop_fence->setPixmap(imageFence.scaled(80,80,Qt::KeepAspectRatio));
    ui->imageShop_woodwall->setPixmap(imageWoodWall.scaled(80,80,Qt::KeepAspectRatio));
    ui->imageShop_stonewall->setPixmap(imageStoneWall.scaled(80,80,Qt::KeepAspectRatio));
    ui->imageShop_legendwall->setPixmap(imageLegendWall.scaled(80,80,Qt::KeepAspectRatio));
    ui->imageShop_ballista->setPixmap(imageBallista.scaled(80,80,Qt::KeepAspectRatio));
    ui->imageShop_catapult->setPixmap(imageCatapult.scaled(80,80,Qt::KeepAspectRatio));
    ui->imageShop_cannon->setPixmap(imageCannon.scaled(80,80,Qt::KeepAspectRatio));
    ui->equipment_atk_1->setPixmap(imageNothing.scaled(80,80,Qt::KeepAspectRatio));
    ui->equipment_atk_2->setPixmap(imageNothing.scaled(80,80,Qt::KeepAspectRatio));
    ui->equipment_atk_3->setPixmap(imageNothing.scaled(80,80,Qt::KeepAspectRatio));
    ui->equipment_atk_4->setPixmap(imageNothing.scaled(80,80,Qt::KeepAspectRatio));

    ui->listGameLog->setWordWrap(true);
}

void StageGame::loadPlayers(){
    ui->labelGreet->setText("Welcome, [ " + QString::fromLocal8Bit(this->currentPlayer.username) + " ] , be brave !");
    ui->listPlayer->clear();
    // load players list from Lobby
    for ( int i = 0; i < currentLobby.player_number ; i++ ){
        ui->listPlayer->addItem("[ID: " + QString::number(currentLobby.players[i].id) + "]" +
                                " [Name: " + QString::fromLocal8Bit(currentLobby.players[i].username) + "]"+
                                " [Team:" + QString::number(currentLobby.players[i].team_id+1) + "]");
    }
}

void StageGame::informRule(){
    // Inform rules
    // This is also first message of the game
    QMessageBox::information(nullptr,"Game rules",GAME_RULES,0);
}

void StageGame::updateDynamicUI(){
    qDebug() << "Updated Dynamic GUI" ;
    int myTeam = currentPlayer.team_id;

    //Update MAP : Castles state / Mine resources
    ui->labelStatusCst1->setText(getOccupiedText(currentGame.castles[0].occupied_by));
    ui->labelStatusCst2->setText(getOccupiedText(currentGame.castles[1].occupied_by));
    ui->labelStatusCst3->setText(getOccupiedText(currentGame.castles[2].occupied_by));
    ui->labelWallCst1->setText(getWallName(currentGame.castles[0].wall.type));
    ui->labelWallCst2->setText(getWallName(currentGame.castles[1].wall.type));
    ui->labelWallCst3->setText(getWallName(currentGame.castles[2].wall.type));
    ui->labelResMine1->setText(getMineResourceText(currentGame.mines[0]));
    ui->labelResMine2->setText(getMineResourceText(currentGame.mines[1]));
    ui->labelResMine3->setText(getMineResourceText(currentGame.mines[2]));
    ui->labelResMine4->setText(getMineResourceText(currentGame.mines[3]));
    ui->labelResMine5->setText(getMineResourceText(currentGame.mines[4]));
    ui->labelResMine6->setText(getMineResourceText(currentGame.mines[5]));
    ui->labelToughCst1->setText( "DEF: " + QString::number(currentGame.castles[0].wall.defense) );
    ui->labelToughCst2->setText( "DEF: " + QString::number(currentGame.castles[1].wall.defense) );
    ui->labelToughCst3->setText( "DEF: " + QString::number(currentGame.castles[2].wall.defense) );
    ui->labelAtk_team1->setText( "POWER: " + QString::number(currentGame.teams[0].weapon.attack));
    ui->labelAtk_team2->setText( "POWER: " + QString::number(currentGame.teams[1].weapon.attack));
    ui->labelAtk_team3->setText( "POWER: " + QString::number(currentGame.teams[2].weapon.attack));
    ui->labelAtk_team4->setText( "POWER: " + QString::number(currentGame.teams[3].weapon.attack));

    //Update INVENTORY : resources, equipment
    ui->labelWoodResource->setText("x " + QString::number(currentGame.teams[myTeam].wood));
    ui->labelStoneResource->setText("x " + QString::number(currentGame.teams[myTeam].stone));
    ui->labelIronResource->setText("x " + QString::number(currentGame.teams[myTeam].iron));
    ui->labelGoldResource->setText("x " + QString::number(currentGame.teams[myTeam].gold));
    ui->equipment_atk_1->setPixmap(getWeaponPixMap(currentGame.teams[0].weapon.type).scaled(80,80,Qt::KeepAspectRatio));
    ui->equipment_atk_2->setPixmap(getWeaponPixMap(currentGame.teams[1].weapon.type).scaled(80,80,Qt::KeepAspectRatio));
    ui->equipment_atk_3->setPixmap(getWeaponPixMap(currentGame.teams[2].weapon.type).scaled(80,80,Qt::KeepAspectRatio));
    ui->equipment_atk_4->setPixmap(getWeaponPixMap(currentGame.teams[3].weapon.type).scaled(80,80,Qt::KeepAspectRatio));

    //Update Shop resource label
    ui->labelResourceShop->setText("You have: " + QString::number(currentGame.teams[myTeam].wood) + "W, " +
                                   QString::number(currentGame.teams[myTeam].stone) + "S, " +
                                   QString::number(currentGame.teams[myTeam].iron)+ "I");
}

void StageGame::on_actionRules_triggered()
{
    //Call for informRule()
    this->informRule();
}

void StageGame::on_buttonAttack_clicked()
{
    //Attack action handle
    bool isStep1Confirmed = false, isStep2Confirmed = false;
    int targetID = -1, targetResType = -1, answerID = -1;
    int targetType = QInputDialog::getInt(this,"Step 1",TEXT_ATTACK_STEP1,1,0,1,1,&isStep1Confirmed,Qt::Dialog);
    if (targetType == 1 && isStep1Confirmed ){
        // Chose "Attack mine"
        // * Get mine ID
        targetID = QInputDialog::getInt(this,"Step 2",TEXT_ATTACK_STEP2,1,1,6,1,&isStep2Confirmed,Qt::Dialog) - 1;
        // * Get mine resource type
        if ( isStep2Confirmed ){
            targetResType = QInputDialog::getInt(this,"Step 2.1",TEXT_ATTACK_STEP2_MINE,1,1,3,1,&isStep2Confirmed,Qt::Dialog) - 1;
        }
    } else if (targetType == 0 && isStep1Confirmed) {
        //Chose "Attack castle"
        // * Get castle ID
        targetID = QInputDialog::getInt(this,"Step 2",TEXT_ATTACK_STEP2,1,1,3,1,&isStep2Confirmed,Qt::Dialog) - 1;
    }
    // Double check
    if (isStep2Confirmed) {
        QMessageBox::StandardButton isStep3Confirmed;
        isStep3Confirmed = QMessageBox::question(this, "Confirmation", TEXT_ATTACK_STEP3 ,QMessageBox::Yes|QMessageBox::No);
        if (isStep3Confirmed == QMessageBox::Yes) {
            if (targetType == 1){
                // Show attack Mine Question
                Question currentQuestion = currentGame.mines[targetID].question[targetResType];
                answerID = QInputDialog::getInt(this,"Answer question",TEXT_RULES_QUESTION + getQuestText(currentQuestion),1,1,4,1,0,Qt::Dialog) - 1;
                // Send attack request
                currentPlayer.attack_mine_request(clientSocket,targetID,targetResType,currentQuestion.id,answerID);
            } else {
                // Show attack Castle Question
                Question currentQuestion = currentGame.castles[targetID].question;
                answerID = QInputDialog::getInt(this,"Answer question",TEXT_RULES_QUESTION + getQuestText(currentQuestion),1,1,4,1,0,Qt::Dialog) - 1;
                currentPlayer.attack_castle_request(clientSocket,targetID,currentQuestion.id,answerID);
            }
            // Set cooldown on attack command
            QTimer::singleShot(0, [&](){
                ui->buttonAttack->setText("Cooldown");
                ui->buttonAttack->setDisabled(true);
            });
            QTimer::singleShot(COOLDOWN_INTERVAL, [&](){
                ui->buttonAttack->setText("Attack");
                ui->buttonAttack->setDisabled(false);
            });
        }
    }
}

void StageGame::on_buttonCheat_clicked()
{
    // Cheat command here
    // Ask for confirmation
    QMessageBox::StandardButton isCheatConfirmed;
    isCheatConfirmed = QMessageBox::question(this, "Confirmation", "Are you sure cheating?" ,QMessageBox::Yes|QMessageBox::No);
    if (isCheatConfirmed == QMessageBox::Yes){
        // Send Cheat request
        currentPlayer.cheat_request(clientSocket);
        ui->listGameLog->insertItem(0,"[You] Sent cheat request.");
    }
}

void StageGame::on_buttonBuyItem_clicked()
{
    // First choose item to buy
    bool isBuyConfirmed = false, isAnyCastleChose = false;
    int itemType = -1; // 0: WPN ; 1: WALL
    int choseCastleID = -1; // Get castle's ID that equips wall
    int itemID = QInputDialog::getInt(this,"Step 1",TEXT_BUY_ITEM,7,1,7,1,&isBuyConfirmed,Qt::Dialog);
    if (isBuyConfirmed){
        if ( itemID < 4 && itemID > 0) {
            itemType = 0; // Weapon type
        }
        else {
            itemType = 1; // Wall ID
            itemID -= 3; // Get wall ID
            // Ask for target castle
            choseCastleID = QInputDialog::getInt(this,"Step 2",TEXT_BUY_WALL,1,1,3,1,&isAnyCastleChose,Qt::Dialog) - 1;
        }
    }
    if (itemType == 0){
        //Send buy Weapon request
        currentPlayer.buy_weapon_request(clientSocket,itemID);
         ui->listGameLog->insertItem(0,"[You] Sent buy weapon request.");
    }
    else if (itemType == 1 && isAnyCastleChose) {
        //Send buy Wall request
        currentPlayer.buy_wall_request(clientSocket,itemID,choseCastleID);
        ui->listGameLog->insertItem(0,"[You] Sent build wall request.");
    }
}


void StageGame::on_actionQuit_Game_triggered()
{
    // On Quit Lobby Action
    QMessageBox::StandardButton isConfirm;
    isConfirm = QMessageBox::question(this, "Confirmation", "Quit this game?",QMessageBox::Yes|QMessageBox::No);
    if (isConfirm == QMessageBox::Yes) {
        //sending quit lobby request
        this->currentLobby.quit_lobby_request(this->clientSocket);
    }
}

