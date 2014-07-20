#-------------------------------------------------
#
# Project created by QtCreator 2013-03-09T20:36:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timeWatcher
TEMPLATE = app

target.path = /usr/bin/
target.files += timeWatcher

autostart.path = /etc/xdg/autostart
autostart.files += timeWatcher.py

shortcutfiles.files += admin-gui.desktop timeWatcher.desktop
shortcutfiles.path = /usr/share/applications/

python.path = /usr/bin/
python.files += timeDaemon.py

directory.path = /etc/
directory.commands = mkdir /etc/timeWatcher

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INSTALLS += target
INSTALLS += shortcutfiles
INSTALLS += python
INSTALLS += autostart
INSTALLS += directory
