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
    #include <Winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <errno.h>
#endif

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Platform dependent typedefs
#ifdef _WIN64
    typedef SOCKET socket_tcp;
#else
    typedef int socket_tcp;
#endif

// Platform dependent enumerations
#ifdef _WIN64
    enum socket_address_family_e {
        socket_address_family_ipv4 = AF_INET,
        socket_address_family_ipv6 = AF_INET6,
    };
    enum socket_protocol_e {
        socket_type_tcp = SOCK_STREAM,
        socket_type_udp = SOCK_DGRAM
    };
#else
    enum socket_address_family_e {
        socket_address_family_ipv4 = AF_INET,
        socket_address_family_ipv6 = AF_INET6,
    };
    enum socket_protocol_e {
        socket_type_tcp = SOCK_STREAM,
        socket_type_udp = SOCK_DGRAM
    };
#endif

// Type definitions
typedef int(*socket_tcp_accept_callback_function_t)( socket_tcp _socket_tcp, unsigned long ip_address, unsigned short port );

/** !
 * Create a TCP socket
 * 
 * @param p_socket_tcp : return
 * @param address_family socket_address_family_ipv4 -or- socket_address_family_ipv6
 * @param port_number the port number
 * 
 * @sa tcp_socket_bind
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int socket_tcp_create ( socket_tcp *const p_socket_tcp, enum socket_address_family_e address_family, unsigned short port_number );

DLLEXPORT int socket_tcp_listen ( socket_tcp _socket_tcp, socket_tcp_accept_callback_function_t pfn_tcp_accept_callback );
