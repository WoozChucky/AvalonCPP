cmake_minimum_required(VERSION 3.16)
set(This AvalonServer)
project(${This} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


#set(CMAKE_PREFIX_PATH /Users/nunosilva/Qt/6.2.0/macos)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.0\\msvc2019_64")

include_directories(../../Shared/Abstractions/include)
include_directories(../../Shared/SocketServer/include)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)


add_executable(${This}
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h)

target_link_libraries(${This} Qt6::Core Qt6::Widgets SocketServer)
