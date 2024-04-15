import QtQuick 2.6
import QtPositioning 5.3
import QtLocation 5.0
import Sailfish.Silica 1.0

Page {
    PositionSource {
        id: positionSource
        nmeaSource: qsTr("/usr/share/%1/nmea/path.nmea").arg(Qt.application.name)
        active: true
    }
    Binding {
        target: map
        property: "center"
        value: positionSource.position.coordinate
        when: positionSource.position.coordinate.isValid
    }
    Map {
        MapQuickItem {
            id: footprints
            property alias diameter: image.width
            coordinate: positionSource.position.coordinate
            sourceItem: Image {
                id: image
                source: Qt.resolvedUrl("../icons/footprints.svg")
                width: 48 * Theme.pixelRatio
                height: width
                fillMode: Image.PreserveAspectFit
            }
            anchorPoint.x: image.width / 2
            anchorPoint.y: image.height / 2
        }

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
