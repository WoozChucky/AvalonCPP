cmake_minimum_required(VERSION 3.16)
set(This AvalonGame)
project(${This} VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g -O0 -Wall")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

include(CMake/genrev.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Dependencies
find_package(fmt)
find_package(SDL2)
find_package(OpenSSL)
find_package(Protobuf)
find_package(Boost)
find_package(glew REQUIRED)
find_package(utf8cpp)
find_package(Opus)
find_package(nlohmann_json)

# Third party libraries
add_subdirectory(vendor/imgui-docking)

if (WIN32)
    add_definitions(-DAV_PLATFORM_WIN)
    add_definitions(-DAV_PLATFORM=AV_PLATFORM_WIN)
elseif(UNIX AND NOT APPLE)
    add_definitions(-DAV_PLATFORM_UNIX)
    add_definitions(-DAV_PLATFORM=AV_PLATFORM_UNIX)
elseif(APPLE)
    add_definitions(-DAV_PLATFORM_UNIX)
    add_definitions(-DAV_PLATFORM=AV_PLATFORM_UNIX)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Project libraries
add_subdirectory(src/proto)
add_subdirectory(src/common)
add_subdirectory(src/network)
add_subdirectory(src/engine)

# Project applications
add_subdirectory(src/app)
add_subdirectory(genrev)

# Set the directory containing proto header and source files
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")


set(PROTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/proto")

file(GLOB PROTO_FILES "${PROTO_PATH}/*.proto")
foreach(PROTO_FILE in ${PROTO_FILES})
    string(REGEX REPLACE "[.]proto$" ".pb.cc" OUTPUT_SOURCE ${PROTO_FILE})
    list(APPEND OUTPUT_SOURCES ${OUTPUT_SOURCE})
endforeach()

add_custom_command(OUTPUT ${OUTPUT_SOURCES}
        COMMAND protoc --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/src/proto ${PROTO_FILES}
        DEPENDS ${PROTO_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "some comment")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
