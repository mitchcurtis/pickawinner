TEMPLATE = app
TARGET = basic
QT += quick quickcontrols2

SOURCES += \
    basic.cpp

OTHER_FILES += \
    basic.qml

RESOURCES += \
    basic.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/pickawinner/basic
INSTALLS += target
