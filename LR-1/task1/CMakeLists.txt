cmake_minimum_required(VERSION 3.16)
project(task1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    main.cpp
    mainwindow/mainwindow.cpp
    movingrect/movingrect.cpp
    car/car.cpp
)

set(HEADERS
    mainwindow/mainwindow.h
    movingrect/movingrect.h
    car/car.h
)

add_executable(main ${SOURCES} ${HEADERS})

target_link_libraries(main Qt6::Core Qt6::Widgets)