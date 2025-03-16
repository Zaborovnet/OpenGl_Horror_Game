QT += core gui opengl widgets
CONFIG += c++11

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NightStoreHorror
TEMPLATE = app

SOURCES += main.cpp \
           Environment.cpp \
           Game.cpp \
           MainWindow.cpp \
           Shader.cpp \
           SoundEngine.cpp \
           TextureGenerator.cpp

HEADERS  += \
            Environment.h \
            Game.h \
            MainWindow.h \
            Shader.h \
            SoundEngine.h \
            TextureGenerator.h

FORMS    += MainWindow.ui

FORMS += \
    MainWindow.ui

LIBS += -lGL -lGLU

QMAKE_CXXFLAGS += -std=c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
