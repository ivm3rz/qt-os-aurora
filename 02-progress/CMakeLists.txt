project(progress LANGUAGES CXX VERSION 0.1)

# Включаем Qt-кодогенерацию
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME}
     main.cpp
     progress_widget.h
     progress_widget.cpp
)

target_link_libraries(${PROJECT_NAME} Qt::Widgets)
