/** !
 * Cross platform socket primitives 
 * 
 * @file socket.c 
 * 
 * @author Jacob Smith
 */

// Include 
#include <socket/socket.h>

int tcp_socket_create ( tcp_socket *const p_tcp_socket )
{

    // Argument check
    if ( p_tcp_socket == (void *) 0 ) goto no_tcp_socket; 

    // Platform specific implementation
    #ifdef _WIN64
        typedef SOCKET tcp_socket;
    #else
        typedef int tcp_socket;
    #endif

    *p_tcp_socket = socket(AF_INET6, AF_INET, iType, iProtocol);

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_tcp_socket:
                #ifndef NDEBUG
                    printf("[socket] Null pointer provided for parameter \"%s\"")
                #endif

                // Error
                return 0;
        }
    }
}