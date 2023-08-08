project(calc LANGUAGES CXX VERSION 0.1)

# Используем MathEval для парсинга и вычисления мат.выражений
FetchContent_Declare(boost_matheval
     GIT_REPOSITORY https://github.com/hmenke/boost_matheval.git
     GIT_TAG        master
)
FetchContent_MakeAvailable(boost_matheval)

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

target_link_libraries(${PROJECT_NAME} Qt::Widgets matheval::x3)
