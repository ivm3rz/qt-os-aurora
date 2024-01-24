project(calc LANGUAGES CXX VERSION 0.1)

# Используем MathEval для парсинга и вычисления мат.выражений
FetchContent_Declare(boost_matheval
     GIT_REPOSITORY https://github.com/hmenke/boost_matheval.git
     GIT_TAG        master
)
FetchContent_MakeAvailable(boost_matheval)

add_executable(${PROJECT_NAME}
     main.cpp
     calculator.h
     calculator.cpp
     calculator.ui
)

target_link_libraries(${PROJECT_NAME} Qt::Widgets matheval::x3)

# Включаем Qt-кодогенерацию
set_target_properties(${PROJECT_NAME}
     PROPERTIES
     AUTOMOC ON
     AUTOUIC ON
)
