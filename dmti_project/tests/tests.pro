# tests/tests.pro
QT += core testlib
CONFIG += c++17 console
CONFIG -= app_bundle
TEMPLATE = app
TARGET = test

SOURCES += ../logic/natural.cpp \
           ../logic/integer.cpp \
           ../logic/rational.cpp \
           ../logic/polinomial.cpp \
           generalTest.cpp

HEADERS += ../logic/natural.h \
           ../logic/integer.h \
           ../logic/rational.h \
           ../logic/polinomial.h \
           ../logic/number_structures.h

INCLUDEPATH += ../logic
