QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/rosnode.cpp \
    src/socketclient.cpp \
    src/stftcpserver.cpp \
    src/stfudpserver.cpp \
    src/tab1controlpannel.cpp \
    src/tab2potstatuspannel.cpp \
    src/tab3turtlebotcontrolpannel.cpp \
    src/tab4adminlogin.cpp \
    src/tab4adminpannel.cpp

HEADERS += \
    include/smart_turtle_farm/mainwidget.h \
    include/smart_turtle_farm/rosnode.h \
    include/smart_turtle_farm/socketclient.h \
    include/smart_turtle_farm/stftcpserver.h \
    include/smart_turtle_farm/stfudpserver.h \
    include/smart_turtle_farm/tab1controlpannel.h \
    include/smart_turtle_farm/tab2potstatuspannel.h \
    include/smart_turtle_farm/tab3turtlebotcontrolpannel.h \
    include/smart_turtle_farm/tab4adminlogin.h \
    include/smart_turtle_farm/tab4adminpannel.h

FORMS += \
    ui/mainwidget.ui \
    ui/tab1controlpannel.ui \
    ui/tab2potstatuspannel.ui \
    ui/tab3turtlebotcontrolpannel.ui \
    ui/tab4adminlogin.ui \
    ui/tab4adminpannel.ui

INCLUDEPATH += /opt/ros/noetic/include

RESOURCES += \
    STF_Image.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


