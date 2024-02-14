project(qmlcalc
     LANGUAGES CXX
     DESCRIPTION "QML calculator"
     VERSION 0.1
)

# Используем MathEval для парсинга и вычисления мат.выражений
FetchContent_Declare(boost_matheval
     GIT_REPOSITORY https://github.com/hmenke/boost_matheval.git
     GIT_TAG        master
)
FetchContent_MakeAvailable(boost_matheval)

find_package(Qt5 COMPONENTS Quick REQUIRED)

add_executable(${PROJECT_NAME}
     main.cpp
     calc.h
     calc.cpp
     resources.qrc
)

set_target_properties(${PROJECT_NAME}
     PROPERTIES
     AUTORCC ON
     AUTOMOC ON
)

target_link_libraries(${PROJECT_NAME}
     Qt::Quick
     matheval::x3
)
