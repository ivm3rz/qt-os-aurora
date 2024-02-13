import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5


ApplicationWindow {
    visible: true
    width: 480
    height: 480
    title: qsTr("QML calculator")



    GridLayout {
        id: grid
        anchors.fill: parent

        function onDigitButtonClicked(digitButton) {
            if(digits.text == "0") {
                digits.text = digitButton.text
            } else {
                digits.text += digitButton.text
            }
        }

        Text {
            id: digits
            text: "0"
            font.pixelSize: 16
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            minimumPixelSize: 12
            Layout.row: 0
            Layout.columnSpan: 4
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: one
            text: "1"
            font.bold: true
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: two
            text: "2"
            font.bold: true
            Layout.row: 1
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: three
            text: "3"
            font.bold: true
            Layout.row: 1
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: four
            text: "4"
            font.bold: true
            Layout.row: 2
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: five
            text: "5"
            font.bold: true
            Layout.row: 2
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: six
            text: "6"
            font.bold: true
            Layout.row: 2
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: seven
            text: "7"
            font.bold: true
            Layout.row: 3
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: eight
            text: "8"
            font.bold: true
            Layout.row: 3
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: nine
            text: "9"
            font.bold: true
            Layout.row: 3
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: zero
            text: "0"
            font.bold: true
            Layout.row: 4
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            onClicked: grid.onDigitButtonClicked(this)
        }

        Button {
            id: decimal
            text: ","
            font.bold: true
            Layout.row: 4
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: percent
            text: "%"
            enabled: false
            font.bold: true
            Layout.row: 4
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: plus
            text: "+"
            font.bold: true
            Layout.row: 1
            Layout.column: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: minus
            text: "-"
            font.bold: true
            Layout.row: 2
            Layout.column: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: divide
            text: "÷"
            font.bold: true
            Layout.row: 3
            Layout.column: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button {
            id: times
            text: "×"
            font.bold: true
            Layout.row: 4
            Layout.column: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}