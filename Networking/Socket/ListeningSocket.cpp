
#include "ListeningSocket.hpp"

HDE::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bcklog) : BindingSocket(domain, service, protocol, port, interface)
{
    backlog = bcklog;
    start_listening();
    test_connection(listening);
};

// Mutators

void HDE::ListeningSocket::start_listening()
{
    listening = listen(get_sock(), backlog);
}

// Getters

int HDE::ListeningSocket::get_listening()
{
    return listening;
}

int HDE::ListeningSocket::get_backlog()
{
    return backlog;
}
