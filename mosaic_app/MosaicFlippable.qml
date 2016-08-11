import QtQuick 2.7
import MoMosaic 1.0


Rectangle {
    Component {
        id: listDelegate
        Rectangle {
            width: gridView1.cellWidth
            height: gridView1.cellHeight
            color: "gray"
            Image {
                id: frontIcon
                asynchronous: true;
                anchors.centerIn: parent
                sourceSize.width: gridView1.cellWidth - 2
                sourceSize.height: gridView1.cellHeight - 2
                fillMode: Image.PreserveAspectFit
                source: {index == -1 ? '' : "image://imageProvider/" + index}
                smooth: true
                visible: true
                cache: true
            }
        }
    }

    Flipable {
        id:flipable

        anchors.fill: parent

        property bool flipped: false

        front: Rectangle {
            id: thumbnailView
            anchors.fill: parent
            width: 600
            height: 500
            visible: true
            color: "gray"
            GridView {
                anchors.fill: parent
                id: gridView1
                cellWidth: 50
                cellHeight: 50
                delegate: listDelegate
                model: mosaicImages
                visible: true
            }
        }
        back: MoMosaicView {
            id: mosaicView
        }

        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
            angle: 0    // the default angle
        }

        states: State {
            name: "back"
            PropertyChanges { target: rotation; angle: 180 }
            when: flipable.flipped
        }

        transitions: Transition {
            NumberAnimation { target: rotation; property: "angle"; duration: 100 }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: flipable.flipped = !flipable.flipped
        }
    }
}
