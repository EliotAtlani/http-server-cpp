#ifndef API_hpp
#define API_hpp

#include <stdio.h>

#include "../Server/SimpleServer.hpp"

namespace HDE
{
    class Api : public SimpleServer
    {
    private:
        // Route key: method + route
        std::unordered_map<std::string, std::function<std::string(const std::unordered_map<std::string, std::string> &)>> routes;

        // Helper to build the route key
        std::string build_key(const std::string &method, const std::string &route);

        int port;

        // Parse HTTP method and route from request
        std::tuple<std::string, std::string, std::unordered_map<std::string, std::string>> parse_request(const std::string &request);
        std::unordered_map<std::string, std::string> parse_query(const std::string &query);

    public:
        Api(int port, u_long interface, int backlog);

        void launch();

        // Route registration methods
        Api &get(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler);
        Api &post(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler);
        Api &put(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler);
        Api &del(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler);

        // Logic to handle requests (simulating for now)
        void handle_request(const std::string &request, int client_socket);
    };
}

#endif