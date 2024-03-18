import QtQuick 2.0
import QtQuick.LocalStorage 2.0

QtObject {
     property var database;

     function addNote(date, description) {
          database.transaction(function(tx) {
               tx.executeSql("INSERT INTO note(date,description) VALUES(?, ?)", [date, description]);
          });
     }

     Component.onCompleted: {
          database = LocalStorage.openDatabaseSync("notes", "1.0")
          database.transaction(function(tx) {
               tx.executeSql(
                    "CREATE TABLE IF NOT EXISTS notes(
                         id INTEGER PRIMARY KEY AUTOINCREMENT,
                         date TEXT,
                         description TEXT
                    )");
               }
          );
     }
}
