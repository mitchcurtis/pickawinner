#include <QtQml/qqmlextensionplugin.h>

#include <QtQuickControls2/qquickstyle.h>

#include "saturationlightnesspicker_p.h"

//static inline void initResources()
//{
//    Q_INIT_RESOURCE(pickawinnerplugin);
//#ifdef QT_STATIC
//    Q_INIT_RESOURCE(qmake_QtQuick_PickAWinner);
//#endif
//}

class PickAWinnerPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    PickAWinnerPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri);
    void initializeEngine(QQmlEngine *engine, const char *uri);
};

PickAWinnerPlugin::PickAWinnerPlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{
//    initResources();
}

void PickAWinnerPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<SaturationLightnessPicker>(uri, 1, 0, "SaturationLightnessPickerTemplate");

    qmlRegisterType(QUrl::fromLocalFile(baseUrl().toLocalFile() + QStringLiteral("/SaturationLightnessPicker.qml")),
        uri, 1, 0, "SaturationLightnessPicker");
}

void PickAWinnerPlugin::initializeEngine(QQmlEngine *, const char *)
{
}

#include "pickawinnerplugin.moc"
