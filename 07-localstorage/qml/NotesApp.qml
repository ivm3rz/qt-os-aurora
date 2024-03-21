import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow {
     initialPage: Component { Notes { } }
     cover: Component {
         CoverBackground {
             CoverPlaceholder {
                 text: qsTr("Заметки")
                 icon {
                     source: Qt.resolvedUrl("icons/NotesApp.svg")
                     sourceSize {
                         width: icon.width
                         height: icon.height
                     }
                 }
             }
         }
     }
}
