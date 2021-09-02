/********************************************************************************
** Form generated from reading UI file 'stagelogin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGELOGIN_H
#define UI_STAGELOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StageLogin
{
public:
    QWidget *centralwidget;
    QLabel *labelStatus;
    QPushButton *btnLogin;
    QPushButton *btnRegister;
    QLabel *text1;
    QLabel *text2;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QLabel *text_SignIn;
    QPushButton *btnRetry;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StageLogin)
    {
        if (StageLogin->objectName().isEmpty())
            StageLogin->setObjectName(QString::fromUtf8("StageLogin"));
        StageLogin->setWindowModality(Qt::WindowModal);
        StageLogin->resize(600, 330);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StageLogin->sizePolicy().hasHeightForWidth());
        StageLogin->setSizePolicy(sizePolicy);
        StageLogin->setAutoFillBackground(false);
        StageLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        centralwidget = new QWidget(StageLogin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setGeometry(QRect(130, 70, 340, 35));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelStatus->setFont(font);
        labelStatus->setAlignment(Qt::AlignCenter);
        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(150, 250, 120, 35));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(9);
        btnLogin->setFont(font1);
        btnLogin->setStyleSheet(QString::fromUtf8(""));
        btnRegister = new QPushButton(centralwidget);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        btnRegister->setGeometry(QRect(330, 250, 120, 35));
        btnRegister->setFont(font1);
        btnRegister->setStyleSheet(QString::fromUtf8(""));
        text1 = new QLabel(centralwidget);
        text1->setObjectName(QString::fromUtf8("text1"));
        text1->setGeometry(QRect(130, 130, 100, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        text1->setFont(font2);
        text2 = new QLabel(centralwidget);
        text2->setObjectName(QString::fromUtf8("text2"));
        text2->setGeometry(QRect(130, 180, 100, 30));
        text2->setFont(font2);
        txtUsername = new QLineEdit(centralwidget);
        txtUsername->setObjectName(QString::fromUtf8("txtUsername"));
        txtUsername->setGeometry(QRect(250, 130, 220, 30));
        txtPassword = new QLineEdit(centralwidget);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(250, 180, 220, 30));
        txtPassword->setEchoMode(QLineEdit::Password);
        text_SignIn = new QLabel(centralwidget);
        text_SignIn->setObjectName(QString::fromUtf8("text_SignIn"));
        text_SignIn->setGeometry(QRect(200, 20, 200, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Candara"));
        font3.setPointSize(18);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        text_SignIn->setFont(font3);
        text_SignIn->setAlignment(Qt::AlignCenter);
        btnRetry = new QPushButton(centralwidget);
        btnRetry->setObjectName(QString::fromUtf8("btnRetry"));
        btnRetry->setGeometry(QRect(470, 75, 50, 25));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto"));
        font4.setPointSize(8);
        font4.setBold(true);
        font4.setWeight(75);
        btnRetry->setFont(font4);
        btnRetry->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        background-color: #00cccc;\n"
"        color: #fff7e6 ;\n"
"        border-radius: 10;\n"
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
"}"));
        StageLogin->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(StageLogin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StageLogin->setStatusBar(statusbar);

        retranslateUi(StageLogin);

        QMetaObject::connectSlotsByName(StageLogin);
    } // setupUi

    void retranslateUi(QMainWindow *StageLogin)
    {
        StageLogin->setWindowTitle(QApplication::translate("StageLogin", "StageLogin", nullptr));
        labelStatus->setText(QApplication::translate("StageLogin", "Status", nullptr));
        btnLogin->setText(QApplication::translate("StageLogin", "Login", nullptr));
        btnRegister->setText(QApplication::translate("StageLogin", "Register", nullptr));
        text1->setText(QApplication::translate("StageLogin", "Username", nullptr));
        text2->setText(QApplication::translate("StageLogin", "Password", nullptr));
        text_SignIn->setText(QApplication::translate("StageLogin", "SIGN IN", nullptr));
        btnRetry->setText(QApplication::translate("StageLogin", "Retry", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StageLogin: public Ui_StageLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGELOGIN_H
