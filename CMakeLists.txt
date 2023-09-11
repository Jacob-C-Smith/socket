# Need CMake 3.20
cmake_minimum_required (VERSION 3.20)

# The name of the repository
project ("socket")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Add the socket project
if ( NOT "${HAS_SOCKET}")

    # Log
    message("[socket] Adding socket project")

    # Let any parent project know that it has the socket project
    set(HAS_SOCKET CACHE true PARENT_SCOPE)
endif()

# Add source to the executable
add_executable(socket_example "socket.c" "main.c")
target_include_directories(socket_example PUBLIC include include/socket/)

# Add source to the library
add_library(socket SHARED "socket.c")
target_include_directories(socket PUBLIC include include/socket/)