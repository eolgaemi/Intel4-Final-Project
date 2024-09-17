QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwidget.cpp \
    stftcpserver.cpp \
    stfudpserver.cpp \
    tab1controlpannel.cpp \
    tab2potstatuspannel.cpp \
    tab3turtlebotcontrolpannel.cpp \
    tab4adminlogin.cpp \
    tab4adminpannel.cpp

HEADERS += \
    mainwidget.h \
    stftcpserver.h \
    stfudpserver.h \
    tab1controlpannel.h \
    tab2potstatuspannel.h \
    tab3turtlebotcontrolpannel.h \
    tab4adminlogin.h \
    tab4adminpannel.h

FORMS += \
    mainwidget.ui \
    tab1controlpannel.ui \
    tab2potstatuspannel.ui \
    tab3turtlebotcontrolpannel.ui \
    tab4adminlogin.ui \
    tab4adminpannel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    STF_Image.qrc
