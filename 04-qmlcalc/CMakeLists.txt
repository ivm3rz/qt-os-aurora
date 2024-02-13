project(qmlcalc
     LANGUAGES CXX
     DESCRIPTION "QML calculator"
     VERSION 0.1
)

find_package(Qt5 COMPONENTS Quick REQUIRED)

add_executable(${PROJECT_NAME}
     main.cpp
     resources.qrc
)

set_target_properties(${PROJECT_NAME}
     PROPERTIES
     AUTORCC ON
)

target_link_libraries(${PROJECT_NAME} Qt::Quick)
