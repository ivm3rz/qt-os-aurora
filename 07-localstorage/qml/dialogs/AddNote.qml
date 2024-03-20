import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
     allowedOrientations: Orientation.All
     readonly property alias note: noteArea.text
     readonly property alias date: datePicker.date

     Column {
          anchors.fill: parent

          DialogHeader {
               acceptText: qsTr( "Сохранить" )
               cancelText: qsTr( "Отменить" )
          }

          TextArea {
               id: noteArea
               placeholderText: "Введите заметку"
          }

          ValueButton {
               property date date
               id: datePicker
               label: qsTr( "Дата" )
               width: parent.width
               onClicked: {
                    var dialog = pageStack.push("Sailfish.Silica.DatePickerDialog", { date: date })
                    dialog.accepted.connect(function() {
                         value = dialog.dateText
                         date = dialog.date
                    })
               }
          }
     }

     Component.onCompleted: {
          datePicker.date = new Date()
          datePicker.value = datePicker.date.toLocaleDateString(Locale.ShortFormat)
     }
}
