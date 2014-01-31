QT += core
DESTDIR = $$PWD
OBJECTS_DIR = .obj
MOC_DIR = .moc

HEADERS += EvManGlobal.h \
           GenericParser.h

SOURCES += EvManGlobal.cpp \
           main.cpp \
           GenericParser.cpp

QMAKE_CXXFLAGS += -std=c++11
