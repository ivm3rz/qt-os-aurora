project(calc LANGUAGES CXX VERSION 0.1)

add_executable(${PROJECT_NAME}
     src/main.cpp
)

target_link_libraries(${PROJECT_NAME} Qt::Widgets)
