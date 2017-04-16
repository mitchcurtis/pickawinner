import QtQuick 2.2
import QtTest 1.0
import PickAWinner 1.0

TestCase {
    id: testCase
    width: 200
    height: 200
    visible: true
    when: windowShown
    name: "SaturationLightnessPicker"

    Component {
        id: pickerComponent
        SaturationLightnessPicker {}
    }

    function test_mouse_data() {
        var data = [
            { mouseX: 0, mouseY: 0, saturation: 1.0, lightness: 0.0 },
            { mouseX: 100, mouseY: 0, saturation: 1.0, lightness: 0.5 },
            { mouseX: 200, mouseY: 0, saturation: 1.0, lightness: 1.0 },
            { mouseX: 0, mouseY: 0, saturation: 1.0, lightness: 0.0 },
            { mouseX: 0, mouseY: 100, saturation: 0.5, lightness: 0.0 },
            { mouseX: 0, mouseY: 200, saturation: 0.0, lightness: 0.0 },
            { mouseX: 100, mouseY: 100, saturation: 0.5, lightness: 0.5 },
            { mouseX: 200, mouseY: 200, saturation: 0.0, lightness: 1.0 },
        ];

        for (var i = 0; i < data.length; ++i)
            data[i].tag = ("x=" + data[i].mouseX + ", y=" + data[i].mouseY + ": "
                + "s=" + data[i].saturation.toFixed(2) + " l=" + data[i].lightness.toFixed(2));

        return data;
    }

    function test_mouse(data) {
        var control = pickerComponent.createObject(testCase);
        control.width = 200;
        control.height = 200;

        mousePress(control, data.mouseX, data.mouseY);
        compare(control.saturation, data.saturation);
        compare(control.lightness, data.lightness);

        control.destroy();
    }

    // TODO: make these properties of the picker?
    property real saturationStepSize: 0.05
    property real lightnessStepSize: 0.05

    function test_keys_data() {
        var data = [
            { saturationBefore: 1.0, key: Qt.Key_Up, saturationAfter: 1.0 },
            { saturationBefore: 0.0, key: Qt.Key_Down, saturationAfter: 0.0 },
            { saturationBefore: 1.0, key: Qt.Key_Down, saturationAfter: 1.0 - saturationStepSize },
            { saturationBefore: 0.0, key: Qt.Key_Up, saturationAfter: 0.0 + saturationStepSize },
            { lightnessBefore: 0.0, key: Qt.Key_Left, lightnessAfter: 0.0 },
            { lightnessBefore: 1.0, key: Qt.Key_Right, lightnessAfter: 1.0 },
            { lightnessBefore: 1.0, key: Qt.Key_Left, lightnessAfter: 1.0 - lightnessStepSize },
            { lightnessBefore: 0.0, key: Qt.Key_Right, lightnessAfter: 0.0 + lightnessStepSize },
        ];

        for (var i = 0; i < data.length; ++i)
            if (data[i].hasOwnProperty("saturationBefore")) {
                data[i].tag = "saturationBefore=" + data[i].saturationBefore
                    + ", key=" + data[i].key
                    + ", saturationAfter=" + data[i].saturationAfter.toFixed(2);
            } else {
                data[i].tag = "lightnessBefore=" + data[i].lightnessBefore
                    + ", key=" + data[i].key
                    + ", lightnessAfter=" + data[i].lightnessAfter.toFixed(2);
            }

        return data;
    }

    function test_keys(data) {
        var control = pickerComponent.createObject(testCase);

        var saturationBefore = data.hasOwnProperty("saturationBefore") ? data.saturationBefore : control.saturation;
        var lightnessBefore = data.hasOwnProperty("lightnessBefore") ? data.lightnessBefore : control.lightness;
        control.saturation = saturationBefore;
        control.lightness = lightnessBefore;

        control.forceActiveFocus();
        verify(control.activeFocus);

        keyClick(data.key);
        var saturationAfter = data.hasOwnProperty("saturationAfter") ? data.saturationAfter : saturationBefore;
        var lightnessAfter = data.hasOwnProperty("lightnessAfter") ? data.lightnessAfter : lightnessBefore;
        compare(control.saturation, saturationAfter);
        compare(control.lightness, lightnessAfter);

        control.destroy();
    }

    SignalSpy {
        id: hueSpy
        signalName: "hueChanged"
    }

    SignalSpy {
        id: saturationSpy
        signalName: "saturationChanged"
    }

    SignalSpy {
        id: lightnessSpy
        signalName: "lightnessChanged"
    }

    SignalSpy {
        id: alphaSpy
        signalName: "alphaChanged"
    }

    SignalSpy {
        id: colorSpy
        signalName: "colorChanged"
    }

    function test_setters() {
        var control = pickerComponent.createObject(testCase);
        compare(control.hue, 0.0);
        compare(control.saturation, 0.0);
        compare(control.lightness, 0.0);
        compare(control.alpha, 0.0);

        hueSpy.target = control;
        saturationSpy.target = control;
        lightnessSpy.target = control;
        alphaSpy.target = control;
        colorSpy.target = control;

        control.hue = 1.0;
        compare(hueSpy.count, 1);
        compare(colorSpy.count, 1);

        control.saturation = 1.0;
        compare(saturationSpy.count, 1);
        compare(colorSpy.count, 2);

        control.lightness = 1.0;
        compare(lightnessSpy.count, 1);
        compare(colorSpy.count, 3);

        control.alpha = 0.5;
        compare(alphaSpy.count, 1);
        compare(colorSpy.count, 4);

        var fuzz = 0.0001;
        fuzzyCompare(control.color.r, 1, fuzz);
        fuzzyCompare(control.color.g, 1, fuzz);
        fuzzyCompare(control.color.b, 1, fuzz);
        fuzzyCompare(control.color.a, 0.5, fuzz);

        control.color = Qt.hsla(0.3, 0.4, 0.5, 0.6)
        fuzzyCompare(control.color.hslHue, 0.3, fuzz);
        fuzzyCompare(control.color.hslSaturation, 0.4, fuzz);
        fuzzyCompare(control.color.hslLightness, 0.5, fuzz);
        fuzzyCompare(control.color.a, 0.6, fuzz);
        compare(colorSpy.count, 5);

        control.destroy();
    }
}
