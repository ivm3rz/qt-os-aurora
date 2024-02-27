---

## Open Weather Map

Приложение для погодных сведений через [**OpenWeatherMap
API**](https://openweathermap.org/current). Графический интерфейс реализован с
использованием [**QtWidgets**](https://doc.qt.io/qt-5/qtwidgets-index.html).
Ключ API взят из
[примера](http://samples.openweathermap.org/data/2.5/find?q=London&appid=b1b15e88fa797225412429c1c50c122a1r)
использования **OpenWeatherMap**. Для получения информации о текущем
местоположении используется сервис [ifconfig.co](https://ifconfig.co/). 

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
    libqt5network5
```

#### Сборка приложения

```bash
mkdir build
cd build
cmake ..
make weather
```

### Запуск приложения

```bash
./bin/weather
```
