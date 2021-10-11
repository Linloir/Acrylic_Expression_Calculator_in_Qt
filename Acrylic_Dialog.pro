QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ConvertFunc.cpp \
    additiontabwidget.cpp \
    hashmap.cpp \
    historypage.cpp \
    infopage.cpp \
    main.cpp \
    acrylic.cpp \
    qtransparentbutton.cpp \
    scrollareacustom.cpp \
    scrollindicator.cpp \
    scrolllistcontainer.cpp \
    stackpage.cpp \
    tabicons.cpp \
    tabindicator.cpp \
    tabpage.cpp

HEADERS += \
    ConvertFunc.h \
    Stack.h \
    WindowCompositionAttribute.h \
    acrylic.h \
    additiontabwidget.h \
    hashmap.h \
    historypage.h \
    infopage.h \
    qtransparentbutton.h \
    scrollareacustom.h \
    scrollindicator.h \
    scrolllistcontainer.h \
    stackpage.h \
    tabicons.h \
    tabindicator.h \
    tabpage.h

FORMS += \
    acrylic.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
