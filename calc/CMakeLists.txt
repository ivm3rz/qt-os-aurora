project(calc LANGUAGES CXX VERSION 0.1)

add_executable(${PROJECT_NAME}
     main.cpp
     calculator.h
     calculator.cpp
     calculator.ui
)

target_link_libraries(${PROJECT_NAME} Qt::Widgets)
