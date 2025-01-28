#include "Api/api.hpp"

int main()
{
    // Create the API server
    HDE::Api api(8080, INADDR_ANY, 10);

    // Define routes
    api.get("/home", []()
            { return "Welcome to the home page!"; });

    api.post("/submit", []()
             { return "Form submitted successfully!"; });

    api.put("/update", []()
            { return "Resource updated!"; });

    api.del("/delete", []()
            { return "Resource deleted!"; });

    // Start the server
    api.launch();

    return 0;
}