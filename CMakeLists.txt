cmake_minimum_required(VERSION 3.11) # FetchContent introduced in 3.11

project(QtAurora DESCRIPTION "Learning Qt applications")

# Задаем минимальный стандарт языка С++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Включаем Qt-кодогенерацию
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)
message(STATUS "Found Qt widgets: ${Qt5Widgets_VERSION}")

add_subdirectory(calc)
