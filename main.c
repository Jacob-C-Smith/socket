// Include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// socket submodule
#include <socket/socket.h>

// Preprocessor macros
#define MAX_BUFFER_LEN 65536

int accept_callback ( socket_tcp _socket_tcp, unsigned long ip_address, unsigned short port )
{

    // Uninitialized data
    char buffer[MAX_BUFFER_LEN];

    // Initialized data
    unsigned char a = (ip_address & 0xff000000) >> 24,
                  b = (ip_address & 0x00ff0000) >> 16,
                  c = (ip_address & 0x0000ff00) >> 8,
                  d = (ip_address & 0x000000ff) >> 0;
    
    // Log the IP
    printf("%d.%d.%d.%d:%d\n", a, b, c, d, port);

    // Receive data from the socket
    socket_tcp_receive(_socket_tcp, buffer, MAX_BUFFER_LEN);

    // Success
    return 1;
}

// Entry point
int main ( int argc, const char *argv[] )
{

    // Initialized data
    socket_tcp _tcp_socket = 0;

    // Create a socket
    socket_tcp_create(&_tcp_socket, socket_address_family_ipv4, 3000);

    // This will cause GitHub actions to wait forever. No can do.
    socket_tcp_listen(_tcp_socket, &accept_callback);

    // Success
    return EXIT_SUCCESS;
}