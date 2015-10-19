import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("Plot demonstration")
    width: 640
    height: 480
    visible: true

    Plot{
        id: plot
        anchors.fill: parent
        samples: []

        function generate() {
            var s = [];
            for (var i = 0; i < 900; i++){
                var x = 1 + i/100;
                var f = Math.log(x) * Math.cos(3*x - 15);
                s.push(f);
            }

            plot.samples = s;
        }
        Component.onCompleted: generate()
    }

}
