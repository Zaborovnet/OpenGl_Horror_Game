QT += core gui opengl widgets
CONFIG += c++11

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NightStoreHorror
TEMPLATE = app

SOURCES += main.cpp \
           MainWindow.cpp \
           audio/SoundEngine.cpp \
           core/Environment.cpp \
           core/Game.cpp \
           core/PlayerState.cpp \
           rendering/Shader.cpp \
           rendering/TextureGenerator.cpp

HEADERS  += \
            MainWindow.h \
            audio/SoundEngine.h \
            core/Environment.h \
            core/Game.h \
            core/PlayerState.h \
            rendering/Shader.h \
            rendering/TextureGenerator.h

FORMS    += MainWindow.ui

FORMS += \
    MainWindow.ui

LIBS += -lGL -lGLU

QMAKE_CXXFLAGS += -std=c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
