import QtQuick 2.0
//import "com.matasoft.tablemodel"

Rectangle {
    width: 360
    height: 360

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
    ListView {
        model: MyTableModel
        anchors.fill: parent
        delegate: Text {
            text: id + ": " + model.firstName + " " + model.lastName;
        }
    }
}
