import QtQuick 2.4
import QuickPaintedItemEx 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    property alias mouseArea: mouseArea

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        //anchors.fill: parent

        onClicked: {
            sp.value = 80
            p.value = 50
        }

//        onClicked: {
//            p.value = 50
//        }
    }

    ProgressBarEx {
        id: p
        x: 10
        y: 10
        width: 20
        height: 100
        visible: false
        z: 2

        Behavior on value { PropertyAnimation {} }
    }

    HyperbolaEx {
        x: 10
        y: 10
        width: parent.width - 20
        height: parent.height - 20
        //visible: false
    }

    CircularGauge {
        visible: false
        id: cg
        x: 10
        y: 10
        width: parent.width - 20
        height: parent.height - 20
        ///stepSize: 0.11
        minimumValue: 0
        maximumValue: 100
        value: accelerating ? maximumValue : 0
        anchors.centerIn: parent

        //tickmarksVisible: false

        property bool accelerating: false

        Keys.onSpacePressed: accelerating = true
        Keys.onReleased: {
            if (event.key === Qt.Key_Space) {
                accelerating = false;
                event.accepted = true;
            }
        }

        Component.onCompleted: forceActiveFocus()

        Behavior on value {
            NumberAnimation {
                duration: 1000
            }
        }

        style: CircularGaugeStyle {
            maximumValueAngle: 90
            minimumValueAngle: -90

            //background :  Rectangle {
            //    anchors.fill: parent
            //    color: "transparent"
            //}
            background:  Canvas {
                //id: canvas
                property real currentValue: cg.value
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.reset();

                    ctx.beginPath();
                    ctx.strokeStyle = "#e34c22";
                    ctx.lineWidth = outerRadius * 0.02;

                    ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
                            degreesToRadians(valueToAngle(0) - 90), degreesToRadians(valueToAngle(cg.value) - 90));
                    ctx.stroke();
                    //console.log(outerRadius - ctx.lineWidth / 2)


                }
                 onCurrentValueChanged: requestPaint()
            }

            function degreesToRadians(degrees) {
                return degrees * (Math.PI / 180);
            }

            foreground: Item {
                Rectangle {
                    width: outerRadius * 0.2
                    height: width
                    radius: width / 2
                    color: "#e5e5e5"
                    anchors.centerIn: parent
                }
            }

            minorTickmarkCount: 4
            minorTickmarkInset: 0
            minorTickmark: Rectangle {
                implicitWidth: outerRadius * 0.01
                antialiasing: true
                implicitHeight: outerRadius * 0.03
                //color: "#e5e5e5"
                color: "red"
            }

            //needleRotation: 0
//            needle: Rectangle {
//                y: outerRadius * 0.15
//                implicitWidth: outerRadius * 0.03
//                implicitHeight: outerRadius * 0.9
//                antialiasing: true
//                color: "#e5e5e5"
//            }


            tickmark: Text {
                text: styleData.value

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.bottom
                    text: styleData.index
                    color: "blue"
                }
            }

            tickmarkLabel:  Text {
                font.pixelSize: Math.max(6, outerRadius * 0.1)
                text: styleData.value
                color: styleData.value >= 80 ? "#e34c22" : "#e5e5e5"
                antialiasing: true
            }
        }
    }

    SunPath {
        id: sp
        x: 10
        y: 10
        width: parent.width - 20
        height: parent.height - 20
        visible: false

        Behavior on value { PropertyAnimation { duration: 2000 } }
    }
}
