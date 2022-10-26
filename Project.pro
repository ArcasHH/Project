QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battle.cpp \
    createfield.cpp \
    enemyfields.cpp \
    main.cpp \
    menu.cpp \
    recieverwindow.cpp \
    senderwindow.cpp \
    server.cpp

HEADERS += \
    AIPlayer.h \
    FieldCell.h \
    SharedDeata.h \
    battle.h \
    communicator.h \
    createfield.h \
    enemyfields.h \
    menu.h \
    point.h \
    recieverwindow.h \
    senderwindow.h \
    server.h

FORMS += \
    battle.ui \
    createfield.ui \
    menu.ui \
    recieverwindow.ui \
    senderwindow.ui \
    server.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
