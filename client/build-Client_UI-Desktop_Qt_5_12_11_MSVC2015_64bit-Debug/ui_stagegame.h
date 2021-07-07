/********************************************************************************
** Form generated from reading UI file 'stagegame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGEGAME_H
#define UI_STAGEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StageGame
{
public:
    QAction *actionRules;
    QAction *actionQuit_Game;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *mapTabPage;
    QLabel *castle1;
    QLabel *castle2;
    QLabel *castle3;
    QLabel *mine1;
    QLabel *mine4;
    QLabel *mine2;
    QLabel *mine5;
    QLabel *mine6;
    QLabel *mine3;
    QLabel *textCastle1;
    QLabel *textCastle2;
    QLabel *textCastle3;
    QLabel *textMine1;
    QLabel *textMine4;
    QLabel *textMine6;
    QLabel *textMine3;
    QLabel *textMine5;
    QLabel *textMine2;
    QLabel *labelStatusCst1;
    QLabel *labelStatusCst2;
    QLabel *labelStatusCst3;
    QLabel *labelWallCst1;
    QLabel *labelWallCst2;
    QLabel *labelWallCst3;
    QLabel *labelResMine1;
    QLabel *labelResMine2;
    QLabel *labelResMine3;
    QLabel *labelResMine4;
    QLabel *labelResMine5;
    QLabel *labelResMine6;
    QLabel *labelToughCst1;
    QLabel *labelToughCst2;
    QLabel *labelToughCst3;
    QWidget *inventoryTabPage;
    QLabel *text2_1;
    QLabel *text2_3;
    QLabel *miniText2_2;
    QFrame *line2_1;
    QFrame *line2_3;
    QLabel *imgWood;
    QLabel *imgStone;
    QLabel *imgIron;
    QLabel *labelWoodResource;
    QLabel *labelStoneResource;
    QLabel *labelIronResource;
    QLabel *equipment_atk_1;
    QLabel *equipment_atk_2;
    QLabel *equipment_atk_3;
    QLabel *equipment_atk_4;
    QPushButton *buttonAttack;
    QLabel *text2_4;
    QLabel *miniText2_3;
    QFrame *line2_4;
    QPushButton *buttonCheat;
    QLabel *textTeam1Weapon;
    QLabel *textTeam4Weapon;
    QLabel *textTeam2Weapon;
    QLabel *textTeam3Weapon;
    QLabel *labelAtk_team1;
    QLabel *labelAtk_team2;
    QLabel *labelAtk_team3;
    QLabel *labelAtk_team4;
    QLabel *imgGold;
    QLabel *labelGoldResource;
    QWidget *shopTabPage;
    QFrame *line3_0;
    QLabel *text3_1;
    QLabel *text3_2;
    QFrame *line3_1;
    QFrame *line3_2;
    QLabel *miniText3_1;
    QLabel *miniText3_2;
    QLabel *imageShop_fence;
    QLabel *imageShop_woodwall;
    QLabel *imageShop_stonewall;
    QLabel *imageShop_legendwall;
    QLabel *imageShop_ballista;
    QLabel *imageShop_catapult;
    QLabel *imageShop_cannon;
    QLabel *textShop_1;
    QLabel *textShop_2;
    QLabel *textShop_3;
    QLabel *textShop_4;
    QLabel *textShop_5;
    QLabel *textShop_6;
    QLabel *textShop_7;
    QLabel *miniTextShop_1;
    QLabel *miniTextShop_2;
    QLabel *miniTextShop_3;
    QLabel *miniTextShop_4;
    QLabel *miniTextShop_5;
    QLabel *miniTextShop_6;
    QLabel *miniTextShop_7;
    QFrame *line3_3;
    QPushButton *buttonBuyItem;
    QLabel *labelResourceShop;
    QWidget *rankingTab;
    QLabel *text1;
    QLabel *text2;
    QLabel *text3;
    QPushButton *btnContinue;
    QLabel *imgGold1;
    QLabel *labelAsset1;
    QLabel *labelAsset2;
    QLabel *imgGold2;
    QLabel *label1st;
    QLabel *label2nd;
    QListWidget *listGameLog;
    QLabel *text0_1;
    QLabel *labelGreet;
    QFrame *line_greet;
    QLabel *text0_2;
    QListWidget *listPlayer;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuHelp;

    void setupUi(QMainWindow *StageGame)
    {
        if (StageGame->objectName().isEmpty())
            StageGame->setObjectName(QString::fromUtf8("StageGame"));
        StageGame->resize(960, 640);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        StageGame->setFont(font);
        StageGame->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"        background-color: #e6ebff;\n"
"}\n"
"\n"
"QPushButton {\n"
"        background-color: #00cccc;\n"
"        color: #fff7e6 ;\n"
"        border-radius: 15;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"        color: #fff7e6 ;\n"
"        background-color: #002e4d;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"        color: #fff7e6 ;\n"
"        background-color: #000066;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"        color: #ffff66;\n"
"        background-color: #ffff66;\n"
"}\n"
"\n"
"QLineEdit {\n"
"        background-color: #b3ecff;\n"
"        border-radius: 15;\n"
"        padding-left: 10;\n"
"        color: #0000b3;\n"
"        font-family : roboto;\n"
"}\n"
"\n"
"QLabel {\n"
"        color: #005c99;\n"
"}\n"
"\n"
"QListWidget {\n"
"        background-color: #ccffcc;\n"
"		font-family: Roboto;\n"
"		font-size: 9;\n"
"		border-radius: 10 ;\n"
"        padding-left: 5;\n"
"        padding-top: 5;\n"
"}\n"
"\n"
"/*Copy tren mang cho cai listwidget nhin sang chanh hon*/\n"
"QListView::item"
                        ":alternate {\n"
