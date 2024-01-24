project(volers
     LANGUAGES CXX
     DESCRIPTION "Significant volcano eruptions viewer"
     VERSION 0.1
)

add_executable(${PROJECT_NAME}
     main.cpp
     resources.qrc
)

target_link_libraries(${PROJECT_NAME} Qt::Core)

set_target_properties(${PROJECT_NAME}
     PROPERTIES
     AUTORCC ON
)
