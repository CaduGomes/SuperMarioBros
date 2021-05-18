QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background_image.cpp \
    brick_block.cpp \
    coin_object.cpp \
    flag_object.cpp \
    floor_block.cpp \
    game.cpp \
    gamedirector.cpp \
    goomba_mob.cpp \
    main.cpp \
    mushroom_object.cpp \
    mystery_block.cpp \
    pipe_block.cpp \
    player.cpp

HEADERS += \
    background_image.h \
    brick_block.h \
    coin_object.h \
    flag_object.h \
    floor_block.h \
    game.h \
    gamedirector.h \
    goomba_mob.h \
    iobserver.h \
    isubject.h \
    mushroom_object.h \
    mystery_block.h \
    pipe_block.h \
    player.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
