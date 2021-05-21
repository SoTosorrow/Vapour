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
    node_data.cpp \
    node_edge.cpp \
    node_edge_temp.cpp \
    node_inter.cpp \
    node_item.cpp \
    node_socket.cpp \
    shader/node_shader.cpp \
    shader/node_shader_content.cpp \
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
    editor_scene.h \
    editor_view.h \
    editor_win.h \
    node.h \
    node_data.h \
    node_edge.h \
    node_edge_temp.h \
    node_inter.h \
    node_item.h \
    node_socket.h \
    vapour_action.h \
    vapour_action_develop.h \
    vapour_descriptor.h \
    vapour_edge.h \
    vapour_edge_temp.h \
    vapour_node.h \
    vapour_node_develop.h \
    vapour_scene.h \
    vapour_socket.h \
    types.h \
    shader/node_shader.h \
    shader/node_shader_content.h \
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
