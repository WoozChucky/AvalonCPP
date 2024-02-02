set(This AvalonProto)

include_directories(include)
include_directories(${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES "src/*.cc" "include/**/*.h")

find_package(Protobuf REQUIRED)

add_library(${This} STATIC ${SOURCES})

target_link_libraries(${This} PRIVATE protobuf::protobuf)

target_include_directories(${This} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Add an installation rule to copy the shared library to the output directory
install(TARGETS ${This}
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
