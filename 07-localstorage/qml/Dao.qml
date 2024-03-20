import QtQuick 2.0
import QtQuick.LocalStorage 2.0

QtObject {
    property var database

    function addNote(date, description) {
        var rowid = 0
        database.transaction(function(tx) {
            tx.executeSql("INSERT INTO notes(date, description) VALUES(?, ?)", [date, description])
            const result = tx.executeSql("SELECT last_insert_rowid()")
            rowid = result.insertId
            }
        )
        return rowid
    }

    function updateNote(id, date, description) {
        var affectedRows = 0
        database.transaction(function(tx) {
            const result = tx.executeSql("UPDATE notes SET date = ?, description = ? WHERE rowid = ?", [date, description, id])
            affectedRows = result.affectedRows
            }
        )
        return affectedRows
    }

    function getNotes(callback) {
        database.readTransaction(function(tx) {
            const result = tx.executeSql("SELECT rowid, date, description FROM notes ORDER BY rowid DESC")
            callback(result.rows)
            }
        )
    }

    Component.onCompleted: {
        database = LocalStorage.openDatabaseSync("notes", "1.0")
        database.transaction(function(tx) {
            tx.executeSql("CREATE TABLE IF NOT EXISTS notes(date TEXT NOT NULL, description TEXT NOT NULL)")
            }
        )
    }
}
