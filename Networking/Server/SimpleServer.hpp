#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include <stdio.h>
#include <unistd.h>
#include <sstream>

#include "../Socket/hdelibc-sockets.hpp"

namespace HDE
{
    class SimpleServer
    {
    protected:
        ListeningSocket *socket;
        int new_socket;
        char buffer[30000];

    public:
        SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklog);
        ListeningSocket *get_socket();
        virtual void accepter();
        virtual void handler();
        virtual void responder();
        void launch();
        std::string get_request_method(const std::string &request);
        std::string get_route(const std::string &request);
    };
}

#endif