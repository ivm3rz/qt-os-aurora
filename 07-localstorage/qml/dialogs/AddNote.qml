import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property alias note: noteArea.text
    property alias date: datePicker.date

    Column {
        anchors.fill: parent

        DialogHeader {
            acceptText: qsTr("Сохранить")
            cancelText: qsTr("Отменить")
        }

        TextArea {
            id: noteArea
            placeholderText: qsTr("Введите заметку")
        }

        ValueButton {
            property date date
            id: datePicker
            label: qsTr("Дата заметки")
            width: parent.width
            onClicked: {
                var dialog = pageStack.push("Sailfish.Silica.DatePickerDialog", {date: date})
                dialog.accepted.connect(function() {
                    value = dialog.dateText
                    date = dialog.date
                })
            }

            function shortDate() {
                return date.toLocaleDateString(Locale.ShortFormat)
            }
        }
    }

    Connections {
        target: datePicker
        onDateChanged: {
            datePicker.value = datePicker.shortDate()
        }
    }

    Component.onCompleted: {
        datePicker.date = new Date()
        datePicker.value = datePicker.shortDate()
    }
}
