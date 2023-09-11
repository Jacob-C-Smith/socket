# SOCKET CMake configuration file:
# This file is meant to be placed in a cmake subfolder of SOCKET-devel-2.x.y-VC

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)
set_package_properties(SOCKET PROPERTIES
    URL "https://g10.app/status/#primitives"
    DESCRIPTION "socket"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(SOCKET_FOUND TRUE)

# For compatibility with autotools SOCKET-config.cmake, provide SOCKET_* variables.

set_and_check(SOCKET_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(SOCKET_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(SOCKET_INCLUDE_DIR  "${SOCKET_PREFIX}/include")
set(SOCKET_INCLUDE_DIRS           "${SOCKET_INCLUDE_DIR}")
set_and_check(SOCKET_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(SOCKET_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(SOCKET_LIBRARIES socket::socket)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated SOCKET-target.cmake files.

set(_SOCKET_library     "${SOCKET_LIBDIR}/socket.lib")
set(_SOCKET_dll_library "${SOCKET_BINDIR}/socket.dll")
if(EXISTS "${_SOCKET_library}" AND EXISTS "${_SOCKET_dll_library}")
    if(NOT TARGET socket::socket)
        add_library(socket::socket SHARED IMPORTED)
        set_target_properties(socket::socket
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${SOCKET_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_SOCKET_library}"
                IMPORTED_LOCATION "${_SOCKET_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "SOCKET_SHARED"
                INTERFACE_SOCKET_SHARED "ON"
        )
    endif()
    set(SOCKET_SOCKET_FOUND TRUE)
else()
    set(SOCKET_SOCKET_FOUND FALSE)
endif()
unset(_SOCKET_library)
unset(_SOCKET_dll_library)

check_required_components(SOCKET)
