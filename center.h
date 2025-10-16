#ifndef CENTER_H
#define CENTER_H

#include <QWidget>
#include <QScreen>
#include <QGuiApplication>

inline void centerWindow(QWidget *window)
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    QPoint center = screenGeometry.center();

    QRect frameGm = window->frameGeometry();
    frameGm.moveCenter(center);
    window->move(frameGm.topLeft());
}

#endif
