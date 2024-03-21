---

## NotesApp

Приложение, позволяющее добавлять и удалять заметки с использованием базы данных
[`LocalStorage`](https://doc.qt.io/archives/qt-5.6/qtquick-localstorage-qmlmodule.html)
и отображать их в списке
[`SilicaListView`](https://developer.auroraos.ru/doc/software_development/reference/silica/silicalistview).

### Cборка приложения

Проект собирается обычным образом с помощью [Аврора
SDK](https://developer.auroraos.ru/doc/software_development/sdk).

Для конфигурации сборки используется
[CMake](https://developer.auroraos.ru/doc/4.0.2/software_development/guidelines/cmake). 

⚠️ Приложение не функционирует в _Debug_-режиме при запуске с [`Qt QML
Live`](https://doc.qt.io/QMLLive/index.html) в Аврора SDK
[5.0.0](https://developer.auroraos.ru/release_notes/aurora_sdk_5.0.0.60) и
[5.0.1](https://developer.auroraos.ru/doc/software_development/sdk/downloads#5-0-1-27)
по причине ошибок при создании файла базы данных:
```
[I] unknown:0 - QmlLive: (Re)loading "qml/LocalStorageExample.qml"
[W] unknown:0 - LocalStorage: can't create path -  "//.local/share/ru.auroraos/LocalStorageExample/QML/OfflineStorage/Databases"
[W] unknown:0 - QSqlDatabasePrivate::database: unable to open database: "out of memory Error opening database"
[W] unknown:0 - QSqlQuery::prepare: database not open
[D] dbInit:9 - Error creating table in database: Error:
```
