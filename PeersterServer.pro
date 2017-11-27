QT += core
QT -= gui
QT += network core gui

CONFIG += c++11

TARGET = PeersterServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    controller.cpp \
    serversocket.cpp \
    friendrelation.cpp \
    ratingcalculator.cpp \
    rating.cpp

HEADERS += \
    controller.h \
    serversocket.h \
    friendrelation.h \
    config.h \
    ratingcalculator.h \
    rating.h
