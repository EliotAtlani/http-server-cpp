#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include <stdio.h>
#include <unistd.h>

#include "../Socket/hdelibc-sockets.hpp"

namespace HDE
{
    class SimpleServer
    {
    private:
        ListeningSocket *socket;
        virtual void accepter() = 0;
        virtual void handler() = 0;
        virtual void responder() = 0;

    public:
        SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklog);

        virtual void launch() = 0;
        ListeningSocket *get_socket();
    };
}

#endif