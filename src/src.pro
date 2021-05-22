QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    vapour_action.cpp \
    vapour_demo.cpp \
    vapour_descriptor.cpp \
    vapour_edge.cpp \
    vapour_edge_temp.cpp \
    vapour_node.cpp \
    vapour_scene.cpp \
    vapour_socket.cpp \
    vapour_data.cpp \
    vapour_view.cpp \
    vapour_win.cpp

HEADERS += \
    vapour_action.h \
    vapour_action_develop.h \
    vapour_descriptor.h \
    vapour_descriptor_develop.h \
    vapour_edge.h \
    vapour_edge_temp.h \
    vapour_node.h \
    vapour_node_develop.h \
    vapour_scene.h \
    vapour_socket.h \
    types.h \
    vapour_data.h \
    vapour_types.h \
    vapour_view.h \
    vapour_win.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    ../README.md \
    ../reply/nodestyle.qss
