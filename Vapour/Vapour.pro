QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=D:\Cpp\OpenCV-MinGW-Build-OpenCV-4.0.1-x64\include

LIBS+=D:\Cpp\OpenCV-MinGW-Build-OpenCV-4.0.1-x64\x64\mingw\bin\libopencv_core401.dll
LIBS+=D:\Cpp\OpenCV-MinGW-Build-OpenCV-4.0.1-x64\x64\mingw\bin\libopencv_highgui401.dll
LIBS+=D:\Cpp\OpenCV-MinGW-Build-OpenCV-4.0.1-x64\x64\mingw\bin\libopencv_imgproc401.dll
LIBS+=D:\Cpp\OpenCV-MinGW-Build-OpenCV-4.0.1-x64\x64\mingw\bin\libopencv_calib3d401.dll
LIBS+=D:\Cpp\OpenCV-MinGW-Build-OpenCV-4.0.1-x64\x64\mingw\bin\libopencv_imgcodecs401.dll
LIBS+=D:\Cpp\OpenCV-MinGW-Build-OpenCV-4.0.1-x64\x64\mingw\bin\libopencv_videoio401.dll


SOURCES += \
    main.cpp \
    vaction.cpp \
    vcomputethread.cpp \
    vdata.cpp \
    vdescriptor.cpp \
    vedge.cpp \
    vedge_temp.cpp \
    vnode.cpp \
    vscene.cpp \
    vsocket.cpp \
    vview.cpp \
    vwin.cpp

HEADERS += \
    types.h \
    vaction.h \
    vaction_cv.h \
    vaction_develop.h \
    vcomputethread.h \
    vdata.h \
    vdescriptor.h \
    vdescriptor_cv.h \
    vdescriptor_develop.h \
    vedge.h \
    vedge_temp.h \
    vnode.h \
    vnode_cv.h \
    vnode_develop.h \
    vscene.h \
    vsocket.h \
    vview.h \
    vwin.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
