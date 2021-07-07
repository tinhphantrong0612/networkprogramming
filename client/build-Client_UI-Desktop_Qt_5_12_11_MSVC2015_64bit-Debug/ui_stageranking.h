/********************************************************************************
** Form generated from reading UI file 'stageranking.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAGERANKING_H
#define UI_STAGERANKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StageRanking
{
public:
    QLabel *text1;
    QLabel *text2;
    QLabel *text1_2;
    QLabel *text1_3;

    void setupUi(QWidget *StageRanking)
    {
        if (StageRanking->objectName().isEmpty())
            StageRanking->setObjectName(QString::fromUtf8("stageranking"));
        StageRanking->resize(480, 400);
        StageRanking->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        text1 = new QLabel(StageRanking);
        text1->setObjectName(QString::fromUtf8("text1"));
        text1->setGeometry(QRect(90, 20, 300, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        text1->setFont(font);
        text1->setAlignment(Qt::AlignCenter);
        text2 = new QLabel(StageRanking);
        text2->setObjectName(QString::fromUtf8("text2"));
        text2->setGeometry(QRect(40, 350, 400, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        text2->setFont(font1);
        text2->setAlignment(Qt::AlignCenter);
        text1_2 = new QLabel(StageRanking);
        text1_2->setObjectName(QString::fromUtf8("text1_2"));
        text1_2->setGeometry(QRect(90, 70, 300, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(18);
        font2.setBold(false);
        font2.setWeight(50);
        text1_2->setFont(font2);
        text1_2->setAlignment(Qt::AlignCenter);
        text1_3 = new QLabel(StageRanking);
        text1_3->setObjectName(QString::fromUtf8("text1_3"));
        text1_3->setGeometry(QRect(90, 200, 300, 40));
        text1_3->setFont(font2);
        text1_3->setAlignment(Qt::AlignCenter);

        retranslateUi(StageRanking);

        QMetaObject::connectSlotsByName(StageRanking);
    } // setupUi

    void retranslateUi(QWidget *stageranking)
    {
        stageranking->setWindowTitle(QApplication::translate("stageranking", "Form", nullptr));
        text1->setText(QApplication::translate("stageranking", "The game has ended !", nullptr));
        text2->setText(QApplication::translate("stageranking", "* auto return to waiting room after close this", nullptr));
        text1_2->setText(QApplication::translate("stageranking", "Winner", nullptr));
        text1_3->setText(QApplication::translate("stageranking", "Runner-up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StageRanking: public Ui_StageRanking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAGERANKING_H
