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

add_executable(task2 ${SOURCES})

target_link_libraries(task2 Qt6::Core Qt6::Widgets)

set_target_properties(car PROPERTIES
    WIN32_EXECUTABLE TRUE
)