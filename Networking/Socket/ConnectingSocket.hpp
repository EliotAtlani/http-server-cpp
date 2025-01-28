#ifndef ConnectingSocket_hpp
#define ConnectingSocket_hpp

#include <stdio.h>

#include "SimpleSocket.hpp"
namespace HDE
{
    class ConnectingSocket : public SimpleSocket
    {
    private:
        // MEMBER VALUE
        // The binding variable stores the value 0 if successful
        int binding;

        // MEMBER FUNCTION
        // Virutal function from parent
        void connect_to_network(int sock, struct sockaddr_in address);

    public:
        // Constructor
        ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);

        // Getters
        int get_binding();
    };
}

#endif