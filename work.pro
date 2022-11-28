QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bookdialog.cpp \
    booklist.cpp \
    chpwd.cpp \
    history.cpp \
    infochange.cpp \
    main.cpp \
    mainwindow.cpp \
    photo.cpp \
    usermanagement.cpp

HEADERS += \
    BookDao.h \
    FileWork.h \
    Model.h \
    Tool.h \
    UserDao.h \
    bookdialog.h \
    booklist.h \
    chpwd.h \
    history.h \
    infochange.h \
    login.h \
    mainwindow.h \
    photo.h \
    registerwindow.h \
    usermanagement.h

FORMS += \
    bookdialog.ui \
    booklist.ui \
    chpwd.ui \
    history.ui \
    infochange.ui \
    login.ui \
    mainwindow.ui \
    photo.ui \
    registerwindow.ui \
    usermanagement.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES +=
