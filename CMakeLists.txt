cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(universe)

set(universe_VERSION_MAJOR 1)
set(univere_VERSION_MINOR 0)
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

set(EXECUTABLE_NAME "Universe-Simulator")
add_executable(${EXECUTABLE_NAME} main.cpp universe.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

#INSTALL TARGET
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

#CPACK
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${universe_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${universe_VERSION_MINOR}")
include(CPack)

