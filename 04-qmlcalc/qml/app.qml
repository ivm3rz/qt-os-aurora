import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5


ApplicationWindow {
    visible: true
    width: 480
    height: 480
    title: qsTr("Hello World")

   GridLayout {
       id: grid
       anchors.fill: parent

       rows: 3
       columns: 3

       Rectangle {
            color: "red"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.row: 1
            Layout.column: 2
       }

       Rectangle {
            color: "blue"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 1
            Layout.rowSpan: 2
            Layout.row: 1
            Layout.column: 1
       }

       Rectangle {
            color: "green"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 1
            Layout.rowSpan: 2
            Layout.row: 2
            Layout.column: 3
       }

       Rectangle {
            color: "white"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.row: 2
            Layout.column: 2
       }

       Rectangle {
            color: "yellow"
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.row: 3
            Layout.column: 1
       }
   }
}