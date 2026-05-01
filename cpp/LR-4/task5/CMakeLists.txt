cmake_minimum_required(VERSION 3.16)
project(task5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(SANITIZER_FLAGS "-fsanitize=address -fsanitize=thread -fno-omit-frame-pointer")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    main.cpp
)

set(HEADERS
    vector.h
    pair.h
)

add_executable(c ${SOURCES} ${HEADERS})

target_include_directories(c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(c Qt6::Core Qt6::Widgets)