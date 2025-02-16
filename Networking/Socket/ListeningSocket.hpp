#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include <stdio.h>

#include "BindingSocket.hpp"

namespace HDE
{
    class ListeningSocket : public BindingSocket
    {

    private:
        int backlog;
        int listening;
        int port_;

    public:
        ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bcklog);
        void start_listening();

        int get_listening();
        int get_backlog();
        int get_port();
    };
}

#endif