#include "saturationlightnesspicker_p.h"

#include <QtQuickTemplates2/private/qquickcontrol_p_p.h>

QT_BEGIN_NAMESPACE

/*!
    \qmltype SaturationLightnessPicker
    \inherits Control
    \instantiates SaturationLightnessPicker
    \inqmlmodule QtQuick.Controls
    \ingroup qtquickcontrols2-input
    \brief Provides a way to select both saturation and lightness simultaneously.

    \image qtquickcontrols2-slider.gif

    \code
    SaturationLightnessPicker {
    }
    \endcode

    \sa {Customizing SaturationLightnessPicker}, {Input Controls}
*/

/*!
    \qmlsignal QtQuick.Controls::SaturationLightnessPicker::colorPicked()

    This signal is emitted when the colour is picked or changed by the user interactively.
*/

class SaturationLightnessPickerPrivate : public QQuickControlPrivate
{
    Q_DECLARE_PUBLIC(SaturationLightnessPicker)

public:
    SaturationLightnessPickerPrivate() :
        hue(0),
        saturation(0),
        lightness(0),
        alpha(0),
        pressed(false),
        handle(nullptr)
    {
    }

    void setHandleZ();
    qreal saturationAt(const QPointF &pos) const;
    qreal lightnessAt(const QPointF &pos) const;

    enum ColorChangedEmission {
        DontEmitColorChanged,
        EmitColorChanged
    };

    enum ColorPickedEmission {
        DontEmitColorPicked,
        EmitColorPicked
    };

    bool setHue(qreal hue, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked);
    bool setSaturation(qreal saturation, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked);
    bool setLightness(qreal lightness, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked);
    bool setAlpha(qreal alpha, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked);

    qreal hue;
    qreal saturation;
    qreal lightness;
    qreal alpha;
    bool pressed;
    QPointF pressPoint;
    QQuickItem *handle;
};

void SaturationLightnessPickerPrivate::setHandleZ()
{
    if (qFuzzyIsNull(handle->z())) {
        if (contentItem)
            handle->setZ(contentItem->z() + 1);
        else if (background)
            handle->setZ(background->z() + 1);
    }
}

qreal SaturationLightnessPickerPrivate::saturationAt(const QPointF &pos) const
{
    if (pos.y() < 0)
        return 1.0;

    if (pos.y() >= height)
        return 0.0;

    return 1.0 - pos.y() / height;
}

qreal SaturationLightnessPickerPrivate::lightnessAt(const QPointF &pos) const
{
    if (pos.x() < 0)
        return 0.0;

    if (pos.x() >= width)
        return 1.0;

    return pos.x() / width;
}

bool SaturationLightnessPickerPrivate::setHue(qreal hue, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked)
{
    hue = qBound(0.0, hue, 360.0);

    if (qFuzzyCompare(this->hue, hue))
        return false;

    this->hue = hue;

    Q_Q(SaturationLightnessPicker);
    emit q->hueChanged();
    if (emitColorChanged == EmitColorChanged)
        emit q->colorChanged();
    if (emitColorPicked == EmitColorPicked)
        emit q->colorPicked();
    return true;
}

bool SaturationLightnessPickerPrivate::setSaturation(qreal saturation, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked)
{
    saturation = qBound(0.0, saturation, 1.0);

    if (qFuzzyCompare(this->saturation, saturation))
        return false;

    this->saturation = saturation;

    if (handle)
        handle->setY((1.0 - this->saturation) * height - handle->height() / 2);

    Q_Q(SaturationLightnessPicker);
    emit q->saturationChanged();
    if (emitColorChanged == EmitColorChanged)
        emit q->colorChanged();
    if (emitColorPicked == EmitColorPicked)
        emit q->colorPicked();
    return true;
}

bool SaturationLightnessPickerPrivate::setLightness(qreal lightness, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked)
{
    lightness = qBound(0.0, lightness, 1.0);

    if (qFuzzyCompare(this->lightness, lightness))
        return false;

    this->lightness = lightness;

    if (handle)
        handle->setX(this->lightness * width - handle->width() / 2);

    Q_Q(SaturationLightnessPicker);
    emit q->lightnessChanged();
    if (emitColorChanged == EmitColorChanged)
        emit q->colorChanged();
    if (emitColorPicked == EmitColorPicked)
        emit q->colorPicked();
    return true;
}

bool SaturationLightnessPickerPrivate::setAlpha(qreal alpha, ColorChangedEmission emitColorChanged, ColorPickedEmission emitColorPicked)
{
    alpha = qBound(0.0, alpha, 1.0);
    if (this->alpha == alpha)
        return false;

    Q_Q(SaturationLightnessPicker);
    this->alpha = alpha;
    emit q->alphaChanged();
    if (emitColorChanged == EmitColorChanged)
        emit q->colorChanged();
    if (emitColorPicked == EmitColorPicked)
        emit q->colorPicked();
    return true;
}

