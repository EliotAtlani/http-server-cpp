#include "Api/api.hpp"

int main()
{
    // Create the API server
    HDE::Api api(8080, INADDR_ANY, 10);

    // Define routes
    api.get("/greet", [](const std::unordered_map<std::string, std::string> &params)
            {
    std::string name = params.at("name");
    return "Hello, " + name + "!"; });

    // Start the server
    api.launch();

    return 0;
}