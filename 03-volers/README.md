---

## Volcanic Eruption

Приложение для отображения в виде таблицы сведений о наиболее значимых
вулканических извержениях, демонстрирующее использование паттерна MVC
(Model-View-Controller). В качестве источника данных используется публично
доступный [СSV-файл](https://public.opendatasoft.com/api/explore/v2.1/catalog/datasets/significant-volcanic-eruption-database/exports/csv?lang=en&timezone=Europe%2FMinsk&use_labels=true&delimiter=%3B).
В качестве модели данных используется стандартная модель и `QTableWidget` для
отображения данных. Для отображения индекса вулканической активности
используется делегат, используеющий `QComboBox` в качестве виджета для
редактирования.

### Требования и ограничений

* Компилятор С++, поддерживающий стандарт C++14.
* CMake версии не ниже 3.11.
* Qt версии 5.15.

📝 **Замечание** Приложение разрабатывалось и тестировалось на *Ubuntu 22.04*.

### Инструкции для сборки

#### Установка сборочного окружения

```bash
apt install -y \
    build-essential \
    cmake \
    qtbase5-dev \
```

#### Сборка приложения

```bash
mkdir build
cd build
cmake ..
make volers
```

### Запуск приложения

```bash
./bin/volers
```
