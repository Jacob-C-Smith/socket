/** !
 * Cross platform socket primitives 
 * 
 * @file socket.c 
 * 
 * @author Jacob Smith
 */

// Include 
#include <socket/socket.h>

int socket_tcp_create ( socket_tcp *const p_socket_tcp, enum socket_address_family_e address_family, unsigned short port_number )
{

    // Argument check
    if ( p_socket_tcp == (void *) 0 ) goto no_tcp_socket; 

    // Platform specific initialized data
    #ifdef _WIN64
        socket_tcp _socket_tcp = INVALID_SOCKET;
    #else
        socket_tcp _socket_tcp = -1;
        int option = 1;
        struct sockaddr_in socket_address =
        {
            .sin_family = address_family,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(port_number),
            .sin_zero = { 0 }
        };
    #endif

    // Platform specific implementation
    #ifdef _WIN64

        // Create the socket
        _socket_tcp = socket(address_family, socket_type_tcp, IPPROTO_TCP);

        // Error check
        if ( _socket_tcp == INVALID_SOCKET ) goto failed_to_create_socket;

    #else

        // Create the socket
        _socket_tcp = socket(address_family, socket_type_tcp, IPPROTO_TCP);

        // Error check
        if ( _socket_tcp == -1 ) goto failed_to_create_socket;
        
        // Set socket options
        if ( setsockopt(_socket_tcp, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1 ) goto failed_to_set_socket_option;

        // Bind the socket to the port
        if ( bind(_socket_tcp,(struct sockaddr*) &socket_address, sizeof(socket_address)) == -1 ) goto failed_to_bind_socket;

    #endif

    // Return a socket to the caller
    *p_socket_tcp = _socket_tcp;

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_tcp_socket:
                #ifndef NDEBUG
                    printf("[socket] Null pointer provided for parameter \"p_tcp_socket\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Socket errors
        {
            failed_to_create_socket:
                #ifndef NDEBUG
                    printf("[socket] Call to function \"socket\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_to_set_socket_option:
                #ifndef NDEBUG
                    printf("[socket] Call to function \"setsockopt\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            failed_to_bind_socket:
                #ifndef NDEBUG
                    printf("[socket] Call to function \"bind\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            failed_to_listen:
                #ifndef NDEBUG
                    printf("[socket] Failed to listen on socket\n");
                #endif

                // Error
                return 0;
        }
    }
}

int socket_tcp_listen ( socket_tcp _socket_tcp, socket_tcp_accept_callback_function_t pfn_tcp_accept_callback )
{

    // Initialized data
    socket_tcp new_socket = 0;
    struct sockaddr_in peer_addr = {0};
    int addr_len = sizeof(peer_addr);
    char buf[1<<16] = { 0 };

    // Listen for connections
    if ( listen(_socket_tcp, 1) == -1 ) goto failed_to_listen;

    // Accept a new connection
    new_socket = accept(_socket_tcp, (struct sockaddr *) &peer_addr, &addr_len);

    // Error check
    if ( new_socket == -1 ) goto failed_to_connect;
    
    // Callback
    pfn_tcp_accept_callback(new_socket, ntohl(peer_addr.sin_addr.s_addr), ntohs(peer_addr.sin_port));

    
    while(1)
    {
        for (size_t i = 0; i < 1<<16; i++)
            buf[i] = '\0';
        
        recv(new_socket, buf, (1<<16), 0);
        printf("%s\n",buf);
    }

    // Success
    return 1;

    failed_to_listen:
        return 0;
    failed_to_connect:
        return 0;
}