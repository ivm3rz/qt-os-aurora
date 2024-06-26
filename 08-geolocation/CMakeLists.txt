cmake_minimum_required(VERSION 3.11)

project(MapApp
     VERSION 0.1
     DESCRIPTION "Аврора-приложение, работающее с картой"
     LANGUAGES CXX
)

# Задаем минимальный стандарт языка С++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Core Network Qml Gui Quick REQUIRED)

include(FindPkgConfig)

option(USE_SAILFISHAPP "Использовать библиотеку libsailfishapp" ON)

if(USE_SAILFISHAPP)
     pkg_search_module(SAILFISH sailfishapp REQUIRED)
else()
     pkg_search_module(AURORA auroraapp REQUIRED)
endif()

add_executable(${PROJECT_NAME} main.cpp)

if(USE_SAILFISHAPP)
     target_compile_definitions(${PROJECT_NAME} PRIVATE USE_SAILFISH_APP)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Werror -Wall -Wextra -pedantic-errors>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>
)

target_include_directories(${PROJECT_NAME} PRIVATE
     $<IF:$<BOOL:${USE_SAILFISHAPP}>,${SAILFISH_INCLUDE_DIRS},${AURORA_INCLUDE_DIRS}>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
     $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
     Qt5::Quick
)

if(USE_SAILFISHAPP)
     target_link_libraries(${PROJECT_NAME} PRIVATE
          ${SAILFISH_LDFLAGS}
     )
else()
     target_link_libraries(${PROJECT_NAME} PRIVATE
          ${AURORA_LDFLAGS}
     )
endif()

install(
     TARGETS ${PROJECT_NAME}
     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
     DIRECTORY qml
     DESTINATION share/${PROJECT_NAME}
)

install(
     DIRECTORY nmea
     DESTINATION share/${PROJECT_NAME}
)

install(
     FILES ${PROJECT_NAME}.desktop
     DESTINATION share/applications
)

foreach(_size 86x86 108x108 128x128 172x172)
     install(
          FILES icons/${_size}/ru.auroraos.png
          RENAME ${PROJECT_NAME}.png
          DESTINATION share/icons/hicolor/${_size}/apps
     )
endforeach()

file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
     "${CMAKE_INSTALL_PREFIX}\n${CMAKE_BINARY_DIR}/${PROJECT_NAME}:bin\n")
