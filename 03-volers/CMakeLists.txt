project(volers
     LANGUAGES CXX
     DESCRIPTION "Significant volcano eruptions viewer"
     VERSION 0.1
)

add_executable(${PROJECT_NAME}
     main.cpp
     resources.qrc
)

target_compile_options(${PROJECT_NAME}
     PUBLIC
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Werror -Wall -Wextra -pedantic-errors>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>
)

target_link_libraries(${PROJECT_NAME} Qt::Widgets)

set_target_properties(${PROJECT_NAME}
     PROPERTIES
     AUTORCC ON
)
