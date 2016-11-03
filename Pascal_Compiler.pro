TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    scanner.c \
    parser.c

HEADERS += \
    scanner.h \
    parser.h \
    header.h
