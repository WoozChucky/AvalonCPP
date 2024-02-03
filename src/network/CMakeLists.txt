set(This Network)

include_directories(include)

file(GLOB_RECURSE HEADERS "include/**/*.h")
file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE WIN_SOURCES "src/Windows/*.cpp")
file(GLOB_RECURSE UNIX_SOURCES "src/Unix/*.cpp")

find_package(fmt REQUIRED)
find_package(utf8cpp REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

message(STATUS "SOURCES: ${SOURCES}")

if(WIN32)
    message(STATUS "Building for Windows")
    list(APPEND SOURCES ${WIN_SOURCES})
else()
    message(STATUS "Building for Unix")
    list(APPEND SOURCES ${UNIX_SOURCES})
endif()

message(STATUS "SOURCES: ${SOURCES}")

add_library(${This} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${This} PRIVATE fmt::fmt utf8cpp Boost::boost OpenSSL::SSL OpenSSL::Crypto)

target_include_directories(${This} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Add an installation rule to copy the shared library to the output directory
install(TARGETS ${This}
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
