cmake_minimum_required(VERSION 3.20)
project(glad)


set(Sources
    src/glad.c
    include/glad/glad.h
    include/KHR/khrplatform.h
)

add_library(glad STATIC ${Sources})

target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
