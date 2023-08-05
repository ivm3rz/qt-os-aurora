project(calc LANGUAGES CXX VERSION 0.1)

# Включаем Qt-кодогенерацию
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME}
     main.cpp
     calculator.h
     calculator.cpp
     calculator.ui
)

target_link_libraries(${PROJECT_NAME} Qt::Widgets)
