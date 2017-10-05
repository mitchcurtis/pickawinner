#ifndef SATURATIONLIGHTNESSPICKER_P_H
#define SATURATIONLIGHTNESSPICKER_P_H

#include <QtGui/qcolor.h>
#include <QtQuickTemplates2/private/qquickcontrol_p.h>

class SaturationLightnessPickerPrivate;

class SaturationLightnessPicker : public QQuickControl
{
    Q_OBJECT
    Q_PROPERTY(qreal hue READ hue WRITE setHue NOTIFY hueChanged)
    Q_PROPERTY(qreal saturation READ saturation WRITE setSaturation NOTIFY saturationChanged)
    Q_PROPERTY(qreal lightness READ lightness WRITE setLightness NOTIFY lightnessChanged)
    Q_PROPERTY(qreal alpha READ alpha WRITE setAlpha NOTIFY alphaChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool pressed READ isPressed WRITE setPressed NOTIFY pressedChanged)
    Q_PROPERTY(QQuickItem *handle READ handle WRITE setHandle NOTIFY handleChanged FINAL)

public:
    explicit SaturationLightnessPicker(QQuickItem *parent = nullptr);

    qreal hue() const;
    void setHue(qreal hue);

    qreal saturation() const;
    void setSaturation(qreal saturation);

    qreal lightness() const;
    void setLightness(qreal lightness);

    qreal alpha() const;
    void setAlpha(qreal alpha);

    QColor color() const;
    void setColor(const QColor &color);

    bool isPressed() const;
    void setPressed(bool pressed);

    QQuickItem *handle() const;
    void setHandle(QQuickItem *handle);

Q_SIGNALS:
    void hueChanged();
    void saturationChanged();
    void lightnessChanged();
    void alphaChanged();
    void colorChanged();
    void colorPicked();
    void pressedChanged();
    void handleChanged();

public slots:
    void increaseSaturation();
    void decreaseSaturation();

    void increaseLightness();
    void decreaseLightness();

protected:
    void componentComplete() override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseUngrabEvent() override;

private:
    void updateValuesForPos(const QPoint &pos);

    Q_DISABLE_COPY(SaturationLightnessPicker)
    Q_DECLARE_PRIVATE(SaturationLightnessPicker)
};

QML_DECLARE_TYPE(SaturationLightnessPicker)

#endif // SATURATIONLIGHTNESSPICKER_P_H
