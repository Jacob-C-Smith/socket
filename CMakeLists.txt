# Need CMake 3.28.0
cmake_minimum_required (VERSION 3.28.0)

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

    set (SOCKET_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the socket project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SOCKET true PARENT_SCOPE)
        set(SOCKET_INCLUDE_DIR ${SOCKET_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to the executable
add_executable(socket_example "main.c")
add_dependencies(socket_example socket)
target_include_directories(socket_example PUBLIC ${SOCKET_INCLUDE_DIR})
target_link_libraries(socket_example socket)

# Add source to the library
add_library(socket SHARED "socket.c")
target_include_directories(socket PUBLIC ${SOCKET_INCLUDE_DIR})