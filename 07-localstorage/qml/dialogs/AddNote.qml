import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
     allowedOrientations: Orientation.All
     property string note

     Column {
          anchors.fill: parent

          DialogHeader {
               acceptText: "Сохранить"
               cancelText: "Отменить"
          }

          TextArea {
               id: noteArea
               placeholderText: "Введите заметку"
          }
     }

     onAccepted: note = noteArea.text
}
