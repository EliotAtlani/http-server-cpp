#include "api.hpp"
#include <unistd.h>
#include <string.h>

// Constructor
HDE::Api::Api(int port, u_long interface, int backlog)
    : SimpleServer(AF_INET, SOCK_STREAM, 0, port, interface, backlog)
{
}

// Helper to build the route key
std::string HDE::Api::build_key(const std::string &method, const std::string &route)
{
    return method + ":" + route;
}

// Register GET route
HDE::Api &HDE::Api::get(const std::string &route, std::function<std::string()> handler)
{
    routes[build_key("GET", route)] = handler;
    return *this;
}

// Register POST route
HDE::Api &HDE::Api::post(const std::string &route, std::function<std::string()> handler)
{
    routes[build_key("POST", route)] = handler;
    return *this;
}

// Register PUT route
HDE::Api &HDE::Api::put(const std::string &route, std::function<std::string()> handler)
{
    routes[build_key("PUT", route)] = handler;
    return *this;
}

// Register DELETE route
HDE::Api &HDE::Api::del(const std::string &route, std::function<std::string()> handler)
{
    routes[build_key("DELETE", route)] = handler;
    return *this;
}

// Parse the HTTP request to extract the method and route
std::pair<std::string, std::string> HDE::Api::parse_request(const std::string &request)
{
    std::istringstream request_stream(request);
    std::string method, route;

    request_stream >> method >> route; // Extract HTTP method and route
    return {method, route};
}

// Handle an incoming request
void HDE::Api::handle_request(const std::string &request, int client_socket)
{
    auto [method, route] = parse_request(request);
    std::string key = build_key(method, route);

    if (routes.find(key) != routes.end())
    {
        // Execute the handler and get the response body
        std::string response_body = routes[key]();

        // Send the response back to the client
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n" +
            std::string("Content-Length: ") + std::to_string(response_body.size()) + "\r\n\r\n" +
            response_body;

        write(client_socket, response.c_str(), response.size());
    }
    else
    {
        // Respond with 404 if no route matches
        std::string response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "No route!";
        write(client_socket, response.c_str(), response.size());
    }

    close(client_socket); // Close the connection
}

// Core server loop (continuously listens for incoming requests)
void HDE::Api::launch()
{
    std::cout << "Server running on port " << get_socket()->get_listening() << "..." << std::endl;

    while (true)
    {
        std::cout << "Waiting for a connection..." << std::endl;

        accepter(); // Accept an incoming connection
        handler();  // Read the request

        std::string request(buffer); // Convert buffer to string
        handle_request(request, new_socket);
    }
}
