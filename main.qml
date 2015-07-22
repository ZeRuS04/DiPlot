import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("Plot demonstration")
    width: 640
    height: 480
    visible: true

    Plot{
        anchors.fill: parent
        samples: [25, 43,76,21,55.2,-23, 100.8,43,88,9,0,21]

        // ограничение диапазона выборки:
        minSampleValue: 20
        maxSampleValue: 80
    }
}
