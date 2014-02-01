QT += core
DESTDIR = $$PWD
OBJECTS_DIR = .obj
MOC_DIR = .moc

HEADERS += EvManGlobal.h \
           GenericParser.h \
           TProtocolsInfoTable.h \
           TMetaRuleInfos.h \
           TRule.h \
           TBackends.h

SOURCES += EvManGlobal.cpp \
           main.cpp \
           GenericParser.cpp \
           TProtocolsInfoTable.cpp \
           TMetaRuleInfos.cpp \
           TRule.cpp \
           TBackends.cpp

QMAKE_CXXFLAGS += -std=c++11
