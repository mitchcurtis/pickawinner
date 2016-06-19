import QtQuick 2.6
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

import PickAWinner 1.0

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
            padding: 0
            Layout.alignment: Qt.AlignTop

            background: Rectangle {
                implicitWidth: 40
                implicitHeight: picker.implicitHeight

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

        ColumnLayout {
            SaturationLightnessPicker {
                id: picker
                hue: hueSlider.value

                onSaturationChanged: saturationField.text = saturation
                onLightnessChanged: lightnessField.text = lightness
            }

            Label {
                text: qsTr("Saturation")
            }

            TextField {
                id: saturationField
                text: picker.saturation
                readOnly: true
                Layout.fillWidth: true

                validator: DoubleValidator {
                    bottom: 0
                    top: 1
                }

                onTextChanged: picker.saturation = text
            }

            Label {
                text: qsTr("Lightness")
            }

            TextField {
                id: lightnessField
                text: picker.lightness
                readOnly: true
                Layout.fillWidth: true

                validator: DoubleValidator {
                    bottom: 0
                    top: 1
                }

                onTextChanged: picker.lightness = text
            }

            Label {
                text: qsTr("Hex")
            }

            TextField {
                id: hexField
                readOnly: true
                text: qsTr("#%1%2%3").arg(toHex(c.r)).arg(toHex(c.g)).arg(toHex(c.b))
                Layout.fillWidth: true

                readonly property color c: Qt.hsla(hueSlider.value, picker.saturation, picker.lightness, 1)

                function toHex(n) {
                    var str = Math.floor(n * 255).toString(16);
                    if (str.length < 2)
                        str = "0" + str;
                    return str;
                }
            }
        }
    }
}
