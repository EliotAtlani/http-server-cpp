#include "SimpleServer.hpp"

HDE::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklog)
{
    socket = new ListeningSocket(domain, service, protocol, port, interface, bcklog);
};

HDE::ListeningSocket *HDE::SimpleServer::get_socket()
{
    return socket;
}

void HDE::SimpleServer::accepter()
{
    struct sockaddr_in address = get_socket()->get_address();
    int addrlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
    read(new_socket, buffer, 30000);
}

void HDE::SimpleServer::handler()
{
    std::cout << buffer << std::endl;
}

void HDE::SimpleServer::responder()
{
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 17\r\n"
        "\r\n"
        "Hello from server";

    write(new_socket, response.c_str(), response.length());
    close(new_socket);
}

void HDE::SimpleServer::launch()
{

    while (true)
    {
        std::cout << "===== WAITING  =====" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "===== DONE =====" << std::endl;
    }
}

std::string HDE::SimpleServer::get_request_method(const std::string &request)
{
    std::istringstream request_stream(request);
    std::string method;
    request_stream >> method;
    return method;
}

std::string HDE::SimpleServer::get_route(const std::string &request)
{
    std::istringstream request_stream(request);
    std::string method;
    std::string route;
    request_stream >> method;
    request_stream >> route;
    return route;
}