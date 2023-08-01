cmake_minimum_required(VERSION 3.12.0)

project(QtAurora
     LANGUAGES CXX
     VERSION 0.1
     DESCRIPTION "Learning Qt applications"
)

# Задаем минимальный стандарт языка С++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включаем Qt-кодогенерацию
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
