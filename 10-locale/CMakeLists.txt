cmake_minimum_required(VERSION 3.11)

project(LocaleApp
     VERSION 0.1
     DESCRIPTION "Локализованное Аврора-приложение"
     LANGUAGES CXX
)

# Задаем минимальный стандарт языка С++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Core Network Qml Gui Quick LinguistTools REQUIRED)

include(FindPkgConfig)

option(USE_SAILFISHAPP "Использовать библиотеку libsailfishapp" ON)

if(USE_SAILFISHAPP)
     pkg_search_module(SAILFISH sailfishapp REQUIRED)
     pkg_search_module(SAILFISH sailfishapp_i18n REQUIRED)
else()
     pkg_search_module(AURORA auroraapp REQUIRED)
     pkg_search_module(AURORA auroraapp_i18n REQUIRED)
endif()

file(GLOB TS_FILES "${CMAKE_SOURCE_DIR}/*.ts")
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "${CMAKE_BINARY_DIR}/qm")
qt5_add_translation(QM_FILES ${TS_FILES})
add_executable(${PROJECT_NAME} main.cpp ${QM_FILES})

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
     FILES ${PROJECT_NAME}.desktop
     DESTINATION share/applications
)

foreach(_size 86x86 108x108 128x128 172x172)
     install(
          FILES icons/${_size}/${PROJECT_NAME}.png
          DESTINATION share/icons/hicolor/${_size}/apps
     )
endforeach()

foreach(qm_file IN LISTS QM_FILES)
     get_filename_component(qm_filename "${qm_file}" NAME)
     # string(REPLACE "${short_name}" "${PROJECT_NAME}" _full_filename "${_filename}")
     install(FILES ${qm_file}
          DESTINATION share/${PROJECT_NAME}/translations
          RENAME ${qm_filename}
     )
endforeach()


file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
     "${CMAKE_INSTALL_PREFIX}\n${CMAKE_BINARY_DIR}/${PROJECT_NAME}:bin\n")
