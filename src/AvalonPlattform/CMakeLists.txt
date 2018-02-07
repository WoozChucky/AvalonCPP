set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 3.9)
project(AvalonPlattform)

set(CMAKE_CXX_STANDARD 17)

add_executable(AvalonPlattform Main.cpp Game.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../AvalonEngine)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../AvalonEngine/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_include_directories(AvalonPlattform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../AvalonEngine)
    target_link_libraries(AvalonPlattform ${SFML_LIBRARIES} AvalonEngine)
endif()