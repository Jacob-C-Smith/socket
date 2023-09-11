/** !
 * Include header for socket library
 * 
 * @file socket/socket.h 
 * 
 * @author Jacob Smith 
 */

// Include guard
#pragma once

// Includes
#include <stdio.h>

// Platform dependent includes
#ifdef _WIN64
    #include <windows.h>
    #include <process.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Platform dependent typedefs
#ifdef _WIN64
    typedef SOCKET tcp_socket;
#else
    typedef int tcp_socket;
#endif

/** !
 * Initialize the high precision timer
 * 
 * @param void
 * 
 * @sa timer_high_precision
 * 
 * @return void
 */
DLLEXPORT void timer_init ( void );

/** !
 * Create a TCP socket
 * 
 * @param p_tcp_socket : pointer to tcp_socket
 * 
 * @sa tcp_socket_destroy
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int tcp_socket_create ( tcp_socket *const p_tcp_socket );
