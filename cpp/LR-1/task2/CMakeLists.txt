cmake_minimum_required(VERSION 3.16)
project(task2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt6_standard_project_setup()

file(GLOB_RECURSE SOURCES
    "*.cpp"
    "*.h"
)

add_executable(c ${SOURCES})

target_link_libraries(c Qt6::Core Qt6::Widgets)

target_include_directories(c PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/shapes/hdr
    ${CMAKE_CURRENT_SOURCE_DIR}/animation
)

set_target_properties(c PROPERTIES
    WIN32_EXECUTABLE TRUE
)