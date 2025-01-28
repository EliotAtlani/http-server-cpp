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
HDE::Api &HDE::Api::get(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler)
{
    routes[build_key("GET", route)] = handler;
    return *this;
}

// Register POST route
HDE::Api &HDE::Api::post(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler)
{
    routes[build_key("POST", route)] = handler;
    return *this;
}

// Register PUT route
HDE::Api &HDE::Api::put(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler)
{
    routes[build_key("PUT", route)] = handler;
    return *this;
}

// Register DELETE route
HDE::Api &HDE::Api::del(const std::string &route, std::function<std::string(const std::unordered_map<std::string, std::string> &)> handler)
{
    routes[build_key("DELETE", route)] = handler;
    return *this;
}
std::unordered_map<std::string, std::string> HDE::Api::parse_query(const std::string &query)
{
    std::unordered_map<std::string, std::string> params;
    std::istringstream query_stream(query);
    std::string pair;

    while (std::getline(query_stream, pair, '&'))
    {
        size_t equal_pos = pair.find("=");
        if (equal_pos != std::string::npos)
        {
            std::string key = pair.substr(0, equal_pos);
            std::string value = pair.substr(equal_pos + 1);
            params[key] = value;
        }
    }

    return params;
}
std::tuple<std::string, std::string, std::unordered_map<std::string, std::string>> HDE::Api::parse_request(const std::string &request)
{
    std::istringstream request_stream(request);
    std::string method, full_route, route, query;

    // Extract the method and full route (e.g., "GET /path?key=value HTTP/1.1")
    request_stream >> method >> full_route;

    // Separate route and query string
    size_t query_start = full_route.find("?");
    if (query_start != std::string::npos)
    {
        route = full_route.substr(0, query_start);  // Extract the path before '?'
        query = full_route.substr(query_start + 1); // Extract the query string after '?'
    }
    else
    {
        route = full_route; // No query string, use the entire route
    }

    // Parse query parameters into a map
    std::unordered_map<std::string, std::string> params = parse_query(query);

    // Return the method, route, and parameters
    return {method, route, params};
}

// Handle an incoming request
void HDE::Api::handle_request(const std::string &request, int client_socket)
{
    auto [method, route, params] = parse_request(request);

    std::string key = build_key(method, route);

    if (routes.find(key) != routes.end())
    {
        // Execute the handler and get the response body
        std::string response_body = routes[key](params);

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
