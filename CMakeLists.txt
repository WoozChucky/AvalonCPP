cmake_minimum_required(VERSION 3.16)
set(This Avalon)
project(${This} VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g -O0 -Wall -Wextra -Wpedantic -Werror")

find_package(fmt)
find_package(SDL2)
find_package(OpenSSL)
find_package(Protobuf)
find_package(Boost)
find_package(glew)

add_executable(${This} src/main.cpp)

target_link_libraries(${This} fmt::fmt OpenSSL::SSL protobuf::protobuf SDL2::SDL2 SDL2::SDL2main Boost::boost)
