---

## MapApp

Приложение, работающее с картой под ОС Аврора.

#### Цель:

Научиться самостоятельно создавать Аврора-приложение, использующее модуль [`Qt
Location`](https://doc.qt.io/archives/qt-5.6/qtlocation-index.html).

#### Описание/Пошаговая инструкция выполнения домашнего задания:

##### Раздел 1. Добавление зависимостей RPM-пакета
- В spec-файл добавить зависимости от [`Qt
Location`](https://doc.qt.io/archives/qt-5.6/qtlocation-index.html) и
[`WebTiles`](https://developer.auroraos.ru/doc/5.0.0/software_development/guides/webtiles).

##### Раздел 2. Реализация главной страницы приложения с картой

- Сделать страницу `MapPage` загружаемой при старте приложения.
- В элементе map файла MapPage.qml задать плагин для работы с картами
  [OSM](https://wiki.openstreetmap.org/wiki/Tiles).
- Привязать центр отображаемого фрагмента карты к актуальным координатам, если
  они корректны. Для этого нужно создать элемент типа `Binding`:
```qml
Binding {
    target: map
    property: "center"
    value: positionSource.position.coordinate
    when: positionSource.position.coordinate.isValid
}
```
- Активировать обработку жестов в элементе `map`.
- Добавить элемент типа `Slider` для управления свойством zoomLevel элемента `map`:
```qml
Slider {
    from: map.minimumZoomLevel
    to: map.maximumZoomLevel
    value: 11
}
```
- Разместить добавленный элемент вдоль нижней границы экрана поверх карты и
  привязать занчение `zoomLevel` элемента map к значению его свойства `value`.
- Проверить, что карта центрируется на актуальных координатах, можно её
  перетаскивать и управлять масштабом с помощью слайдера.

##### Раздел 3: Добавление элемента для отображения текущего местоположения.

- Cоздать визуальный компонент
[`MapQuickItem`](https://doc.qt.io/archives/qt-5.6/qml-qtlocation-mapquickitem.html)
c идентификатором `footprints`:
```qml
import QtQuick 2.6
import QtLocation 5.0

MapQuickItem {
    id: footprints
    sourceItem: Image {
        id: image
        source: Qt.resolvedUrl("graphics/footprints.svg")
        width: ???
        height: width
        fillMode: Image.PreserveAspectFit
    }
}
```
- Изменить его свойство `anchorPoint` так, чтобы координате соответствовал центр
  изображения.
- В компонент MapPage добавить элемент типа `Footprints`, координаты которого
  привязаны к координатам, получаемым из элемента `positionSource`, видимость
  определяется корректностью координат, а диаметр вычисляется следующим образом:
```js
Math.min(map.width, map.height) / 8
```
- В обработчике сигнала `Component.completed` компонента `MapPage` разместить
  добавленный элемент на карте с помощью `map.addMapItem`. 
- Проверить, что позиция, соответствующая актуальным координатам, отображается
  на карте.

⚠️ Плагин `WebTiles` не функционирует через HTTP(S) прокси-сервер:
```
[W] unknown:0 - QGeoTileRequestManager: Failed to fetch tile (10,5,4) 5 times, giving up. Last error message was: 'Socket operation timed out'
[W] unknown:0 - QGeoTileRequestManager: Failed to fetch tile (8,5,4) 5 times, giving up. Last error message was: 'Socket operation timed out'
[W] unknown:0 - QGeoTileRequestManager: Failed to fetch tile (9,5,4) 5 times, giving up. Last error message was: 'Socket operation timed out'
```
