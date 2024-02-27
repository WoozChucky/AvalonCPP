set(This Avalon)
project(${This})

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp" "src/*.h" "src/**/*.h")

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${This} ${SOURCES})
else()
    if(WIN32)
        add_executable(${This} WIN32 ${SOURCES})
    else()
        add_executable(${This} ${SOURCES})
    endif()
endif()

file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(${This}
        fmt::fmt
        OpenSSL::SSL
        protobuf::protobuf
        nlohmann_json::nlohmann_json
        SDL2::SDL2
        SDL2::SDL2main
        Freetype::Freetype
        ZLIB::ZLIB
        Boost::boost
        GLEW::GLEW
        glm::glm
        tmxlite::tmxlite
        imgui
        AvalonProto
        Common
        Network
        Engine)