SaturationLightnessPicker::SaturationLightnessPicker(QQuickItem *parent) :
    QQuickControl(*(new SaturationLightnessPickerPrivate), parent)
{
    setActiveFocusOnTab(true);
    setFocusPolicy(Qt::StrongFocus);
    setAcceptedMouseButtons(Qt::LeftButton);
}

/*!
    \qmlproperty real PickAWinner::SaturationLightnessPicker::hue

    This property controls the hue of the colors that are displayed on the
    picker. It is typically bound to a hue slider:

    TODO: un-uglify slider

    \qml
    import QtQuick 2.6
    import QtQuick.Layouts 1.0
    import QtQuick.Controls 2.0

    ApplicationWindow {
        width: layout.implicitWidth + 40
        height: layout.implicitHeight + 40
        visible: true

        RowLayout {
            id: layout
            spacing: 10
            anchors.centerIn: parent

            Slider {
                id: hueSlider
                from: 1
                to: 0
                orientation: Qt.Vertical
                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 200

                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "#ff0000"
                        }
                        GradientStop {
                            position: 0.166666
                            color: "#ffff00"
                        }
                        GradientStop {
                            position: 0.333333
                            color: "#00ff00"
                        }
                        GradientStop {
                            position: 0.5
                            color: "#00ffff"
                        }
                        GradientStop {
                            position: 0.666666
                            color: "#0000ff"
                        }
                        GradientStop {
                            position: 0.833333
                            color: "#ff00ff"
                        }
                        GradientStop {
                            position: 1
                            color: "#ff0000"
                        }
                    }
                }
            }
            SaturationLightnessPicker {
                id: picker
                hue: hueSlider.value
            }
        }
    }
    \endqml

    The default value is \c 0.0.

    \sa saturation, lightness
*/
qreal SaturationLightnessPicker::hue() const
{
    Q_D(const SaturationLightnessPicker);
    return d->hue;
}

void SaturationLightnessPicker::setHue(qreal hue)
{
    Q_D(SaturationLightnessPicker);
    d->setHue(hue, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::DontEmitColorPicked);
}

/*!
    \qmlproperty real PickAWinner::SaturationLightnessPicker::saturation

    This property holds the saturation.

    The default value is \c 0.0.

    \sa lightness, hue
*/
qreal SaturationLightnessPicker::saturation() const
{
    Q_D(const SaturationLightnessPicker);
    return d->saturation;
}

void SaturationLightnessPicker::setSaturation(qreal saturation)
{
    Q_D(SaturationLightnessPicker);
    d->setSaturation(saturation, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::DontEmitColorPicked);
}

/*!
    \qmlproperty real PickAWinner::SaturationLightnessPicker::lightness

    This property holds the lightness.

    The default value is \c 0.0.

    \sa saturation, hue
*/
qreal SaturationLightnessPicker::lightness() const
{
    Q_D(const SaturationLightnessPicker);
    return d->lightness;
}

void SaturationLightnessPicker::setLightness(qreal lightness)
{
    Q_D(SaturationLightnessPicker);
    d->setLightness(lightness, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::DontEmitColorPicked);
}

/*!
    \qmlproperty real PickAWinner::SaturationLightnessPicker::alpha

    This property holds the alpha.

    The default value is \c 0.0.

    \sa hue, saturation, lightness
*/
qreal SaturationLightnessPicker::alpha() const
{
    Q_D(const SaturationLightnessPicker);
    return d->alpha;
}

void SaturationLightnessPicker::setAlpha(qreal alpha)
{
    Q_D(SaturationLightnessPicker);
    d->setAlpha(alpha, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::DontEmitColorPicked);
}

QColor SaturationLightnessPicker::color() const
{
    Q_D(const SaturationLightnessPicker);
    return QColor::fromHslF(d->hue, d->saturation, d->lightness, d->alpha);
}

void SaturationLightnessPicker::setColor(const QColor &color)
{
    Q_D(SaturationLightnessPicker);
    if (this->color() == color)
        return;

    QColor hsl = color.toHsl();
    auto dontEmitColorChanged = SaturationLightnessPickerPrivate::DontEmitColorChanged;
    auto dontEmitColorPicked = SaturationLightnessPickerPrivate::DontEmitColorPicked;

    d->setHue(hsl.hslHueF(), dontEmitColorChanged, dontEmitColorPicked);
    d->setSaturation(hsl.hslSaturationF(), dontEmitColorChanged, dontEmitColorPicked);
    d->setLightness(hsl.lightnessF(), dontEmitColorChanged, dontEmitColorPicked);
    d->setAlpha(color.alphaF(), dontEmitColorChanged, dontEmitColorPicked);

    emit colorChanged();
}

