cmake_minimum_required(VERSION 3.20)
project(imgui)

find_package(SDL2)
find_package(glew)

set(Sources
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_sdl2.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${Sources})

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")


target_link_libraries(imgui PUBLIC SDL2::SDL2 SDL2::SDL2main GLEW::GLEW)
