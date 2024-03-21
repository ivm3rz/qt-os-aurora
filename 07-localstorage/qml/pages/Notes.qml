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
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Редактировать")
                    onClicked: {
                        var dialog = pageStack.push(Qt.resolvedUrl("../dialogs/AddNote.qml"))
                        dialog.note = note
                        dialog.date = new Date(date)
                        dialog.onAccepted.connect(function() {
                            console.log("Update note #" + id)
                            dao.updateNote(id, dialog.date.toISOString(), dialog.note)
                            const index = id > 0 ? id - 1 : 0 // Нумерация индексов модели начинается с 0
                            noteModel.set(index, {id: id, note: dialog.note, date: dialog.date})
                        })
                    }
                }
            }
            Label {
                x: Theme.horizontalPageMargin
                text: date.toLocaleDateString(Locale.ShortFormat) + ": " + note
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
                        const result = dao.addNote(dialog.date.toISOString(), dialog.note)
                        const rowid = parseInt(result, 10)
                        if(rowid) {
                            console.log("Append note #" + rowid)
                            noteModel.append({id: rowid, note: dialog.note, date: dialog.date})
                        }
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
                noteModel.append({id: item.rowid, note: item.description, date: d})
            }
        })
    }

}
