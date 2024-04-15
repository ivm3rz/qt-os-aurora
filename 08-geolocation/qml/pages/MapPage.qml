import QtQuick 2.6
import Sailfish.Silica 1.0

import QtPositioning 5.3
import QtLocation 5.0
import "../assets"

Page {
    PositionSource { id: positionSource }
    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            id: mapPlugin

            name: "webtiles"
            allowExperimental: false

            PluginParameter {
                name: "webtiles.scheme"
                value: "https"
            }
            PluginParameter {
                name: "webtiles.host"
                value: "tile.openstreetmap.org"
            }
            PluginParameter {
                name: "webtiles.path"
                value: "/${z}/${x}/${y}.png"
            }
        }
        // ToDo: enable gesture recognition
        // ToDo: bind zoomLevel property to slider value

        // ToDo: add binding of the map center to the position coordinate

        // ToDo: create MouseArea to handle clicks and holds

        Component.onCompleted: center = QtPositioning.coordinate(56.028238, 37.853624)
    }
    // ToDo: add a slider to control zoom level

    // ToDo: add a component corresponding to MapQuickCircle

    // ToDo: add item at the current position
}
