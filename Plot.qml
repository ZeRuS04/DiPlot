import QtQuick 2.3
import QtQuick.Controls 1.2
import CustomGeometry 1.0

Rectangle {
    id: mainRect
    property var samples:[]
    property var minSampleValue: Number.NEGATIVE_INFINITY
    property var maxSampleValue: Number.POSITIVE_INFINITY

    signal pointSelected(int index);
    signal pointUnselected(int index);

    function limitSamples(samplesf){
        var tmp = [];
        tmp = samplesf;
        var limitedSamples = [];
        for(var i = 0; i < tmp.length; i++){
                if(tmp[i] < minSampleValue)
                    continue;
                if(tmp[i] > maxSampleValue)
                    continue;
            limitedSamples.push(tmp[i])
        }
        return limitedSamples
    }

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
                samples: mainRect.limitSamples(mainRect.samples)
                Repeater{
                    model: graph.points
                    delegate: Rectangle{
                        id: rect
                        width: 15; height: 15;
                        x: modelData.px-width/2;
                        y: modelData.py-height/2;
                        radius: width/2
                        color: "steelblue"
                        property int i: index
                        property bool lock: false
                        Rectangle{
                            id: vertLine
                            color: Qt.rgba(0,0,0,0.5)

                            width: 1
                            height: field.height
                            visible: false
                            x: parent.width/2
                            y: parent.height/2
                        }
                        Rectangle{
                            id: horizLine
                            color: Qt.rgba(0,0,0,0.5)

                            width: 2*field.width
                            height: 1
                            visible: false
                            anchors.horizontalCenter: parent.horizontalCenter
                            y: parent.height/2
                        }

                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                if(!rect.lock){
                                    val.visible = true
                                    vertLine.visible = true
                                    horizLine.visible = true
                                    rect.width*=1.5
                                    rect.height*=1.5
                                    rect.color = "orange"
                                    mainRect.pointSelected(rect.i);
                                }
                            }
                            onExited: {
                                if(!rect.lock){
                                    val.visible = false
                                    vertLine.visible = false
                                    horizLine.visible = false
                                    rect.width/=1.5
                                    rect.height/=1.5
                                    rect.color = "steelblue"
                                    mainRect.pointUnselected(rect.i);
                                }
                            }
                            onClicked: {
                                rect.lock = !rect.lock
                                rect.color = rect.lock ? "green" : "orange"
                            }
                        }
                        Text{
                            id: val
                            anchors.bottom: parent.top
                            anchors.horizontalCenter: parent.horizontalCenter
                            visible: false
                            text: graph.samples[rect.i]
                            font.pointSize: 14
                            color: "black"
                        }
                    }
                }
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

