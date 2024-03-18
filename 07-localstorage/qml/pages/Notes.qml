import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
     allowedOrientations: Orientation.All

     SilicaListView {
          anchors.fill: parent
          model: ListModel {
               id: noteModel
          }
          delegate: ListItem {
               Label {
                    x: Theme.horizontalPageMargin
                    text: date.toLocaleDateString( Locale.ShortFormat ) + ": " + note
               }
          }
          header: PageHeader {
              title: qsTr( "Список заметок" )
          }

          PullDownMenu {
               quickSelect: true
               MenuItem {
                    text: "Добавить заметку"
                    onClicked: {
                         var dialog = pageStack.push( Qt.resolvedUrl("../dialogs/AddNote.qml") )
                         dialog.onAccepted.connect(function() {
                              noteModel.append({note: dialog.note, date: dialog.date })
                         });
                    }
               }
          }
     }
}
