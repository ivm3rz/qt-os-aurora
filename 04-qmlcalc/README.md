---

Базовый калькулятор реализует основные арифметические операции и аналогично по
функционалу [калькулятору](../01-calculator), реализованного с использованием
[QtWidgets](https://doc.qt.io/qt-5.15/qtwidgets-index.html). Приложение
разработано с использованием [QML](https://doc.qt.io/qt-5/qmlapplications.html),
реализующем графический интерфейс пользователя, и библиотеки [Boost
MathEval](https://github.com/hmenke/boost_matheval), реализующей разбор и
выполнение математических выражений.

В приложении реализовано взаимодействие C++ объекта класса [`MathEval`](calc.h),
реализующего разбор и вычисление математических выражений, с [QML объектами](calc.qml)
графической части приложения.

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
    qtquickcontrols2-5-dev \
    qtdeclarative5-dev \
    qml-module-qtquick2 \
    qml-module-qtquick-window2 \
    qml-module-qtquick-controls2 \
    libboost-dev
```

#### Сборка приложения

```bash
mkdir build
cd build
cmake ..
make qmlcalc        # Для сборки калькулятора на QML
```

### Запуск приложения

```bash
./bin/qmlcalc
```

