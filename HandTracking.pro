QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
        videothread.cpp

HEADERS  += mainwindow.h \
    videothread.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\opencv\build\include

LIBS += C:\opencv\release\bin\libopencv_core490.dll
LIBS += C:\opencv\release\bin\libopencv_highgui490.dll
LIBS += C:\opencv\release\bin\libopencv_imgcodecs490.dll
LIBS += C:\opencv\release\bin\libopencv_imgproc490.dll
LIBS += C:\opencv\release\bin\libopencv_features2d490.dll
LIBS += C:\opencv\release\bin\libopencv_calib3d490.dll
LIBS += C:\opencv\release\bin\libopencv_videoio490.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