/*!
    \qmlproperty bool PickAWinner::SaturationLightnessPicker::pressed

    This property holds whether the slider is pressed.
*/
bool SaturationLightnessPicker::isPressed() const
{
    Q_D(const SaturationLightnessPicker);
    return d->pressed;
}

void SaturationLightnessPicker::setPressed(bool pressed)
{
    Q_D(SaturationLightnessPicker);
    if (d->pressed == pressed)
        return;

    d->pressed = pressed;
    setAccessibleProperty("pressed", pressed);
    emit pressedChanged();
}

/*!
    \qmlproperty Item PickAWinner::SaturationLightnessPicker::handle

    This property holds the handle item.

    \sa {Customizing Slider}
*/
QQuickItem *SaturationLightnessPicker::handle() const
{
    Q_D(const SaturationLightnessPicker);
    return d->handle;
}

void SaturationLightnessPicker::setHandle(QQuickItem *handle)
{
    Q_D(SaturationLightnessPicker);
    if (d->handle == handle)
        return;

    delete d->handle;
    d->handle = handle;

    if (d->handle) {
        if (!d->handle->parentItem())
            d->handle->setParentItem(this);

        d->setHandleZ();
    }

    emit handleChanged();
}

static const qreal changeAmount = 0.01;

void SaturationLightnessPicker::increaseSaturation()
{
    Q_D(SaturationLightnessPicker);
    d->setSaturation(d->saturation + changeAmount, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::EmitColorPicked);
}

void SaturationLightnessPicker::decreaseSaturation()
{
    Q_D(SaturationLightnessPicker);
    d->setSaturation(d->saturation - changeAmount, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::EmitColorPicked);
}

void SaturationLightnessPicker::increaseLightness()
{
    Q_D(SaturationLightnessPicker);
    d->setLightness(d->lightness + changeAmount, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::EmitColorPicked);
}

void SaturationLightnessPicker::decreaseLightness()
{
    Q_D(SaturationLightnessPicker);
    d->setLightness(d->lightness - changeAmount, SaturationLightnessPickerPrivate::EmitColorChanged,
        SaturationLightnessPickerPrivate::EmitColorPicked);
}

void SaturationLightnessPicker::componentComplete()
{
    Q_D(SaturationLightnessPicker);
    QQuickControl::componentComplete();
    d->setHandleZ();
}

void SaturationLightnessPicker::keyPressEvent(QKeyEvent *event)
{
    QQuickControl::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_Left:
        setPressed(true);
        if (isMirrored())
            increaseLightness();
        else
            decreaseLightness();
        event->accept();
        break;
    case Qt::Key_Right:
        setPressed(true);
        if (isMirrored())
            decreaseLightness();
        else
            increaseLightness();
        event->accept();
        break;
    case Qt::Key_Up:
        setPressed(true);
        increaseSaturation();
        event->accept();
        break;
    case Qt::Key_Down:
        setPressed(true);
        decreaseSaturation();
        event->accept();
        break;
    }
}

void SaturationLightnessPicker::keyReleaseEvent(QKeyEvent *event)
{
    QQuickControl::keyReleaseEvent(event);
    setPressed(false);
}

void SaturationLightnessPicker::mousePressEvent(QMouseEvent *event)
{
    Q_D(SaturationLightnessPicker);
    QQuickControl::mousePressEvent(event);
    d->pressPoint = event->pos();
    setPressed(true);

    updateValuesForPos(event->pos());
}

void SaturationLightnessPicker::mouseMoveEvent(QMouseEvent *event)
{
    QQuickControl::mouseMoveEvent(event);

    updateValuesForPos(event->pos());
}

void SaturationLightnessPicker::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(SaturationLightnessPicker);
    QQuickControl::mouseReleaseEvent(event);
    d->pressPoint = QPoint();

    updateValuesForPos(event->pos());
}

void SaturationLightnessPicker::mouseUngrabEvent()
{
    Q_D(SaturationLightnessPicker);
    QQuickControl::mouseUngrabEvent();
    d->pressPoint = QPoint();
    setPressed(false);
}

void SaturationLightnessPicker::updateValuesForPos(const QPoint &pos)
{
    Q_D(SaturationLightnessPicker);
    auto dontEmitColorChanged = SaturationLightnessPickerPrivate::DontEmitColorChanged;
    auto dontEmitColorPicked = SaturationLightnessPickerPrivate::DontEmitColorPicked;

    const bool saturationChanged = d->setSaturation(d->saturationAt(pos),
        dontEmitColorChanged, dontEmitColorPicked);
    const bool lightnessChanged = d->setLightness(d->lightnessAt(pos),
        dontEmitColorChanged, dontEmitColorPicked);

    if (saturationChanged || lightnessChanged) {
        emit colorChanged();
        emit colorPicked();
    }
}

QT_END_NAMESPACE
