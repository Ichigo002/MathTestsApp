QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_FILE = MathTester.rc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogsettinginput.cpp \
    main.cpp \
    mainwindow.cpp \
    windialog.cpp

HEADERS += \
    EnumsStructs.h \
    dialogsettinginput.h \
    mainwindow.h \
    windialog.h

FORMS += \
    dialogsettinginput.ui \
    mainwindow.ui \
    windialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
