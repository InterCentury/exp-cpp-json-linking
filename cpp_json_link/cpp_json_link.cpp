#include <iostream>
#include "third_party/nlohmann/json.hpp"

using json = nlohmann::json;

std::string colorCode(const std::string& color) {
    if (color == "red")    return "\033[31m";
    if (color == "green")  return "\033[32m";
    if (color == "yellow") return "\033[33m";
    if (color == "blue")   return "\033[34m";
    if (color == "reset")  return "\033[0m";
    return "\033[0m"; // default
}

int main() {
    json config;

    config["print_hello"] = true;
    config["hello_color"] = "red";

    if (config["print_hello"]) {
        std::string color = config["hello_color"];
        std::cout << colorCode(color)
            << "Hello World"
            << colorCode("reset") << "\n";
    }

    return 0;
}
