import QtQuick 2.0
import QtQuick.LocalStorage 2.0

QtObject {
     property var database

     function addNote(date, description) {
          database.transaction(function(tx) {
               tx.executeSql("INSERT INTO notes(date,description) VALUES(?, ?)", [date, description])
               }
          )
     }

     function getNotes(callback) {
          database.readTransaction(function(tx) {
               const result = tx.executeSql("SELECT date, description FROM notes")
               callback(result.rows)
               }
          )
     }

     Component.onCompleted: {
          database = LocalStorage.openDatabaseSync("notes", "1.0")
          database.transaction(function(tx) {
               tx.executeSql(
                    "CREATE TABLE IF NOT EXISTS notes(
                         id INTEGER PRIMARY KEY AUTOINCREMENT,
                         date TEXT NOT NULL,
                         description TEXT NOT NULL
                    )")
               }
          )
     }
}
