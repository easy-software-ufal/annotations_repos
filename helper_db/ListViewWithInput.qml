import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import io.qt.examples.backend 1.0
import QtQuick.Controls 1.4
Item {
    Layout.fillHeight: true
    Layout.fillWidth: true
    id: listViewMasterContainer
    Rectangle {
        anchors.margins: 5
        anchors.fill: parent
        border.width: 1
        border.color: "black"
        id: masterContainer
        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 1
            ListView {
                Layout.alignment: Qt.AlignLeft
                id: ctnListView
                property var colors: ["white","lightgray"]
                Layout.fillHeight: true
                Layout.fillWidth: true
                delegate: Rectangle {
                    height: 22
                    width: ctnListView.width
                    color: ctnListView.colors[index%2]
                    Text {
                        text: project
                    }
                }
                model: ListModel {
                    id: listModel
                }
            }
            Item {
                id: inputContainer
                height: 22
                Layout.fillWidth: true
                Button{
                    id: prjAddBtn
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 1
                    anchors.leftMargin: 1
                    height: 22
                    width: 44
                    text: "Add"
                }
                Rectangle {
                    anchors.left: prjAddBtn.right
                    anchors.right: inputContainer.right
                    anchors.rightMargin: 2
                    height: 21
                    anchors.leftMargin: 6
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    border.width: 1
                    border.color: "black"
                    TextInput {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 6
                        horizontalAlignment: TextInput.AlignHCenter
                        cursorVisible: true
                        cursorPosition: 0
                        text: "type project"
                    }
                }
            }
        }
    }
}
