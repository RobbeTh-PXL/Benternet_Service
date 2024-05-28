QT = core

CONFIG += c++17 cmdline

DEFINES += ZMQ_STATIC
LIBS += -lzmq -lcpprest -lssl -lcrypto

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        connection_zmq.cpp \
        handler_message.cpp \
        main.cpp \
        service_translator.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    connection_zmq.h \
    handler_message.h \
    service_translator.h
