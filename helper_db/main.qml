import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import io.qt.examples.backend 1.0
import QtQuick.Controls 1.4
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    ColumnLayout {
        width: parent.width
        height: parent.height
        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: columnlayout
            ListViewMasterWithInput {
                id: projectListView
                Layout.fillHeight: true
                Layout.fillWidth: true
                placeholderText: "type project"
            }
            ListViewMasterWithInput {
                id: projectAnnotationListView
                Layout.fillHeight: true
                Layout.fillWidth: true
                placeholderText: "type annotation"
            }
        }
    }
}
