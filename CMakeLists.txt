cmake_minimum_required(VERSION 3.16)
set(This Avalon)
project(${This} VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g -O0 -Wall")

find_package(fmt)
find_package(SDL2)
find_package(OpenSSL)
find_package(Protobuf)
find_package(Boost)
find_package(glew REQUIRED)

# Set the directory containing proto header and source files
set(PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/proto")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE ProtoHeaders "${PROTO_DIR}/*.h")
file(GLOB_RECURSE ProtoSources "${PROTO_DIR}/*.cc")
file(GLOB_RECURSE CodeSources "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE CodeHeaders "${SOURCE_DIR}/*.h")
file(GLOB_RECURSE ImGuiSources "${SOURCE_DIR}/imgui/*.cpp")
file(GLOB_RECURSE ImGuiHeaders "${SOURCE_DIR}/imgui/*.h")

include_directories(${PROTO_DIR})

add_executable(${This}
        ${CodeSources}
        ${CodeHeaders}
        ${ProtoSources}
        ${ProtoHeaders}
        ${ImGuiSources}
        ${ImGuiHeaders})

target_link_libraries(${This} fmt::fmt OpenSSL::SSL protobuf::protobuf SDL2::SDL2 SDL2::SDL2main Boost::boost GLEW::GLEW)

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
