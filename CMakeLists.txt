cmake_minimum_required(VERSION 3.11) # FetchContent introduced in 3.11

project(QtAurora DESCRIPTION "Learning Qt applications")

# Задаем минимальный стандарт языка С++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
     if(CMAKE_VERSION VERSION_LESS 3.22)
          include(os_release_info)

          get_os_release_info(
               OS_RELEASE_ID
               OS_RELEASE_VERSION
               OS_RELEASE_CODENAME
          )
          message(STATUS "Distrib: ${OS_RELEASE_ID}-${OS_RELEASE_VERSION} (${OS_RELEASE_CODENAME})")
     else()
          cmake_host_system_information(
               RESULT PRETTY_NAME
               QUERY DISTRIB_PRETTY_NAME
          )
          message(STATUS "Distrib: ${PRETTY_NAME}")

          cmake_host_system_information(
               RESULT DISTRO
               QUERY DISTRIB_INFO
          )

          foreach(VAR IN LISTS DISTRO)
               message(STATUS "${VAR}=`${${VAR}}`")
          endforeach()
     endif()
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
message(STATUS "Found Qt widgets: ${Qt5Widgets_VERSION}")

add_subdirectory(01-calculator)
add_subdirectory(02-progress)
add_subdirectory(03-volers)
add_subdirectory(04-qmlcalc)
add_subdirectory(05-weather)