"    background: #EEEEEE;\n"
"}\n"
"\n"
"QListView::item:selected:!active {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #ABAFE5, stop: 1 #8588B2);\n"
"}\n"
"\n"
"QListView::item:selected:active {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6a6ea9, stop: 1 #888dd9);\n"
"}\n"
"\n"
"QListView::item:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #FAFBFE, stop: 1 #DCDEF1);\n"
"}"));
        actionRules = new QAction(StageGame);
        actionRules->setObjectName(QString::fromUtf8("actionRules"));
        actionQuit_Game = new QAction(StageGame);
        actionQuit_Game->setObjectName(QString::fromUtf8("actionQuit_Game"));
        centralwidget = new QWidget(StageGame);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(320, 0, 630, 600));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        tabWidget->setFont(font1);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget {\n"
"        background-color: #ccffdd;\n"
"}\n"
"\n"
"QWidget {\n"
"        background-color: #ccffdd;\n"
"}\n"
"\n"
"QPushButton {\n"
"        background-color: #00cccc;\n"
"        color: #fff7e6 ;\n"
"        border-radius: 25;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"        color: #fff7e6 ;\n"
"        background-color: #002e4d;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"        color: #fff7e6 ;\n"
"        background-color: #000066;\n"
"}\n"
"\n"
"QPushButton: disabled {\n"
"		background-color:#ff6666;\n"
"}\n"
"\n"
"QWidget#mapTabPage {\n"
"        background-image:\n"
"}"));
        tabWidget->setTabsClosable(false);
        mapTabPage = new QWidget();
        mapTabPage->setObjectName(QString::fromUtf8("mapTabPage"));
        mapTabPage->setEnabled(true);
        mapTabPage->setStyleSheet(QString::fromUtf8(""));
        castle1 = new QLabel(mapTabPage);
        castle1->setObjectName(QString::fromUtf8("castle1"));
        castle1->setGeometry(QRect(80, 10, 128, 128));
        castle1->setStyleSheet(QString::fromUtf8(""));
        castle1->setAlignment(Qt::AlignCenter);
        castle2 = new QLabel(mapTabPage);
        castle2->setObjectName(QString::fromUtf8("castle2"));
        castle2->setGeometry(QRect(251, 10, 128, 128));
        castle2->setStyleSheet(QString::fromUtf8(""));
        castle2->setAlignment(Qt::AlignCenter);
        castle3 = new QLabel(mapTabPage);
        castle3->setObjectName(QString::fromUtf8("castle3"));
        castle3->setGeometry(QRect(422, 10, 128, 128));
        castle3->setStyleSheet(QString::fromUtf8(""));
        castle3->setAlignment(Qt::AlignCenter);
        mine1 = new QLabel(mapTabPage);
        mine1->setObjectName(QString::fromUtf8("mine1"));
        mine1->setGeometry(QRect(40, 220, 128, 128));
        mine1->setStyleSheet(QString::fromUtf8(""));
        mine1->setAlignment(Qt::AlignCenter);
        mine4 = new QLabel(mapTabPage);
        mine4->setObjectName(QString::fromUtf8("mine4"));
        mine4->setGeometry(QRect(40, 380, 128, 128));
        mine4->setStyleSheet(QString::fromUtf8(""));
        mine4->setAlignment(Qt::AlignCenter);
        mine2 = new QLabel(mapTabPage);
        mine2->setObjectName(QString::fromUtf8("mine2"));
        mine2->setGeometry(QRect(251, 220, 128, 128));
        mine2->setStyleSheet(QString::fromUtf8(""));
        mine2->setAlignment(Qt::AlignCenter);
        mine5 = new QLabel(mapTabPage);
        mine5->setObjectName(QString::fromUtf8("mine5"));
        mine5->setGeometry(QRect(251, 380, 128, 128));
        mine5->setStyleSheet(QString::fromUtf8(""));
        mine5->setAlignment(Qt::AlignCenter);
        mine6 = new QLabel(mapTabPage);
        mine6->setObjectName(QString::fromUtf8("mine6"));
        mine6->setGeometry(QRect(462, 380, 128, 128));
        mine6->setStyleSheet(QString::fromUtf8(""));
        mine6->setAlignment(Qt::AlignCenter);
        mine3 = new QLabel(mapTabPage);
        mine3->setObjectName(QString::fromUtf8("mine3"));
        mine3->setGeometry(QRect(462, 220, 128, 128));
        mine3->setStyleSheet(QString::fromUtf8(""));
        mine3->setAlignment(Qt::AlignCenter);
        textCastle1 = new QLabel(mapTabPage);
        textCastle1->setObjectName(QString::fromUtf8("textCastle1"));
        textCastle1->setGeometry(QRect(80, 138, 128, 25));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(9);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        textCastle1->setFont(font2);
        textCastle1->setAlignment(Qt::AlignCenter);
        textCastle2 = new QLabel(mapTabPage);
        textCastle2->setObjectName(QString::fromUtf8("textCastle2"));
        textCastle2->setGeometry(QRect(251, 138, 128, 25));
        textCastle2->setFont(font2);
        textCastle2->setAlignment(Qt::AlignCenter);
        textCastle3 = new QLabel(mapTabPage);
        textCastle3->setObjectName(QString::fromUtf8("textCastle3"));
        textCastle3->setGeometry(QRect(422, 138, 128, 25));
        textCastle3->setFont(font2);
        textCastle3->setAlignment(Qt::AlignCenter);
        textMine1 = new QLabel(mapTabPage);
        textMine1->setObjectName(QString::fromUtf8("textMine1"));
        textMine1->setGeometry(QRect(40, 325, 128, 25));
        textMine1->setFont(font2);
        textMine1->setAlignment(Qt::AlignCenter);
        textMine4 = new QLabel(mapTabPage);
        textMine4->setObjectName(QString::fromUtf8("textMine4"));
        textMine4->setGeometry(QRect(40, 498, 128, 25));
        textMine4->setFont(font2);
        textMine4->setAlignment(Qt::AlignCenter);
        textMine6 = new QLabel(mapTabPage);
        textMine6->setObjectName(QString::fromUtf8("textMine6"));
        textMine6->setGeometry(QRect(462, 498, 128, 25));
        textMine6->setFont(font2);
        textMine6->setAlignment(Qt::AlignCenter);
        textMine3 = new QLabel(mapTabPage);
        textMine3->setObjectName(QString::fromUtf8("textMine3"));
        textMine3->setGeometry(QRect(462, 325, 128, 25));
        textMine3->setFont(font2);
        textMine3->setAlignment(Qt::AlignCenter);
        textMine5 = new QLabel(mapTabPage);
        textMine5->setObjectName(QString::fromUtf8("textMine5"));
        textMine5->setGeometry(QRect(251, 498, 128, 25));
        textMine5->setFont(font2);
        textMine5->setAlignment(Qt::AlignCenter);
        textMine2 = new QLabel(mapTabPage);
        textMine2->setObjectName(QString::fromUtf8("textMine2"));
        textMine2->setGeometry(QRect(251, 325, 128, 25));
        textMine2->setFont(font2);
        textMine2->setAlignment(Qt::AlignCenter);
        labelStatusCst1 = new QLabel(mapTabPage);
        labelStatusCst1->setObjectName(QString::fromUtf8("labelStatusCst1"));
        labelStatusCst1->setGeometry(QRect(80, 163, 128, 25));
        labelStatusCst1->setFont(font2);
        labelStatusCst1->setAlignment(Qt::AlignCenter);
        labelStatusCst2 = new QLabel(mapTabPage);
        labelStatusCst2->setObjectName(QString::fromUtf8("labelStatusCst2"));
        labelStatusCst2->setGeometry(QRect(251, 163, 128, 25));
        labelStatusCst2->setFont(font2);
        labelStatusCst2->setAlignment(Qt::AlignCenter);
        labelStatusCst3 = new QLabel(mapTabPage);
        labelStatusCst3->setObjectName(QString::fromUtf8("labelStatusCst3"));
        labelStatusCst3->setGeometry(QRect(422, 163, 128, 25));
        labelStatusCst3->setFont(font2);
        labelStatusCst3->setAlignment(Qt::AlignCenter);
        labelWallCst1 = new QLabel(mapTabPage);
        labelWallCst1->setObjectName(QString::fromUtf8("labelWallCst1"));
        labelWallCst1->setGeometry(QRect(80, 188, 128, 25));
        labelWallCst1->setFont(font2);
        labelWallCst1->setAlignment(Qt::AlignCenter);
        labelWallCst2 = new QLabel(mapTabPage);
        labelWallCst2->setObjectName(QString::fromUtf8("labelWallCst2"));
        labelWallCst2->setGeometry(QRect(251, 188, 128, 25));
        labelWallCst2->setFont(font2);
        labelWallCst2->setAlignment(Qt::AlignCenter);
        labelWallCst3 = new QLabel(mapTabPage);
        labelWallCst3->setObjectName(QString::fromUtf8("labelWallCst3"));
        labelWallCst3->setGeometry(QRect(422, 188, 128, 25));
        labelWallCst3->setFont(font2);
        labelWallCst3->setAlignment(Qt::AlignCenter);
        labelResMine1 = new QLabel(mapTabPage);
        labelResMine1->setObjectName(QString::fromUtf8("labelResMine1"));
        labelResMine1->setGeometry(QRect(30, 350, 148, 25));
        labelResMine1->setFont(font2);
        labelResMine1->setAlignment(Qt::AlignCenter);
        labelResMine2 = new QLabel(mapTabPage);
        labelResMine2->setObjectName(QString::fromUtf8("labelResMine2"));
        labelResMine2->setGeometry(QRect(241, 350, 148, 25));
        labelResMine2->setFont(font2);
        labelResMine2->setAlignment(Qt::AlignCenter);
        labelResMine3 = new QLabel(mapTabPage);
        labelResMine3->setObjectName(QString::fromUtf8("labelResMine3"));
        labelResMine3->setGeometry(QRect(452, 350, 148, 25));
        labelResMine3->setFont(font2);
        labelResMine3->setAlignment(Qt::AlignCenter);
        labelResMine4 = new QLabel(mapTabPage);
        labelResMine4->setObjectName(QString::fromUtf8("labelResMine4"));
        labelResMine4->setGeometry(QRect(30, 523, 148, 25));
        labelResMine4->setFont(font2);
        labelResMine4->setAlignment(Qt::AlignCenter);
        labelResMine5 = new QLabel(mapTabPage);
        labelResMine5->setObjectName(QString::fromUtf8("labelResMine5"));
        labelResMine5->setGeometry(QRect(241, 523, 148, 25));
        labelResMine5->setFont(font2);
        labelResMine5->setAlignment(Qt::AlignCenter);
        labelResMine6 = new QLabel(mapTabPage);
        labelResMine6->setObjectName(QString::fromUtf8("labelResMine6"));
        labelResMine6->setGeometry(QRect(452, 523, 148, 25));
        labelResMine6->setFont(font2);
        labelResMine6->setAlignment(Qt::AlignCenter);
        labelToughCst1 = new QLabel(mapTabPage);
        labelToughCst1->setObjectName(QString::fromUtf8("labelToughCst1"));
        labelToughCst1->setGeometry(QRect(80, 213, 128, 25));
        labelToughCst1->setFont(font2);
        labelToughCst1->setAlignment(Qt::AlignCenter);
        labelToughCst2 = new QLabel(mapTabPage);
        labelToughCst2->setObjectName(QString::fromUtf8("labelToughCst2"));
        labelToughCst2->setGeometry(QRect(251, 213, 128, 25));
        labelToughCst2->setFont(font2);
        labelToughCst2->setAlignment(Qt::AlignCenter);
        labelToughCst3 = new QLabel(mapTabPage);
        labelToughCst3->setObjectName(QString::fromUtf8("labelToughCst3"));
        labelToughCst3->setGeometry(QRect(422, 213, 128, 25));
        labelToughCst3->setFont(font2);
        labelToughCst3->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(mapTabPage, QString());
        inventoryTabPage = new QWidget();
        inventoryTabPage->setObjectName(QString::fromUtf8("inventoryTabPage"));
        text2_1 = new QLabel(inventoryTabPage);
        text2_1->setObjectName(QString::fromUtf8("text2_1"));
        text2_1->setGeometry(QRect(40, 20, 150, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        text2_1->setFont(font3);
        text2_3 = new QLabel(inventoryTabPage);
        text2_3->setObjectName(QString::fromUtf8("text2_3"));
        text2_3->setGeometry(QRect(40, 180, 180, 30));
        text2_3->setFont(font3);
        miniText2_2 = new QLabel(inventoryTabPage);
        miniText2_2->setObjectName(QString::fromUtf8("miniText2_2"));
        miniText2_2->setGeometry(QRect(40, 210, 451, 30));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto"));
        font4.setPointSize(9);
        font4.setItalic(true);
        miniText2_2->setFont(font4);
        line2_1 = new QFrame(inventoryTabPage);
        line2_1->setObjectName(QString::fromUtf8("line2_1"));
        line2_1->setGeometry(QRect(40, 55, 540, 3));
        line2_1->setFrameShape(QFrame::HLine);
        line2_1->setFrameShadow(QFrame::Sunken);
        line2_3 = new QFrame(inventoryTabPage);
        line2_3->setObjectName(QString::fromUtf8("line2_3"));
        line2_3->setGeometry(QRect(40, 240, 540, 3));
        line2_3->setFrameShape(QFrame::HLine);
        line2_3->setFrameShadow(QFrame::Sunken);
        imgWood = new QLabel(inventoryTabPage);
        imgWood->setObjectName(QString::fromUtf8("imgWood"));
        imgWood->setGeometry(QRect(40, 70, 80, 80));
        imgWood->setStyleSheet(QString::fromUtf8(""));
        imgWood->setAlignment(Qt::AlignCenter);
        imgStone = new QLabel(inventoryTabPage);
        imgStone->setObjectName(QString::fromUtf8("imgStone"));
        imgStone->setGeometry(QRect(190, 70, 80, 80));
        imgStone->setStyleSheet(QString::fromUtf8(""));
        imgStone->setAlignment(Qt::AlignCenter);
        imgIron = new QLabel(inventoryTabPage);
        imgIron->setObjectName(QString::fromUtf8("imgIron"));
        imgIron->setGeometry(QRect(330, 70, 80, 80));
        imgIron->setStyleSheet(QString::fromUtf8(""));
        imgIron->setAlignment(Qt::AlignCenter);
        labelWoodResource = new QLabel(inventoryTabPage);
        labelWoodResource->setObjectName(QString::fromUtf8("labelWoodResource"));
        labelWoodResource->setGeometry(QRect(30, 150, 100, 25));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Roboto"));
        font5.setPointSize(12);
        font5.setBold(true);
        font5.setWeight(75);
        labelWoodResource->setFont(font5);
        labelWoodResource->setAlignment(Qt::AlignCenter);
        labelStoneResource = new QLabel(inventoryTabPage);
        labelStoneResource->setObjectName(QString::fromUtf8("labelStoneResource"));
        labelStoneResource->setGeometry(QRect(180, 150, 100, 25));
        labelStoneResource->setFont(font5);
        labelStoneResource->setAlignment(Qt::AlignCenter);
        labelIronResource = new QLabel(inventoryTabPage);
        labelIronResource->setObjectName(QString::fromUtf8("labelIronResource"));
        labelIronResource->setGeometry(QRect(320, 150, 100, 25));
        labelIronResource->setFont(font5);
        labelIronResource->setAlignment(Qt::AlignCenter);
        equipment_atk_1 = new QLabel(inventoryTabPage);
        equipment_atk_1->setObjectName(QString::fromUtf8("equipment_atk_1"));
        equipment_atk_1->setGeometry(QRect(40, 275, 80, 80));
        equipment_atk_1->setAlignment(Qt::AlignCenter);
        equipment_atk_2 = new QLabel(inventoryTabPage);
        equipment_atk_2->setObjectName(QString::fromUtf8("equipment_atk_2"));
        equipment_atk_2->setGeometry(QRect(190, 275, 80, 80));
        equipment_atk_2->setAlignment(Qt::AlignCenter);
        equipment_atk_3 = new QLabel(inventoryTabPage);
        equipment_atk_3->setObjectName(QString::fromUtf8("equipment_atk_3"));
        equipment_atk_3->setGeometry(QRect(330, 275, 80, 80));
        equipment_atk_3->setAlignment(Qt::AlignCenter);
        equipment_atk_4 = new QLabel(inventoryTabPage);
        equipment_atk_4->setObjectName(QString::fromUtf8("equipment_atk_4"));
        equipment_atk_4->setGeometry(QRect(480, 275, 80, 80));
        equipment_atk_4->setAlignment(Qt::AlignCenter);
        buttonAttack = new QPushButton(inventoryTabPage);
        buttonAttack->setObjectName(QString::fromUtf8("buttonAttack"));
        buttonAttack->setEnabled(true);
        buttonAttack->setGeometry(QRect(95, 485, 200, 50));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Roboto"));
        font6.setPointSize(20);
        font6.setBold(true);
        font6.setItalic(false);
        font6.setWeight(75);
        buttonAttack->setFont(font6);
        buttonAttack->setStyleSheet(QString::fromUtf8(""));
        buttonAttack->setCheckable(false);
        text2_4 = new QLabel(inventoryTabPage);
        text2_4->setObjectName(QString::fromUtf8("text2_4"));
        text2_4->setGeometry(QRect(40, 405, 301, 30));
        text2_4->setFont(font3);
        miniText2_3 = new QLabel(inventoryTabPage);
        miniText2_3->setObjectName(QString::fromUtf8("miniText2_3"));
        miniText2_3->setGeometry(QRect(40, 435, 450, 30));
        miniText2_3->setFont(font4);
        line2_4 = new QFrame(inventoryTabPage);
        line2_4->setObjectName(QString::fromUtf8("line2_4"));
        line2_4->setGeometry(QRect(40, 465, 540, 3));
        line2_4->setFrameShape(QFrame::HLine);
        line2_4->setFrameShadow(QFrame::Sunken);
        buttonCheat = new QPushButton(inventoryTabPage);
        buttonCheat->setObjectName(QString::fromUtf8("buttonCheat"));
        buttonCheat->setGeometry(QRect(340, 485, 200, 50));
        buttonCheat->setFont(font6);
        buttonCheat->setStyleSheet(QString::fromUtf8(""));
        textTeam1Weapon = new QLabel(inventoryTabPage);
        textTeam1Weapon->setObjectName(QString::fromUtf8("textTeam1Weapon"));
        textTeam1Weapon->setGeometry(QRect(55, 243, 50, 30));
        textTeam1Weapon->setFont(font2);
        textTeam1Weapon->setAlignment(Qt::AlignCenter);
        textTeam4Weapon = new QLabel(inventoryTabPage);
        textTeam4Weapon->setObjectName(QString::fromUtf8("textTeam4Weapon"));
        textTeam4Weapon->setGeometry(QRect(495, 243, 50, 30));
        textTeam4Weapon->setFont(font2);
        textTeam4Weapon->setAlignment(Qt::AlignCenter);
        textTeam2Weapon = new QLabel(inventoryTabPage);
        textTeam2Weapon->setObjectName(QString::fromUtf8("textTeam2Weapon"));
        textTeam2Weapon->setGeometry(QRect(205, 243, 50, 30));
        textTeam2Weapon->setFont(font2);
        textTeam2Weapon->setAlignment(Qt::AlignCenter);
        textTeam3Weapon = new QLabel(inventoryTabPage);
        textTeam3Weapon->setObjectName(QString::fromUtf8("textTeam3Weapon"));
        textTeam3Weapon->setGeometry(QRect(345, 243, 50, 30));
        textTeam3Weapon->setFont(font2);
        textTeam3Weapon->setAlignment(Qt::AlignCenter);
        labelAtk_team1 = new QLabel(inventoryTabPage);
        labelAtk_team1->setObjectName(QString::fromUtf8("labelAtk_team1"));
        labelAtk_team1->setGeometry(QRect(30, 360, 100, 25));
        labelAtk_team1->setFont(font2);
        labelAtk_team1->setAlignment(Qt::AlignCenter);
        labelAtk_team2 = new QLabel(inventoryTabPage);
        labelAtk_team2->setObjectName(QString::fromUtf8("labelAtk_team2"));
        labelAtk_team2->setGeometry(QRect(180, 360, 100, 25));
        labelAtk_team2->setFont(font2);
        labelAtk_team2->setAlignment(Qt::AlignCenter);
        labelAtk_team3 = new QLabel(inventoryTabPage);
        labelAtk_team3->setObjectName(QString::fromUtf8("labelAtk_team3"));
        labelAtk_team3->setGeometry(QRect(320, 360, 100, 25));
        labelAtk_team3->setFont(font2);
        labelAtk_team3->setAlignment(Qt::AlignCenter);
        labelAtk_team4 = new QLabel(inventoryTabPage);
        labelAtk_team4->setObjectName(QString::fromUtf8("labelAtk_team4"));
        labelAtk_team4->setGeometry(QRect(470, 360, 100, 25));
        labelAtk_team4->setFont(font2);
        labelAtk_team4->setAlignment(Qt::AlignCenter);
        imgGold = new QLabel(inventoryTabPage);
        imgGold->setObjectName(QString::fromUtf8("imgGold"));
        imgGold->setGeometry(QRect(480, 70, 80, 80));
        imgGold->setStyleSheet(QString::fromUtf8(""));
        imgGold->setAlignment(Qt::AlignCenter);
        labelGoldResource = new QLabel(inventoryTabPage);
        labelGoldResource->setObjectName(QString::fromUtf8("labelGoldResource"));
        labelGoldResource->setGeometry(QRect(470, 150, 100, 25));
        labelGoldResource->setFont(font5);
        labelGoldResource->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(inventoryTabPage, QString());
        shopTabPage = new QWidget();
        shopTabPage->setObjectName(QString::fromUtf8("shopTabPage"));
        line3_0 = new QFrame(shopTabPage);
        line3_0->setObjectName(QString::fromUtf8("line3_0"));
        line3_0->setGeometry(QRect(315, 30, 20, 520));
        line3_0->setFrameShape(QFrame::VLine);
        line3_0->setFrameShadow(QFrame::Sunken);
        text3_1 = new QLabel(shopTabPage);
        text3_1->setObjectName(QString::fromUtf8("text3_1"));
        text3_1->setGeometry(QRect(30, 30, 150, 30));
        text3_1->setFont(font3);
        text3_2 = new QLabel(shopTabPage);
        text3_2->setObjectName(QString::fromUtf8("text3_2"));
        text3_2->setGeometry(QRect(345, 30, 180, 30));
        text3_2->setFont(font3);
        line3_1 = new QFrame(shopTabPage);
        line3_1->setObjectName(QString::fromUtf8("line3_1"));
        line3_1->setGeometry(QRect(30, 90, 280, 3));
        line3_1->setFrameShape(QFrame::HLine);
        line3_1->setFrameShadow(QFrame::Sunken);
        line3_2 = new QFrame(shopTabPage);
        line3_2->setObjectName(QString::fromUtf8("line3_2"));
        line3_2->setGeometry(QRect(345, 90, 250, 3));
        line3_2->setFrameShape(QFrame::HLine);
        line3_2->setFrameShadow(QFrame::Sunken);
        miniText3_1 = new QLabel(shopTabPage);
        miniText3_1->setObjectName(QString::fromUtf8("miniText3_1"));
        miniText3_1->setGeometry(QRect(30, 60, 280, 30));
        miniText3_1->setFont(font4);
        miniText3_2 = new QLabel(shopTabPage);
        miniText3_2->setObjectName(QString::fromUtf8("miniText3_2"));
        miniText3_2->setGeometry(QRect(345, 60, 280, 30));
        miniText3_2->setFont(font4);
        imageShop_fence = new QLabel(shopTabPage);
        imageShop_fence->setObjectName(QString::fromUtf8("imageShop_fence"));
        imageShop_fence->setGeometry(QRect(340, 110, 80, 80));
        imageShop_fence->setAlignment(Qt::AlignCenter);
        imageShop_woodwall = new QLabel(shopTabPage);
        imageShop_woodwall->setObjectName(QString::fromUtf8("imageShop_woodwall"));
        imageShop_woodwall->setGeometry(QRect(340, 220, 80, 80));
        imageShop_woodwall->setAlignment(Qt::AlignCenter);
        imageShop_stonewall = new QLabel(shopTabPage);
        imageShop_stonewall->setObjectName(QString::fromUtf8("imageShop_stonewall"));
        imageShop_stonewall->setGeometry(QRect(340, 330, 80, 80));
        imageShop_stonewall->setAlignment(Qt::AlignCenter);
        imageShop_legendwall = new QLabel(shopTabPage);
        imageShop_legendwall->setObjectName(QString::fromUtf8("imageShop_legendwall"));
        imageShop_legendwall->setGeometry(QRect(340, 440, 80, 80));
        imageShop_legendwall->setAlignment(Qt::AlignCenter);
        imageShop_ballista = new QLabel(shopTabPage);
        imageShop_ballista->setObjectName(QString::fromUtf8("imageShop_ballista"));
        imageShop_ballista->setGeometry(QRect(30, 110, 80, 80));
        imageShop_ballista->setAlignment(Qt::AlignCenter);
        imageShop_catapult = new QLabel(shopTabPage);
        imageShop_catapult->setObjectName(QString::fromUtf8("imageShop_catapult"));
        imageShop_catapult->setGeometry(QRect(30, 220, 80, 80));
        imageShop_catapult->setAlignment(Qt::AlignCenter);
        imageShop_cannon = new QLabel(shopTabPage);
        imageShop_cannon->setObjectName(QString::fromUtf8("imageShop_cannon"));
        imageShop_cannon->setGeometry(QRect(30, 330, 80, 80));
        imageShop_cannon->setAlignment(Qt::AlignCenter);
        textShop_1 = new QLabel(shopTabPage);
        textShop_1->setObjectName(QString::fromUtf8("textShop_1"));
        textShop_1->setGeometry(QRect(110, 110, 180, 25));
        textShop_1->setFont(font2);
        textShop_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textShop_2 = new QLabel(shopTabPage);
        textShop_2->setObjectName(QString::fromUtf8("textShop_2"));
        textShop_2->setGeometry(QRect(110, 220, 180, 25));
        textShop_2->setFont(font2);
        textShop_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textShop_3 = new QLabel(shopTabPage);
        textShop_3->setObjectName(QString::fromUtf8("textShop_3"));
        textShop_3->setGeometry(QRect(110, 330, 180, 25));
        textShop_3->setFont(font2);
        textShop_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textShop_4 = new QLabel(shopTabPage);
        textShop_4->setObjectName(QString::fromUtf8("textShop_4"));
        textShop_4->setGeometry(QRect(425, 110, 180, 25));
        textShop_4->setFont(font2);
        textShop_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textShop_5 = new QLabel(shopTabPage);
        textShop_5->setObjectName(QString::fromUtf8("textShop_5"));
        textShop_5->setGeometry(QRect(425, 220, 180, 25));
        textShop_5->setFont(font2);
        textShop_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textShop_6 = new QLabel(shopTabPage);
        textShop_6->setObjectName(QString::fromUtf8("textShop_6"));
        textShop_6->setGeometry(QRect(425, 330, 180, 25));
        textShop_6->setFont(font2);
        textShop_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textShop_7 = new QLabel(shopTabPage);
        textShop_7->setObjectName(QString::fromUtf8("textShop_7"));
        textShop_7->setGeometry(QRect(425, 440, 180, 25));
        textShop_7->setFont(font2);
        textShop_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        miniTextShop_1 = new QLabel(shopTabPage);
        miniTextShop_1->setObjectName(QString::fromUtf8("miniTextShop_1"));
        miniTextShop_1->setGeometry(QRect(125, 140, 180, 30));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Roboto"));
        font7.setPointSize(8);
        font7.setItalic(false);
        miniTextShop_1->setFont(font7);
        miniTextShop_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        miniTextShop_2 = new QLabel(shopTabPage);
        miniTextShop_2->setObjectName(QString::fromUtf8("miniTextShop_2"));
        miniTextShop_2->setGeometry(QRect(125, 250, 180, 30));
        miniTextShop_2->setFont(font7);
        miniTextShop_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        miniTextShop_3 = new QLabel(shopTabPage);
        miniTextShop_3->setObjectName(QString::fromUtf8("miniTextShop_3"));
        miniTextShop_3->setGeometry(QRect(125, 360, 180, 30));
        miniTextShop_3->setFont(font7);
        miniTextShop_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        miniTextShop_4 = new QLabel(shopTabPage);
        miniTextShop_4->setObjectName(QString::fromUtf8("miniTextShop_4"));
        miniTextShop_4->setGeometry(QRect(430, 140, 180, 30));
        miniTextShop_4->setFont(font7);
        miniTextShop_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        miniTextShop_5 = new QLabel(shopTabPage);
        miniTextShop_5->setObjectName(QString::fromUtf8("miniTextShop_5"));
        miniTextShop_5->setGeometry(QRect(430, 250, 180, 30));
        miniTextShop_5->setFont(font7);
        miniTextShop_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        miniTextShop_6 = new QLabel(shopTabPage);
        miniTextShop_6->setObjectName(QString::fromUtf8("miniTextShop_6"));
        miniTextShop_6->setGeometry(QRect(430, 360, 180, 30));
        miniTextShop_6->setFont(font7);
        miniTextShop_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        miniTextShop_7 = new QLabel(shopTabPage);
        miniTextShop_7->setObjectName(QString::fromUtf8("miniTextShop_7"));
        miniTextShop_7->setGeometry(QRect(430, 470, 180, 30));
        miniTextShop_7->setFont(font7);
        miniTextShop_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line3_3 = new QFrame(shopTabPage);
        line3_3->setObjectName(QString::fromUtf8("line3_3"));
        line3_3->setGeometry(QRect(30, 450, 280, 3));
        line3_3->setFrameShape(QFrame::HLine);
        line3_3->setFrameShadow(QFrame::Sunken);
        buttonBuyItem = new QPushButton(shopTabPage);
        buttonBuyItem->setObjectName(QString::fromUtf8("buttonBuyItem"));
        buttonBuyItem->setGeometry(QRect(30, 500, 280, 41));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Roboto"));
        font8.setPointSize(16);
        font8.setBold(true);
        font8.setItalic(false);
        font8.setWeight(75);
        buttonBuyItem->setFont(font8);
        buttonBuyItem->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        background-color: #00cccc;\n"
"        color: #fff7e6 ;\n"
"        border-radius: 20;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"        color: #fff7e6 ;\n"
"        background-color: #002e4d;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"        color: #fff7e6 ;\n"
"        background-color: #000066;\n"
"}"));
        labelResourceShop = new QLabel(shopTabPage);
        labelResourceShop->setObjectName(QString::fromUtf8("labelResourceShop"));
        labelResourceShop->setGeometry(QRect(30, 460, 280, 30));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Roboto"));
        font9.setPointSize(10);
        font9.setBold(true);
        font9.setWeight(75);
        labelResourceShop->setFont(font9);
        labelResourceShop->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget->addTab(shopTabPage, QString());
        rankingTab = new QWidget();
        rankingTab->setObjectName(QString::fromUtf8("rankingTab"));
        rankingTab->setEnabled(false);
        text1 = new QLabel(rankingTab);
        text1->setObjectName(QString::fromUtf8("text1"));
        text1->setGeometry(QRect(115, 40, 400, 40));
        QFont font10;
        font10.setFamily(QString::fromUtf8("Roboto"));
        font10.setPointSize(16);
        font10.setBold(true);
        font10.setWeight(75);
        text1->setFont(font10);
        text1->setAlignment(Qt::AlignCenter);
        text2 = new QLabel(rankingTab);
        text2->setObjectName(QString::fromUtf8("text2"));
        text2->setGeometry(QRect(115, 90, 400, 40));
        QFont font11;
        font11.setFamily(QString::fromUtf8("Roboto"));
        font11.setPointSize(16);
        font11.setBold(false);
        font11.setWeight(50);
        text2->setFont(font11);
        text2->setAlignment(Qt::AlignCenter);
        text3 = new QLabel(rankingTab);
        text3->setObjectName(QString::fromUtf8("text3"));
        text3->setGeometry(QRect(120, 260, 400, 40));
        text3->setFont(font11);
        text3->setAlignment(Qt::AlignCenter);
        btnContinue = new QPushButton(rankingTab);
        btnContinue->setObjectName(QString::fromUtf8("btnContinue"));
        btnContinue->setGeometry(QRect(225, 450, 180, 50));
        QFont font12;
        font12.setFamily(QString::fromUtf8("Roboto"));
        font12.setPointSize(18);
        font12.setBold(true);
        font12.setWeight(75);
        btnContinue->setFont(font12);
        imgGold1 = new QLabel(rankingTab);
        imgGold1->setObjectName(QString::fromUtf8("imgGold1"));
        imgGold1->setGeometry(QRect(345, 140, 40, 40));
        imgGold1->setStyleSheet(QString::fromUtf8(""));
        imgGold1->setAlignment(Qt::AlignCenter);
        labelAsset1 = new QLabel(rankingTab);
        labelAsset1->setObjectName(QString::fromUtf8("labelAsset1"));
        labelAsset1->setGeometry(QRect(115, 140, 200, 40));
        QFont font13;
        font13.setFamily(QString::fromUtf8("Roboto"));
        font13.setPointSize(12);
        font13.setBold(false);
        font13.setWeight(50);
        labelAsset1->setFont(font13);
        labelAsset1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelAsset2 = new QLabel(rankingTab);
        labelAsset2->setObjectName(QString::fromUtf8("labelAsset2"));
        labelAsset2->setGeometry(QRect(115, 310, 200, 40));
        labelAsset2->setFont(font13);
        labelAsset2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        imgGold2 = new QLabel(rankingTab);
        imgGold2->setObjectName(QString::fromUtf8("imgGold2"));
        imgGold2->setGeometry(QRect(345, 310, 40, 40));
        imgGold2->setStyleSheet(QString::fromUtf8(""));
        imgGold2->setAlignment(Qt::AlignCenter);
        label1st = new QLabel(rankingTab);
        label1st->setObjectName(QString::fromUtf8("label1st"));
        label1st->setGeometry(QRect(60, 190, 500, 40));
        label1st->setFont(font9);
        label1st->setAlignment(Qt::AlignCenter);
        label2nd = new QLabel(rankingTab);
        label2nd->setObjectName(QString::fromUtf8("label2nd"));
        label2nd->setGeometry(QRect(60, 360, 500, 40));
        label2nd->setFont(font9);
        label2nd->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(rankingTab, QString());
        listGameLog = new QListWidget(centralwidget);
        listGameLog->setObjectName(QString::fromUtf8("listGameLog"));
        listGameLog->setGeometry(QRect(10, 380, 300, 220));
        QFont font14;
        font14.setFamily(QString::fromUtf8("Roboto"));
        listGameLog->setFont(font14);
        listGameLog->setStyleSheet(QString::fromUtf8(""));
        text0_1 = new QLabel(centralwidget);
        text0_1->setObjectName(QString::fromUtf8("text0_1"));
        text0_1->setGeometry(QRect(10, 350, 300, 30));
        QFont font15;
        font15.setFamily(QString::fromUtf8("Roboto"));
        font15.setPointSize(11);
        font15.setBold(true);
        font15.setItalic(true);
        font15.setWeight(75);
        text0_1->setFont(font15);
        text0_1->setAlignment(Qt::AlignCenter);
        labelGreet = new QLabel(centralwidget);
        labelGreet->setObjectName(QString::fromUtf8("labelGreet"));
        labelGreet->setGeometry(QRect(10, 15, 300, 25));
        QFont font16;
        font16.setFamily(QString::fromUtf8("Roboto"));
        font16.setPointSize(11);
        font16.setBold(true);
        font16.setWeight(75);
        labelGreet->setFont(font16);
        labelGreet->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line_greet = new QFrame(centralwidget);
        line_greet->setObjectName(QString::fromUtf8("line_greet"));
        line_greet->setGeometry(QRect(10, 45, 300, 3));
        line_greet->setFrameShape(QFrame::HLine);
        line_greet->setFrameShadow(QFrame::Sunken);
        text0_2 = new QLabel(centralwidget);
        text0_2->setObjectName(QString::fromUtf8("text0_2"));
        text0_2->setGeometry(QRect(10, 50, 300, 30));
        text0_2->setFont(font15);
        text0_2->setAlignment(Qt::AlignCenter);
        listPlayer = new QListWidget(centralwidget);
        listPlayer->setObjectName(QString::fromUtf8("listPlayer"));
        listPlayer->setGeometry(QRect(10, 80, 300, 270));
        listPlayer->setFont(font14);
        listPlayer->setStyleSheet(QString::fromUtf8(""));
        StageGame->setCentralWidget(centralwidget);
        listGameLog->raise();
        text0_1->raise();
        labelGreet->raise();
        line_greet->raise();
        text0_2->raise();
        listPlayer->raise();
        tabWidget->raise();
        statusbar = new QStatusBar(StageGame);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StageGame->setStatusBar(statusbar);
        menuBar = new QMenuBar(StageGame);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 25));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        StageGame->setMenuBar(menuBar);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionRules);
        menuHelp->addAction(actionQuit_Game);

        retranslateUi(StageGame);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(StageGame);
    } // setupUi

    void retranslateUi(QMainWindow *StageGame)
    {
        StageGame->setWindowTitle(QApplication::translate("StageGame", "MainWindow", nullptr));
        actionRules->setText(QApplication::translate("StageGame", "Rules", nullptr));
        actionQuit_Game->setText(QApplication::translate("StageGame", "Quit Game", nullptr));
#ifndef QT_NO_TOOLTIP
        mapTabPage->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        mapTabPage->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        castle1->setText(QApplication::translate("StageGame", "Castle1", nullptr));
        castle2->setText(QApplication::translate("StageGame", "Castle2", nullptr));
        castle3->setText(QApplication::translate("StageGame", "Castle3", nullptr));
        mine1->setText(QApplication::translate("StageGame", "Mine1", nullptr));
        mine4->setText(QApplication::translate("StageGame", "Mine4", nullptr));
        mine2->setText(QApplication::translate("StageGame", "Mine2", nullptr));
        mine5->setText(QApplication::translate("StageGame", "Mine5", nullptr));
        mine6->setText(QApplication::translate("StageGame", "Mine6", nullptr));
        mine3->setText(QApplication::translate("StageGame", "Mine3", nullptr));
        textCastle1->setText(QApplication::translate("StageGame", "Castle #1", nullptr));
        textCastle2->setText(QApplication::translate("StageGame", "Castle #2", nullptr));
        textCastle3->setText(QApplication::translate("StageGame", "Castle #3", nullptr));
        textMine1->setText(QApplication::translate("StageGame", "Mine #1", nullptr));
        textMine4->setText(QApplication::translate("StageGame", "Mine #4", nullptr));
        textMine6->setText(QApplication::translate("StageGame", "Mine #6", nullptr));
        textMine3->setText(QApplication::translate("StageGame", "Mine#3", nullptr));
        textMine5->setText(QApplication::translate("StageGame", "Mine #5", nullptr));
        textMine2->setText(QApplication::translate("StageGame", "Mine #2", nullptr));
        labelStatusCst1->setText(QApplication::translate("StageGame", "UNOCCUPIED", nullptr));
        labelStatusCst2->setText(QApplication::translate("StageGame", "UNOCCUPIED", nullptr));
        labelStatusCst3->setText(QApplication::translate("StageGame", "UNOCCUPIED", nullptr));
        labelWallCst1->setText(QApplication::translate("StageGame", "NO WALL", nullptr));
        labelWallCst2->setText(QApplication::translate("StageGame", "NO WALL", nullptr));
        labelWallCst3->setText(QApplication::translate("StageGame", "NO WALL", nullptr));
        labelResMine1->setText(QApplication::translate("StageGame", "Nothing to show", nullptr));
        labelResMine2->setText(QApplication::translate("StageGame", "Nothing to show", nullptr));
        labelResMine3->setText(QApplication::translate("StageGame", "Nothing to show", nullptr));
        labelResMine4->setText(QApplication::translate("StageGame", "Nothing to show", nullptr));
        labelResMine5->setText(QApplication::translate("StageGame", "Nothing to show", nullptr));
        labelResMine6->setText(QApplication::translate("StageGame", "Nothing to show", nullptr));
        labelToughCst1->setText(QApplication::translate("StageGame", "TOUGHNESS", nullptr));
        labelToughCst2->setText(QApplication::translate("StageGame", "TOUGHNESS", nullptr));
        labelToughCst3->setText(QApplication::translate("StageGame", "TOUGHNESS", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(mapTabPage), QApplication::translate("StageGame", "Map", nullptr));
        text2_1->setText(QApplication::translate("StageGame", "Resource", nullptr));
        text2_3->setText(QApplication::translate("StageGame", "Team's weapon", nullptr));
        miniText2_2->setText(QApplication::translate("StageGame", "Your team and enemies team 's weapon shown here. ", nullptr));
        imgWood->setText(QApplication::translate("StageGame", "Wood", nullptr));
        imgStone->setText(QApplication::translate("StageGame", "Stone", nullptr));
        imgIron->setText(QApplication::translate("StageGame", "Iron", nullptr));
        labelWoodResource->setText(QApplication::translate("StageGame", "x 0", nullptr));
        labelStoneResource->setText(QApplication::translate("StageGame", "x 0", nullptr));
        labelIronResource->setText(QApplication::translate("StageGame", "x 0", nullptr));
        equipment_atk_1->setText(QApplication::translate("StageGame", "ATK", nullptr));
        equipment_atk_2->setText(QApplication::translate("StageGame", "ATK", nullptr));
        equipment_atk_3->setText(QApplication::translate("StageGame", "ATK", nullptr));
        equipment_atk_4->setText(QApplication::translate("StageGame", "ATK", nullptr));
        buttonAttack->setText(QApplication::translate("StageGame", "Attack", nullptr));
        text2_4->setText(QApplication::translate("StageGame", "Attack Command", nullptr));
        miniText2_3->setText(QApplication::translate("StageGame", "Attack enemies' castle", nullptr));
        buttonCheat->setText(QApplication::translate("StageGame", "Cheat", nullptr));
        textTeam1Weapon->setText(QApplication::translate("StageGame", "Team 1", nullptr));
        textTeam4Weapon->setText(QApplication::translate("StageGame", "Team 4", nullptr));
        textTeam2Weapon->setText(QApplication::translate("StageGame", "Team 2", nullptr));
        textTeam3Weapon->setText(QApplication::translate("StageGame", "Team 3", nullptr));
        labelAtk_team1->setText(QApplication::translate("StageGame", "POWER: 0", nullptr));
        labelAtk_team2->setText(QApplication::translate("StageGame", "POWER: 0", nullptr));
        labelAtk_team3->setText(QApplication::translate("StageGame", "POWER: 0", nullptr));
        labelAtk_team4->setText(QApplication::translate("StageGame", "POWER: 0", nullptr));
        imgGold->setText(QApplication::translate("StageGame", "Gold", nullptr));
        labelGoldResource->setText(QApplication::translate("StageGame", "x 0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(inventoryTabPage), QApplication::translate("StageGame", "Inventory", nullptr));
        text3_1->setText(QApplication::translate("StageGame", "Weapon (ATK)", nullptr));
        text3_2->setText(QApplication::translate("StageGame", "Castle Wall (DEF)", nullptr));
        miniText3_1->setText(QApplication::translate("StageGame", "Powerful weapon to attack enemy's castle", nullptr));
        miniText3_2->setText(QApplication::translate("StageGame", "Guard your castle with toughful walls", nullptr));
        imageShop_fence->setText(QApplication::translate("StageGame", "fence", nullptr));
        imageShop_woodwall->setText(QApplication::translate("StageGame", "woodwall", nullptr));
        imageShop_stonewall->setText(QApplication::translate("StageGame", "stonewall", nullptr));
        imageShop_legendwall->setText(QApplication::translate("StageGame", "legendwall", nullptr));
        imageShop_ballista->setText(QApplication::translate("StageGame", "ballista", nullptr));
        imageShop_catapult->setText(QApplication::translate("StageGame", "catapult", nullptr));
        imageShop_cannon->setText(QApplication::translate("StageGame", "cannon", nullptr));
        textShop_1->setText(QApplication::translate("StageGame", "BALLISTA ! : 1000ATK", nullptr));
        textShop_2->setText(QApplication::translate("StageGame", "CATAPULT ! : 3000ATK", nullptr));
        textShop_3->setText(QApplication::translate("StageGame", "CANNON ! : 8000ATK", nullptr));
        textShop_4->setText(QApplication::translate("StageGame", "FENCE : 200 DEF", nullptr));
        textShop_5->setText(QApplication::translate("StageGame", "WOOD WALL : 1000 DEF", nullptr));
        textShop_6->setText(QApplication::translate("StageGame", "STONE WALL : 3000 DEF", nullptr));
        textShop_7->setText(QApplication::translate("StageGame", "LEGEND WALL : 8000 DEF", nullptr));
        miniTextShop_1->setText(QApplication::translate("StageGame", " Price: 1500 Wood & 200 Iron", nullptr));
        miniTextShop_2->setText(QApplication::translate("StageGame", " Price: 400 W + 1500 S + 300 I", nullptr));
        miniTextShop_3->setText(QApplication::translate("StageGame", " Price: 500 W + 2500 S + 1800 I", nullptr));
        miniTextShop_4->setText(QApplication::translate("StageGame", " Cost: 200 W + 50 S + 50 I", nullptr));
        miniTextShop_5->setText(QApplication::translate("StageGame", " Cost: 1000 W + 100 S + 100 I", nullptr));
        miniTextShop_6->setText(QApplication::translate("StageGame", "Cost: 200 W + 1000 S + 1000 I", nullptr));
        miniTextShop_7->setText(QApplication::translate("StageGame", " Cost: 1000 W + 2000 S + 2000 I", nullptr));
        buttonBuyItem->setText(QApplication::translate("StageGame", "Buy something !", nullptr));
        labelResourceShop->setText(QApplication::translate("StageGame", "You have: 0W, 0S, 0I", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(shopTabPage), QApplication::translate("StageGame", "Shop", nullptr));
        text1->setText(QApplication::translate("StageGame", "THE GAME HAS ENDED !", nullptr));
        text2->setText(QApplication::translate("StageGame", "Winner", nullptr));
        text3->setText(QApplication::translate("StageGame", "Runner-up", nullptr));
        btnContinue->setText(QApplication::translate("StageGame", "Continue !", nullptr));
        imgGold1->setText(QApplication::translate("StageGame", "Gold", nullptr));
        labelAsset1->setText(QApplication::translate("StageGame", "Asset:", nullptr));
        labelAsset2->setText(QApplication::translate("StageGame", "Asset:", nullptr));
        imgGold2->setText(QApplication::translate("StageGame", "Gold", nullptr));
        label1st->setText(QApplication::translate("StageGame", "Champions:", nullptr));
        label2nd->setText(QApplication::translate("StageGame", "2nd place: ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(rankingTab), QApplication::translate("StageGame", "Ranking ", nullptr));
        text0_1->setText(QApplication::translate("StageGame", "NEWS", nullptr));
        labelGreet->setText(QApplication::translate("StageGame", "Greeting, username", nullptr));
        text0_2->setText(QApplication::translate("StageGame", "Player List", nullptr));
        menuHelp->setTitle(QApplication::translate("StageGame", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StageGame: public Ui_StageGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGEGAME_H
