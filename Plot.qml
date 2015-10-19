import QtQuick 2.3
import QtQuick.Controls 1.2
import CustomGeometry 1.0

Rectangle {
    id: mainRect
    property var samples:[]

    signal pointSelected(int index);
    signal pointUnselected(int index);

    Flickable{
        id: flickableGraph
        anchors.top: parent.top;    anchors.bottom: flickableLegend.top;
        anchors.left: parent.left;  anchors.right: parent.right;
        contentWidth: field.width; contentHeight: field.height
        boundsBehavior: Flickable.StopAtBounds
         Rectangle{
            id: field
            width: mainRect.width*horizSlider.value
            height: (mainRect.height-30)*vertSlider.value
            x: 0; y: 0;
            Graph{
                id: graph
                anchors.fill: parent
                samples: mainRect.samples
                Repeater{
                    model: graph.gaPoints
                    delegate: Rectangle{
                        id: rect
                        width: 5; height: 5;
                        x: modelData.px-width/2;
                        y: modelData.py-height/2;
                        radius: width/2
                        color: "red"

                    }
                }
                Component.onCompleted: startGA();
            }
        }
    }
    Flickable{
        id: flickableLegend
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        height: 30

        contentX: flickableGraph.contentX
        contentWidth: legend.width; contentHeight: legend.height
        boundsBehavior: Flickable.StopAtBounds
        Rectangle{
            id: legend
            color: "lightgray"
            height: 30
            width: mainRect.width*horizSlider.value
            Repeater{
                model: graph.points
                delegate: Rectangle{
                    id: legRect
                    width: 30; height: 30;
                    x: modelData.px-width/2;
                    anchors.verticalCenter: legend.verticalCenter
                    color: "steelblue"
                    border.width: 1
                    border.color: "darkblue"
                    visible: false
                    radius: 5
                    property int i: index
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        color: "white"
                        text: legRect.i
                    }
                    Connections{
                        target: mainRect
                        onPointSelected: {
                            if(legRect.i == index)
                                legRect.visible = true
                        }
                        onPointUnselected: {
                            if(legRect.i == index)
                                legRect.visible = false
                        }
                    }

                }
            }
        }

    }

    Slider{
        id: horizSlider
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        minimumValue: 1
        maximumValue: 10
        orientation: Qt.Horizontal
        value: 1
        stepSize: 0.5
    }
    Slider{
        id: vertSlider
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        minimumValue: 1
        maximumValue: 10
        orientation: Qt.Vertical
        value: 1
        stepSize: 0.5
    }
}

