project(progress LANGUAGES CXX VERSION 0.1)

add_executable(${PROJECT_NAME}
     main.cpp
     progress_widget.h
     progress_widget.cpp
)

target_link_libraries(${PROJECT_NAME} Qt::Widgets)

set_target_properties(${PROJECT_NAME}
     PROPERTIES
     AUTOMOC ON
)
