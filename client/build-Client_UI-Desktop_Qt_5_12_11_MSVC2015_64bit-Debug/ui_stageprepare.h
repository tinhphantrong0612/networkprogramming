/********************************************************************************
** Form generated from reading UI file 'stageprepare.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGEPREPARE_H
#define UI_STAGEPREPARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StagePrepare
{
public:
    QAction *actionQuit_Lobby;
    QWidget *centralwidget;
    QPushButton *btnReady;
    QPushButton *btnUnready;
    QLabel *text1;
    QLabel *text2;
    QPushButton *btnStart;
    QLabel *labelRoomID;
    QLabel *labelUserTeam;
    QLabel *text3;
    QLabel *labelUserStatus;
    QLabel *labelGreet;
    QFrame *line1;
    QFrame *line3;
    QFrame *line4;
    QFrame *line2;
    QLabel *textTeam1;
    QLabel *textTeam2;
    QLabel *textTeam3;
    QLabel *textTeam5;
    QFrame *lineTeam1;
    QFrame *lineTeam2;
    QFrame *lineTeam4;
    QFrame *lineTeam3;
    QPushButton *btnChangeTeam;
    QFrame *lineTextGreeting;
    QLabel *labelPlayerID;
    QLabel *labelTeam1;
    QLabel *labelTeam2;
    QLabel *labelTeam4;
    QLabel *labelTeam3;
    QLabel *labelNotice;
    QPushButton *btnKick;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StagePrepare)
    {
        if (StagePrepare->objectName().isEmpty())
            StagePrepare->setObjectName(QString::fromUtf8("StagePrepare"));
        StagePrepare->resize(720, 500);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(9);
        StagePrepare->setFont(font);
        StagePrepare->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"        background-color: #ffff99;\n"
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
""));
        actionQuit_Lobby = new QAction(StagePrepare);
        actionQuit_Lobby->setObjectName(QString::fromUtf8("actionQuit_Lobby"));
        centralwidget = new QWidget(StagePrepare);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnReady = new QPushButton(centralwidget);
        btnReady->setObjectName(QString::fromUtf8("btnReady"));
        btnReady->setGeometry(QRect(400, 160, 80, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        btnReady->setFont(font1);
        btnUnready = new QPushButton(centralwidget);
        btnUnready->setObjectName(QString::fromUtf8("btnUnready"));
        btnUnready->setGeometry(QRect(500, 160, 80, 40));
        btnUnready->setFont(font1);
        text1 = new QLabel(centralwidget);
        text1->setObjectName(QString::fromUtf8("text1"));
        text1->setGeometry(QRect(50, 70, 150, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        text1->setFont(font2);
        text2 = new QLabel(centralwidget);
        text2->setObjectName(QString::fromUtf8("text2"));
        text2->setGeometry(QRect(50, 120, 150, 20));
        text2->setFont(font2);
        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(400, 80, 80, 40));
        btnStart->setFont(font1);
        labelRoomID = new QLabel(centralwidget);
        labelRoomID->setObjectName(QString::fromUtf8("labelRoomID"));
        labelRoomID->setGeometry(QRect(200, 70, 150, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto"));
        font3.setPointSize(11);
        labelRoomID->setFont(font3);
        labelUserTeam = new QLabel(centralwidget);
        labelUserTeam->setObjectName(QString::fromUtf8("labelUserTeam"));
        labelUserTeam->setGeometry(QRect(200, 120, 150, 20));
        labelUserTeam->setFont(font3);
        text3 = new QLabel(centralwidget);
        text3->setObjectName(QString::fromUtf8("text3"));
        text3->setGeometry(QRect(50, 170, 150, 20));
        text3->setFont(font2);
        labelUserStatus = new QLabel(centralwidget);
        labelUserStatus->setObjectName(QString::fromUtf8("labelUserStatus"));
        labelUserStatus->setGeometry(QRect(200, 170, 150, 20));
        labelUserStatus->setFont(font3);
        labelGreet = new QLabel(centralwidget);
        labelGreet->setObjectName(QString::fromUtf8("labelGreet"));
        labelGreet->setGeometry(QRect(450, 15, 250, 25));
        labelGreet->setFont(font1);
        labelGreet->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line1 = new QFrame(centralwidget);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setGeometry(QRect(30, 50, 340, 3));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);
        line3 = new QFrame(centralwidget);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setGeometry(QRect(30, 210, 340, 3));
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);
        line4 = new QFrame(centralwidget);
        line4->setObjectName(QString::fromUtf8("line4"));
        line4->setGeometry(QRect(30, 50, 3, 160));
        line4->setFrameShape(QFrame::VLine);
        line4->setFrameShadow(QFrame::Sunken);
        line2 = new QFrame(centralwidget);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setGeometry(QRect(370, 50, 3, 160));
        line2->setFrameShape(QFrame::VLine);
        line2->setFrameShadow(QFrame::Sunken);
        textTeam1 = new QLabel(centralwidget);
        textTeam1->setObjectName(QString::fromUtf8("textTeam1"));
        textTeam1->setGeometry(QRect(50, 265, 60, 30));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto"));
        font4.setPointSize(9);
        font4.setBold(true);
        font4.setWeight(75);
        textTeam1->setFont(font4);
        textTeam2 = new QLabel(centralwidget);
        textTeam2->setObjectName(QString::fromUtf8("textTeam2"));
        textTeam2->setGeometry(QRect(50, 310, 60, 30));
        textTeam2->setFont(font4);
        textTeam3 = new QLabel(centralwidget);
        textTeam3->setObjectName(QString::fromUtf8("textTeam3"));
        textTeam3->setGeometry(QRect(50, 355, 60, 30));
        textTeam3->setFont(font4);
        textTeam5 = new QLabel(centralwidget);
        textTeam5->setObjectName(QString::fromUtf8("textTeam5"));
        textTeam5->setGeometry(QRect(50, 400, 60, 30));
        textTeam5->setFont(font4);
        lineTeam1 = new QFrame(centralwidget);
        lineTeam1->setObjectName(QString::fromUtf8("lineTeam1"));
        lineTeam1->setGeometry(QRect(30, 250, 3, 195));
        lineTeam1->setFrameShape(QFrame::VLine);
        lineTeam1->setFrameShadow(QFrame::Sunken);
        lineTeam2 = new QFrame(centralwidget);
        lineTeam2->setObjectName(QString::fromUtf8("lineTeam2"));
        lineTeam2->setGeometry(QRect(30, 250, 660, 3));
        lineTeam2->setFrameShape(QFrame::HLine);
        lineTeam2->setFrameShadow(QFrame::Sunken);
        lineTeam4 = new QFrame(centralwidget);
        lineTeam4->setObjectName(QString::fromUtf8("lineTeam4"));
        lineTeam4->setGeometry(QRect(30, 445, 660, 3));
        lineTeam4->setFrameShape(QFrame::HLine);
        lineTeam4->setFrameShadow(QFrame::Sunken);
        lineTeam3 = new QFrame(centralwidget);
        lineTeam3->setObjectName(QString::fromUtf8("lineTeam3"));
        lineTeam3->setGeometry(QRect(690, 250, 3, 195));
        lineTeam3->setFrameShape(QFrame::VLine);
        lineTeam3->setFrameShadow(QFrame::Sunken);
        btnChangeTeam = new QPushButton(centralwidget);
        btnChangeTeam->setObjectName(QString::fromUtf8("btnChangeTeam"));
        btnChangeTeam->setGeometry(QRect(500, 80, 180, 40));
        btnChangeTeam->setFont(font1);
        lineTextGreeting = new QFrame(centralwidget);
        lineTextGreeting->setObjectName(QString::fromUtf8("lineTextGreeting"));
        lineTextGreeting->setGeometry(QRect(200, 40, 500, 3));
        lineTextGreeting->setFrameShape(QFrame::HLine);
        lineTextGreeting->setFrameShadow(QFrame::Sunken);
        labelPlayerID = new QLabel(centralwidget);
        labelPlayerID->setObjectName(QString::fromUtf8("labelPlayerID"));
        labelPlayerID->setGeometry(QRect(200, 15, 250, 25));
        labelPlayerID->setFont(font1);
        labelPlayerID->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelTeam1 = new QLabel(centralwidget);
        labelTeam1->setObjectName(QString::fromUtf8("labelTeam1"));
        labelTeam1->setGeometry(QRect(120, 265, 550, 30));
        labelTeam1->setFont(font);
        labelTeam2 = new QLabel(centralwidget);
        labelTeam2->setObjectName(QString::fromUtf8("labelTeam2"));
        labelTeam2->setGeometry(QRect(120, 310, 550, 30));
        labelTeam2->setFont(font);
        labelTeam4 = new QLabel(centralwidget);
        labelTeam4->setObjectName(QString::fromUtf8("labelTeam4"));
        labelTeam4->setGeometry(QRect(120, 400, 550, 30));
        labelTeam4->setFont(font);
        labelTeam3 = new QLabel(centralwidget);
        labelTeam3->setObjectName(QString::fromUtf8("labelTeam3"));
        labelTeam3->setGeometry(QRect(120, 355, 550, 30));
        labelTeam3->setFont(font);
        labelNotice = new QLabel(centralwidget);
        labelNotice->setObjectName(QString::fromUtf8("labelNotice"));
        labelNotice->setGeometry(QRect(110, 220, 500, 20));
        labelNotice->setFont(font4);
        labelNotice->setAlignment(Qt::AlignCenter);
        btnKick = new QPushButton(centralwidget);
        btnKick->setObjectName(QString::fromUtf8("btnKick"));
        btnKick->setGeometry(QRect(600, 160, 80, 40));
        btnKick->setFont(font1);
        btnKick->setStyleSheet(QString::fromUtf8("QPushButton#btnKick {\n"
"        background-color: #ff3333;\n"
"}\n"
"\n"
"QPushButton#btnKick:hover {\n"
"        color: #fff7e6 ;\n"
"        background-color: #002e4d;\n"
"}\n"
"\n"
"QPushButton#btnKick:pressed {\n"
"        color: #fff7e6 ;\n"
"        background-color: #000066;\n"
"}"));
        StagePrepare->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StagePrepare);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 720, 25));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        StagePrepare->setMenuBar(menubar);
        statusbar = new QStatusBar(StagePrepare);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StagePrepare->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionQuit_Lobby);

        retranslateUi(StagePrepare);

        QMetaObject::connectSlotsByName(StagePrepare);
    } // setupUi

    void retranslateUi(QMainWindow *StagePrepare)
    {
        StagePrepare->setWindowTitle(QApplication::translate("StagePrepare", "MainWindow", nullptr));
        actionQuit_Lobby->setText(QApplication::translate("StagePrepare", "Quit Lobby", nullptr));
        btnReady->setText(QApplication::translate("StagePrepare", "Ready", nullptr));
        btnUnready->setText(QApplication::translate("StagePrepare", "Unready", nullptr));
        text1->setText(QApplication::translate("StagePrepare", "ROOM ID", nullptr));
        text2->setText(QApplication::translate("StagePrepare", "TEAMS", nullptr));
        btnStart->setText(QApplication::translate("StagePrepare", "Start !", nullptr));
        labelRoomID->setText(QApplication::translate("StagePrepare", "Room ID", nullptr));
        labelUserTeam->setText(QApplication::translate("StagePrepare", "No data", nullptr));
        text3->setText(QApplication::translate("StagePrepare", "PERMISSION", nullptr));
        labelUserStatus->setText(QApplication::translate("StagePrepare", "No data", nullptr));
        labelGreet->setText(QApplication::translate("StagePrepare", "Greeting, username", nullptr));
        textTeam1->setText(QApplication::translate("StagePrepare", "Team 1:", nullptr));
        textTeam2->setText(QApplication::translate("StagePrepare", "Team 2:", nullptr));
        textTeam3->setText(QApplication::translate("StagePrepare", "Team 3:", nullptr));
        textTeam5->setText(QApplication::translate("StagePrepare", "Team 4: ", nullptr));
        btnChangeTeam->setText(QApplication::translate("StagePrepare", "Change Team", nullptr));
        labelPlayerID->setText(QApplication::translate("StagePrepare", "PlayerID :", nullptr));
        labelTeam1->setText(QApplication::translate("StagePrepare", "NaN , NaN , NaN", nullptr));
        labelTeam2->setText(QApplication::translate("StagePrepare", "NaN , NaN , NaN", nullptr));
        labelTeam4->setText(QApplication::translate("StagePrepare", "NaN , NaN , NaN", nullptr));
        labelTeam3->setText(QApplication::translate("StagePrepare", "NaN , NaN , NaN", nullptr));
        labelNotice->setText(QApplication::translate("StagePrepare", "NOTICE: LOBBY UPDATED BELOW !", nullptr));
        btnKick->setText(QApplication::translate("StagePrepare", "Kick", nullptr));
        menuHelp->setTitle(QApplication::translate("StagePrepare", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StagePrepare: public Ui_StagePrepare {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGEPREPARE_H
