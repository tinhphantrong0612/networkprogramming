QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth.cpp \
    castle.cpp \
    game.cpp \
    lobby.cpp \
    main.cpp \
    mine.cpp \
    player.cpp \
    question.cpp \
    response.cpp \
    stagegame.cpp \
    stagelogin.cpp \
    stageprepare.cpp \
    stagewaitingroom.cpp \
    stream.cpp \
    team.cpp \
    thread_receive.cpp \
    uitranslate.cpp \
    util.cpp \
    wall.cpp \
    weapon.cpp

HEADERS += \
    auth.h \
    castle.h \
    constant.h \
    game.h \
    lobby.h \
    mine.h \
    player.h \
    question.h \
    response.h \
    stagegame.h \
    stagelogin.h \
    stageprepare.h \
    stagewaitingroom.h \
    stream.h \
    team.h \
    thread_receive.h \
    uitextconst.h \
    uitranslate.h \
    util.h \
    wall.h \
    weapon.h

FORMS += \
    stagegame.ui \
    stagelogin.ui \
    stageprepare.ui \
    stagewaitingroom.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    asset.qrc
