import QtQuick 2.0
import Sailfish.Silica 1.0
import ".."

Page {
     Dao { id: dao }

     allowedOrientations: Orientation.All

     SilicaListView {
          id: notesView
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
                              dao.addNote(dialog.date, dialog.note)
                         });
                    }
               }
          }
     }

     function getNotes() {
         notesView.model.clear();
         dao.getNotes(function(notes) {
             for (var i = 0; i < notes.length; i++) {
                 var note = notes.item(i)
                 notesView.noteModel.append({note: note.description, date: note.date })
             }
         });
     }

     Component.onCompleted: getNotes();
}
