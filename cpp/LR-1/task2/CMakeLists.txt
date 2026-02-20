cmake_minimum_required(VERSION 3.16)
project(task2)

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
    mainwindow/mainwindow.cpp
    shape/shape.cpp
    polygon/polygon.cpp
    triangle/triangle.cpp
    circle/circle.cpp
    rectangle/rectangle.cpp
    square/square.cpp
    rhombus/rhombus.cpp
    hexagon/hexagon.cpp
    star/star.cpp
    customshape/customshape.cpp
    shapemanager/shapemanager.cpp
)

set(HEADERS
    mainwindow/mainwindow.h
    shape/shape.h
    point/point.h
    polygon/polygon.h
    triangle/triangle.h
    circle/circle.h
    rectangle/rectangle.h
    square/square.h
    rhombus/rhombus.h
    hexagon/hexagon.h
    star/star.h
    customshape/customshape.h
    shapemanager/shapemanager.h
)

add_executable(main ${SOURCES} ${HEADERS})

target_link_libraries(main Qt6::Core Qt6::Widgets)