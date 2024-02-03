set(This Avalon)
project(${This})

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(${This} ${SOURCES})

target_link_libraries(${This} fmt::fmt OpenSSL::SSL protobuf::protobuf SDL2::SDL2 SDL2::SDL2main Boost::boost GLEW::GLEW imgui AvalonProto Common Network)


