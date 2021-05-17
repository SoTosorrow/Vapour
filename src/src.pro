QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editor_scene.cpp \
    editor_view.cpp \
    editor_win.cpp \
    main.cpp \
    node.cpp \
    node_edge.cpp \
    node_edge_temp.cpp \
    node_item.cpp \
    node_socket.cpp

HEADERS += \
    editor_scene.h \
    editor_view.h \
    editor_win.h \
    node.h \
    node_edge.h \
    node_edge_temp.h \
    node_item.h \
    node_socket.h \
    types.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    ../README.md \
    ../reply/nodestyle.qss
