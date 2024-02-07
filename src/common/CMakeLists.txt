set(This Common)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/**/*.cpp" "include/**/*.h")

find_package(fmt REQUIRED)
find_package(utf8cpp REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(${This} SHARED ${SOURCES})
set_target_properties(${This} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
target_include_directories(${This} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(${This} PRIVATE fmt::fmt utf8cpp Boost::boost OpenSSL::SSL OpenSSL::Crypto nlohmann_json::nlohmann_json)



# Add an installation rule to copy the shared library to the output directory
install(TARGETS ${This}
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
