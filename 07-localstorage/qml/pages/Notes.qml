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
                text: date + ": " + note
            }
        }
        header: PageHeader {
            title: qsTr("Список заметок")
        }

        PullDownMenu {
            quickSelect: true
            MenuItem {
                text: "Добавить заметку"
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/AddNote.qml"))
                    dialog.onAccepted.connect(function() {
                        noteModel.append({note: dialog.note, date: dialog.date.toLocaleDateString(Locale.ShortFormat) })
                        dao.addNote(dialog.date.toISOString(), dialog.note)
                    })
                }
            }
        }
    }

    Component.onCompleted: {
        noteModel.clear()
        dao.getNotes(function(notes) {
            for (var i = 0; i < notes.length; i++) {
                const item = notes.item(i)
                const d = new Date(item.date)
                noteModel.append({note: item.description, date: d.toLocaleDateString(Locale.ShortFormat)})
            }
        })
    }

}
