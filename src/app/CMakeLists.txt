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

file(GLOB SHADERS "shaders/*")

foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    add_custom_command(TARGET ${This} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SHADER}
            ${CMAKE_BINARY_DIR}/bin/${SHADER_NAME})
endforeach()

target_link_libraries(${This}
        fmt::fmt
        OpenSSL::SSL
        protobuf::protobuf
        nlohmann_json::nlohmann_json
        SDL2::SDL2
        SDL2::SDL2main
        Boost::boost
        GLEW::GLEW
        Opus::opus
        imgui
        AvalonProto
        Common
        Network
        Engine)


