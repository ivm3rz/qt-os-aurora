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
                            console.log("Update note #" + rowid + ", index: " + index)
                            dao.updateNote(rowid, dialog.date.toISOString(), dialog.note)
                            noteModel.set(index, {rowid: rowid, note: dialog.note, date: dialog.date})
                        })
                    }
                }

                MenuItem {
                    text: qsTr("Удалить")
                    onClicked: {
                        const remorseTimeoutMsec = 3000
                        remorseDelete(function() {
                            console.log("Remove note #" + rowid + ", index: " + index)
                            dao.removeNote(rowid)
                            noteModel.remove(index)
                        }, remorseTimeoutMsec
                        )
                    }
                }
            }

            Label {
                font.pixelSize: Theme.fontSizeSmall
                text: date.toLocaleDateString(Locale.ShortFormat) + ": " + note
                truncationMode: TruncationMode.Fade
                anchors {
                    left: parent.left
                    leftMargin: Theme.horizontalPageMargin
                    right: parent.right
                    rightMargin: Theme.horizontalPageMargin
                    verticalCenter: parent.verticalCenter
                }
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
                            console.log("Insert note #" + rowid)
                            noteModel.insert(0, {rowid: rowid, note: dialog.note, date: dialog.date})
                        }
                    })
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: {
        noteModel.clear()
        dao.getNotes(function(notes) {
            for (var i = 0; i < notes.length; i++) {
                const item = notes.item(i)
                const d = new Date(item.date)
                noteModel.append({rowid: item.rowid, note: item.description, date: d})
            }
        })
    }

}
