#-------------------------------------------------
#
# Project created by QtCreator 2021-09-29T16:02:18
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += serialport
QT += charts
TARGET = ActuatorControl_1_0
TEMPLATE = app






# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    golbal.cpp \
        main.cpp \
        mainwindow.cpp \
    actuator_control_interface.cpp \
    server.cpp \
    uart_frame_communication_protocol.cpp \
    serial.cpp \
    dialognotice.cpp

HEADERS += \
    global.h \
        mainwindow.h \
    actuator_control_interface.h \
    server.h \
    uart_frame_communication_protocol.h \
    serial.h \
    dialognotice.h

FORMS += \
        mainwindow.ui \
    dialognotice.ui
