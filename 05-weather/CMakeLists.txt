project(weather LANGUAGES CXX VERSION 0.1)

find_package(Qt5 COMPONENTS Network REQUIRED)

add_executable(${PROJECT_NAME}
     main.cpp
     weather.h
     weather.cpp
)

target_link_libraries(${PROJECT_NAME}
     Qt::Widgets
     Qt::Network
)

# Включаем Qt-кодогенерацию
set_target_properties(${PROJECT_NAME}
     PROPERTIES
     AUTOMOC ON
)
