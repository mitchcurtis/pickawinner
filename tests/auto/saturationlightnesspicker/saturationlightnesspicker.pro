TEMPLATE = app
TARGET = tst_saturationlightnesspicker
CONFIG += qmltestcase

DEFINES += TST_DATA=\\\"$$PAW_SOURCE_TREE/tests/auto/saturationlightnesspicker/data\\\"

SOURCES += \
    $$PWD/tst_saturationlightnesspicker.cpp

OTHER_FILES += \
    $$PWD/data/*

TESTDATA += \
    $$PWD/data/tst_*
