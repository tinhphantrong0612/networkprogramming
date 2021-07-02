/********************************************************************************
** Form generated from reading UI file 'stagewaitingroom.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGEWAITINGROOM_H
#define UI_STAGEWAITINGROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StageWaitingRoom
{
public:
    QAction *actionLogout;
    QWidget *centralwidget;
    QLabel *text0;
    QPushButton *btnCreate;
    QPushButton *btnJoin;
    QListWidget *listLobby;
    QLabel *text1;
    QLabel *text2;
    QPushButton *btnRefresh;
    QLabel *labelWelcome;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StageWaitingRoom)
    {
        if (StageWaitingRoom->objectName().isEmpty())
            StageWaitingRoom->setObjectName(QString::fromUtf8("StageWaitingRoom"));
        StageWaitingRoom->resize(700, 400);
        StageWaitingRoom->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"        background-color: #ffffe6;\n"
"}\n"
"\n"
"QInputDialog {\n"
"		font: Roboto;\n"
"		font-size: 9;\n"
"}\n"
"\n"
"QListWidget {\n"
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
"        background-color: #002e4d;\n"
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
"QMessageBox QPushButton {\n"
"        border-radius: 10;\n"
"        background-color: #005c99;\n"
"}\n"
""));
        actionLogout = new QAction(StageWaitingRoom);
        actionLogout->setObjectName(QString::fromUtf8("actionLogout"));
        centralwidget = new QWidget(StageWaitingRoom);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        text0 = new QLabel(centralwidget);
        text0->setObjectName(QString::fromUtf8("text0"));
        text0->setGeometry(QRect(30, 10, 200, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Ravie"));
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        text0->setFont(font);
        text0->setAlignment(Qt::AlignCenter);
        btnCreate = new QPushButton(centralwidget);
        btnCreate->setObjectName(QString::fromUtf8("btnCreate"));
        btnCreate->setGeometry(QRect(70, 135, 120, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        btnCreate->setFont(font1);
        btnJoin = new QPushButton(centralwidget);
        btnJoin->setObjectName(QString::fromUtf8("btnJoin"));
        btnJoin->setGeometry(QRect(70, 255, 120, 40));
        btnJoin->setFont(font1);
        listLobby = new QListWidget(centralwidget);
        listLobby->setObjectName(QString::fromUtf8("listLobby"));
        listLobby->setGeometry(QRect(255, 50, 425, 290));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(9);
        listLobby->setFont(font2);
        listLobby->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"		background-color: #ccffcc;\n"
"        border-radius: 10 ;\n"
"		font-family: Roboto;\n"
"		font-style: bold;\n"
"		font-size: 9;\n"
"        padding-left: 10;\n"
"        padding-top: 10;\n"
"}\n"
"\n"
"QListView::item:alternate {\n"
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
"}\n"
""));
        text1 = new QLabel(centralwidget);
        text1->setObjectName(QString::fromUtf8("text1"));
        text1->setGeometry(QRect(70, 200, 120, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Ravie"));
        font3.setPointSize(14);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        text1->setFont(font3);
        text1->setAlignment(Qt::AlignCenter);
        text2 = new QLabel(centralwidget);
        text2->setObjectName(QString::fromUtf8("text2"));
        text2->setGeometry(QRect(350, 10, 140, 30));
        text2->setFont(font);
        btnRefresh = new QPushButton(centralwidget);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));
        btnRefresh->setGeometry(QRect(560, 10, 60, 30));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto"));
        font4.setPointSize(8);
        font4.setBold(true);
        font4.setWeight(75);
        btnRefresh->setFont(font4);
        labelWelcome = new QLabel(centralwidget);
        labelWelcome->setObjectName(QString::fromUtf8("labelWelcome"));
        labelWelcome->setGeometry(QRect(30, 70, 200, 31));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Rockwell"));
        font5.setPointSize(12);
        labelWelcome->setFont(font5);
        labelWelcome->setAlignment(Qt::AlignCenter);
        StageWaitingRoom->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StageWaitingRoom);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 25));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        StageWaitingRoom->setMenuBar(menubar);
        statusbar = new QStatusBar(StageWaitingRoom);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StageWaitingRoom->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionLogout);

        retranslateUi(StageWaitingRoom);

        QMetaObject::connectSlotsByName(StageWaitingRoom);
    } // setupUi

    void retranslateUi(QMainWindow *StageWaitingRoom)
    {
        StageWaitingRoom->setWindowTitle(QApplication::translate("StageWaitingRoom", "MainWindow", nullptr));
        actionLogout->setText(QApplication::translate("StageWaitingRoom", "Logout", nullptr));
        text0->setText(QApplication::translate("StageWaitingRoom", "WAITING ROOM", nullptr));
        btnCreate->setText(QApplication::translate("StageWaitingRoom", "Create Game", nullptr));
        btnJoin->setText(QApplication::translate("StageWaitingRoom", "Join a Lobby", nullptr));
        text1->setText(QApplication::translate("StageWaitingRoom", "OR", nullptr));
        text2->setText(QApplication::translate("StageWaitingRoom", "Lobby List", nullptr));
        btnRefresh->setText(QApplication::translate("StageWaitingRoom", "Refresh", nullptr));
        labelWelcome->setText(QApplication::translate("StageWaitingRoom", "TextLabel", nullptr));
        menuHelp->setTitle(QApplication::translate("StageWaitingRoom", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StageWaitingRoom: public Ui_StageWaitingRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGEWAITINGROOM_H
