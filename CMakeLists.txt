cmake_minimum_required(VERSION 3.11) # FetchContent introduced in 3.11

project(QtAurora DESCRIPTION "Learning Qt applications")

# Задаем минимальный стандарт языка С++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

find_package(Qt5Widgets REQUIRED)
message(STATUS "Found Qt widgets: ${Qt5Widgets_VERSION}")

add_subdirectory(01-calculator)
add_subdirectory(02-progress)
add_subdirectory(03-volers)
add_subdirectory(04-qmlcalc)
