#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QtCore/qurl.h>
#include <QtCore/qfile.h>
#include <QtCore/qcoreapplication.h>
#include <QtCore/private/qfileselector_p.h>

#include <QtQuickControls2/qquickstyle.h>
#include <QtQuickControls2/private/qquickstyleplugin_p.h>
#include <QtQuickControls2/private/qquickstyleselector_p.h>

#include "saturationlightnesspicker_p.h"

//static inline void initResources()
//{
//    Q_INIT_RESOURCE(pickawinnerplugin);
//#ifdef QT_STATIC
//    Q_INIT_RESOURCE(qmake_QtQuick_PickAWinner);
//#endif
//}

class PickAWinnerPlugin: public QQuickStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    PickAWinnerPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri);
    void initializeEngine(QQmlEngine *engine, const char *uri);
};

PickAWinnerPlugin::PickAWinnerPlugin(QObject *parent) : QQuickStylePlugin(parent)
{
//    initResources();
}

void PickAWinnerPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<SaturationLightnessPicker>(uri, 1, 0, "SaturationLightnessPickerTemplate");

    QQuickStyleSelector selector;
    selector.setBaseUrl(typeUrl());

    const QString style = QQuickStyle::name();
    if (!style.isEmpty())
        QFileSelectorPrivate::addStatics(QStringList() << style.toLower());

    qmlRegisterType(selector.select(QStringLiteral("SaturationLightnessPicker.qml")), uri, 1, 0, "SaturationLightnessPicker");
}

void PickAWinnerPlugin::initializeEngine(QQmlEngine *, const char *)
{
}

#include "pickawinnerplugin.moc"
