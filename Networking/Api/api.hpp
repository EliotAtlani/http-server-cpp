#ifndef API_hpp
#define API_hpp

#include <stdio.h>

#include "../Server/SimpleServer.hpp"

namespace HDE
{
    class Api : public SimpleServer
    {
    private:
        // Key: HTTP method + route, Value: handler function
        std::unordered_map<std::string, std::function<std::string()>> routes;

        int port;

        // Helper to build the key
        std::string build_key(const std::string &method, const std::string &route);

        // Parse HTTP method and route from request
        std::pair<std::string, std::string> parse_request(const std::string &request);

    public:
        Api(int port, u_long interface, int backlog);

        void launch();

        // Route registration methods
        Api &get(const std::string &route, std::function<std::string()> handler);
        Api &post(const std::string &route, std::function<std::string()> handler);
        Api &put(const std::string &route, std::function<std::string()> handler);
        Api &del(const std::string &route, std::function<std::string()> handler);

        // Logic to handle requests (simulating for now)
        void handle_request(const std::string &request, int client_socket);
    };
}

#endif