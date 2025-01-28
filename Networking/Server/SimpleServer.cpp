#include "SimpleServer.hpp"

HDE::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklog)
{
    socket = new ListeningSocket(domain, service, protocol, port, interface, bcklog);
};

HDE::ListeningSocket *HDE::SimpleServer::get_socket()
{
    return socket;
}