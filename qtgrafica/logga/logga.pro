QT -= gui

CONFIG += c++14
LIBS += $$PWD/../../lib/Snap-3.0/snap-core/Snap.o
LIBS += -lrt
LIBS += -fopenmp
SOURCES += mainlog.cpp \
    $$PWD/../grafica.cpp
QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =/Data/data/Qt/5.9.2

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    $$PWD/../grafica.h \
INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../lib/Snap-3.0/snap-core
INCLUDEPATH += $$PWD/../../lib/Snap-3.0/glib-core
INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
unix: CONFIG += link_pkgconfig
unix:!macx: LIBS += -L$$PWD/../../ -lParete
unix:!macx: PRE_TARGETDEPS += $$PWD/../../libParete.a
unix:!macx: LIBS += -L$$PWD/../../ -lEvoluzione
unix:!macx: PRE_TARGETDEPS += $$PWD/../../libEvoluzione.a
unix:!macx: LIBS += -L$$PWD/../../ -lScimmia
unix:!macx: PRE_TARGETDEPS += $$PWD/../../libScimmia.a