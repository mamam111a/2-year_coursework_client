QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_item.cpp \
    add_shop.cpp \
    adminmenu.cpp \
    delete_item.cpp \
    delete_shop.cpp \
    finditem_admin.cpp \
    finditem_result.cpp \
    finditem_user.cpp \
    findshop_admin.cpp \
    globals.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    regwindow.cpp \
    update_item.cpp \
    update_shop.cpp \
    user_menu.cpp

HEADERS += \
    add_item.h \
    add_shop.h \
    adminmenu.h \
    center.h \
    delete_item.h \
    delete_shop.h \
    finditem_admin.h \
    finditem_result.h \
    finditem_user.h \
    findshop_admin.h \
    globals.h \
    loginwindow.h \
    mainwindow.h \
    regwindow.h \
    sendInfo.h \
    update_item.h \
    update_shop.h \
    user_menu.h

FORMS += \
    add_item.ui \
    add_shop.ui \
    adminmenu.ui \
    delete_item.ui \
    delete_shop.ui \
    finditem_admin.ui \
    finditem_result.ui \
    finditem_user.ui \
    findshop_admin.ui \
    loginwindow.ui \
    mainwindow.ui \
    regwindow.ui \
    update_item.ui \
    update_shop.ui \
    user_menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
