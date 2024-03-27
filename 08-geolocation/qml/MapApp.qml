import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow {
     initialPage: Component { MapPage { } }
     cover: Component{
          CoverBackground {
               CoverPlaceholder {
                    text: qsTr("Карта")
                    icon {
                         source: Qt.resolvedUrl(qsTr("icons/%1.svg").arg(Qt.applicationName))
                         sourceSize {
                              width: icon.width
                              height: icon.height
                         }
                    }
                    forceFit: true
               }
          }
     }

     allowedOrientations: defaultAllowedOrientations
}
