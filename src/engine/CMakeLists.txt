set(This Engine)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/**/*.cpp" "include/**/*.h")

find_package(fmt REQUIRED)
find_package(utf8cpp REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(${This} STATIC ${SOURCES})

target_link_libraries(${This} PRIVATE fmt::fmt utf8cpp Boost::boost OpenSSL::SSL OpenSSL::Crypto SDL2::SDL2 Common)

target_include_directories(${This} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Add an installation rule to copy the shared library to the output directory
install(TARGETS ${This}
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
