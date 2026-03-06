cmake_minimum_required(VERSION 3.16)

project(Car)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Car
    main.cpp
    mainwindow/mainwindow.cpp
    movingrect/movingrect.cpp
    car/car.cpp
    canvas/canvas.cpp
)

target_link_libraries(Car Qt6::Widgets)