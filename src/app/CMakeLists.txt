set(This Avalon)
project(${This})

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${This} ${SOURCES})
else()
    if(WIN32)
        add_executable(${This} WIN32 ${SOURCES})
    else()
        add_executable(${This} ${SOURCES})
    endif()
endif()

target_link_libraries(${This} fmt::fmt OpenSSL::SSL protobuf::protobuf SDL2::SDL2 SDL2::SDL2main Boost::boost GLEW::GLEW Opus::opus imgui AvalonProto Common Network Engine)


