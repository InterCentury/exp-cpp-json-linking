#include <iostream>
#include "third_party/nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    json config;

    config["print_hello"] = false;
    config["hello_color"] = "red";

    if (config["print_hello"]) {
        std::cout << "Hello World\n";
    }

    return 0;
}
