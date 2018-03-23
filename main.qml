import QtQuick 2.10
import QtQuick.Window 2.10
import calc_item 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Calc")

    CalcItem
    {
        visible: true
        anchors.fill:parent
    }
}
