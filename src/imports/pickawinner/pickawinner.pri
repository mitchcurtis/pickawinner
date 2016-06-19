HEADERS += \
    $$PWD/saturationlightnesspicker_p.h

SOURCES += \
    $$PWD/saturationlightnesspicker.cpp

QML_CONTROLS = \
    SaturationLightnessPicker.qml

!qtquickcompiler: QML_FILES += $$QML_CONTROLS
