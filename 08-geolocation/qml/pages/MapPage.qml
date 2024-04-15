import QtQuick 2.6
import QtPositioning 5.3
import QtLocation 5.0
import "../assets"
import Sailfish.Silica 1.0

Page {
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
        gesture.enabled: true
        zoomLevel: slider.value

        // ToDo: add binding of the map center to the position coordinate

        // ToDo: create MouseArea to handle clicks and holds

        Component.onCompleted: center = QtPositioning.coordinate(56.028238, 37.853624)
    }

    Slider {
        id: slider
        minimumValue: map.minimumZoomLevel
        maximumValue: map.maximumZoomLevel
        value: 11
        width: parent.width
        y: parent.height - slider.height
    }

    // ToDo: add a component corresponding to MapQuickCircle

    // ToDo: add item at the current position
}
